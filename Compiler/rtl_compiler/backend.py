import re
from collections import defaultdict

from .lowering import build_processes, ordered_for_target


INTERNAL_SIGNAL_PREFIX = "__pn_"


def _next_signal(state_name):
    return f"{INTERNAL_SIGNAL_PREFIX}next_{state_name}"


def _derived_expression(signal):
    """Accept a redundant `name = rhs` emitted by an LLM and keep only rhs."""
    name = str(signal.get("name", "")).strip()
    expression = _expr(signal.get("expression", ""))
    match = re.match(
        r"^\s*([A-Za-z_][A-Za-z0-9_$]*)\s*(?:<=|=(?!=))\s*(.+)$",
        expression, re.S)
    if match and match.group(1) == name:
        return match.group(2).strip()
    return expression


def _derived_width(model, signal):
    if signal.get("width") is not None:
        return signal["width"]
    name = str(signal.get("name", "")).strip()
    states = model.state_map()
    candidates = []
    if name.endswith("_next"):
        candidates.append(name[:-5])
    if name.startswith("next_"):
        candidates.append(name[5:])
    for candidate in candidates:
        if candidate in states:
            return states[candidate].width
    return 1


def _expr(value):
    if isinstance(value, bool):
        return "1'b1" if value else "1'b0"
    text = str(value).strip()
    if text.lower() == "true":
        return "1'b1"
    if text.lower() == "false":
        return "1'b0"
    # Verilator rejects a bit-select applied directly to a parenthesized
    # concatenation arithmetic expression, e.g. ({1'b0,a}+{1'b0,b})[32].
    # A right shift is equivalent when the destination width selects the bit.
    expression_select = re.compile(
        r"\((?P<body>\{[^()]+\}\s*[+-]\s*\{[^()]+\})\)"
        r"\[(?P<index>\d+)\]")
    text = expression_select.sub(
        lambda match: (f"(({match.group('body')}) >> "
                       f"{match.group('index')})"), text)
    return text


def _range(width):
    if width is None:
        return ""
    if isinstance(width, int):
        return "" if width == 1 else f"[{width - 1}:0] "
    text = str(width).strip()
    if text in {"", "1", "1 bit", "1 bits"}:
        return ""
    if text.startswith("[") and text.endswith("]"):
        return text + " "
    match = re.fullmatch(r"(\d+)\s*(?:bits?)?", text, re.I)
    if match:
        number = int(match.group(1))
        return "" if number == 1 else f"[{number - 1}:0] "
    return f"[({_expr(text)})-1:0] "


def _reset_condition(domain):
    return f"!{domain.reset}" if domain.reset_polarity in {"active_low", "low"} else domain.reset


def _sensitivity(domain):
    result = f"{domain.edge} {domain.clock}"
    if domain.reset and domain.reset_type in {"asynchronous", "async"}:
        reset_edge = "negedge" if domain.reset_polarity in {"active_low", "low"} else "posedge"
        result += f" or {reset_edge} {domain.reset}"
    return result


def _find_action(transition, target, otherwise=False):
    actions = transition.else_actions if otherwise else transition.actions
    for action in actions:
        if action.base_target == target:
            return action
    return None


def _actions_for_target(transition, target, otherwise=False):
    actions = transition.else_actions if otherwise else transition.actions
    return [action for action in actions if action.base_target == target]


def _next_lvalue(action_target, state_name):
    suffix = action_target[len(state_name):]
    return _next_signal(state_name) + suffix


def _memory_depth(model, state):
    if state.depth:
        return state.depth
    for resource in model.resources:
        if str(resource.get("name", "")) != state.name:
            continue
        parameters = resource.get("parameters", {}) or {}
        return resource.get("depth", parameters.get("depth", parameters.get("DEPTH")))
    return None


def _render_next_logic(model, process, target):
    state = model.state_map()[target]
    transitions = model.transition_map()
    names = ordered_for_target(model, process, target)
    next_name = _next_signal(target)
    lines = ["always @* begin", f"    {next_name} = {target};"]
    for index, name in enumerate(names):
        transition = transitions[name]
        actions = _actions_for_target(transition, target)
        keyword = "if" if index == 0 else "else if"
        lines.append(f"    {keyword} ({_expr(transition.guard)}) begin")
        for action in actions:
            lines.append(
                f"        {_next_lvalue(action.target, target)} = "
                f"{_expr(action.expression)};")
        lines.append("    end")
        else_actions = _actions_for_target(transition, target, otherwise=True)
        if else_actions:
            if len(names) != 1:
                # Validation keeps the model deterministic; this situation is
                # still emitted with the transition-local else at lowest rank.
                lines.append("    else begin")
            else:
                lines.append("    else begin")
            for action in else_actions:
                lines.append(
                    f"        {_next_lvalue(action.target, target)} = "
                    f"{_expr(action.expression)};")
            lines.append("    end")
    lines.append("end")
    return lines


def _render_memory_updates(model, process, target, indent):
    transitions = model.transition_map()
    names = ordered_for_target(model, process, target)
    lines = []
    for index, name in enumerate(names):
        transition = transitions[name]
        actions = [action for action in transition.actions
                   if action.base_target == target]
        keyword = "if" if index == 0 else "else if"
        lines.append(f"{indent}{keyword} ({_expr(transition.guard)}) begin")
        for action in actions:
            lines.append(
                f"{indent}    {action.target} <= {_expr(action.expression)};")
        lines.append(f"{indent}end")
    return lines


def _render_process(model, process):
    states = model.state_map()
    transitions = model.transition_map()
    domain = model.domain_map()[process.clock_domain]
    targets = []
    for name in process.transitions:
        for action in transitions[name].actions:
            if action.base_target not in targets:
                targets.append(action.base_target)
    scalar_targets = [name for name in targets if states[name].type not in {"memory", "ram"}]
    memory_targets = [name for name in targets if states[name].type in {"memory", "ram"}]
    if not targets:
        return [], []

    combinational = []
    for target in scalar_targets:
        combinational.extend(_render_next_logic(model, process, target))
        combinational.append("")

    clocked = [f"// Sequential process: {process.name}",
               f"always @({_sensitivity(domain)}) begin"]
    if domain.reset:
        condition = _reset_condition(domain)
        if scalar_targets:
            clocked.append(f"    if ({condition}) begin")
            for target in scalar_targets:
                clocked.append(f"        {target} <= {_expr(states[target].reset_value)};")
            clocked.append("    end else begin")
            body_indent = "        "
        else:
            clocked.append(f"    if (!({condition})) begin")
            body_indent = "        "
    else:
        body_indent = "    "

    for target in scalar_targets:
        clocked.append(f"{body_indent}{target} <= {_next_signal(target)};")
    for target in memory_targets:
        clocked.extend(_render_memory_updates(model, process, target, body_indent))
    if domain.reset:
        clocked.append("    end")
    clocked.append("end")
    return combinational, clocked


def _cdc_info(model, entry, index):
    source = str(entry.get("source", "")).strip()
    destination = entry.get("destination_clock_domain", entry.get("destination"))
    if isinstance(destination, dict):
        destination = destination.get("clock_domain", destination.get("domain", destination.get("name")))
    destination = str(destination or "").strip()
    synchronizer = entry.get("synchronizer", {}) or {}
    stages = int(synchronizer.get("stages", entry.get("stages", 2)))
    registers = synchronizer.get("registers", entry.get("registers", [])) or []
    if isinstance(registers, str):
        registers = [registers]
    if not registers:
        registers = [f"{source}_{destination}_sync{i + 1}" for i in range(stages)]
    return source, destination, stages, [str(x) for x in registers]


def _render_cdc(model):
    state_map = model.state_map()
    port_map = model.port_map()
    derived = {str(x.get("name", "")): x for x in model.derived_signals}
    declarations = []
    blocks = []
    for index, entry in enumerate(model.cdc):
        source, destination, stages, registers = _cdc_info(model, entry, index)
        if source in state_map:
            width = state_map[source].width
        elif source in port_map:
            width = port_map[source].width
        else:
            width = derived.get(source, {}).get("width", 1)
        for register in registers:
            if register not in state_map:
                declarations.append(f"reg {_range(width)}{register};")
        domain = model.domain_map()[destination]
        blocks.extend([f"// CDC synchronizer: {source} -> {destination}",
                       f"always @({_sensitivity(domain)}) begin"])
        if domain.reset:
            blocks.append(f"    if ({_reset_condition(domain)}) begin")
            for register in registers:
                reset = state_map[register].reset_value if register in state_map else "0"
                blocks.append(f"        {register} <= {_expr(reset)};")
            blocks.append("    end else begin")
            indent = "        "
        else:
            indent = "    "
        previous = source
        for register in registers:
            blocks.append(f"{indent}{register} <= {previous};")
            previous = register
        if domain.reset:
            blocks.append("    end")
        blocks.extend(["end", ""])
    return declarations, blocks


def _render_instances(model):
    lines = []
    for resource in model.resources:
        kind = str(resource.get("type", "")).lower()
        if kind not in {"submodule", "module", "instance"}:
            continue
        implementation = resource.get("implementation", resource.get("module"))
        if isinstance(implementation, dict):
            implementation = implementation.get("module", implementation.get("name"))
        module_name = str(implementation or "").strip()
        instance_name = str(resource.get("name", f"u_{module_name}")).strip()
        parameters = resource.get("parameters", {}) or {}
        ports = resource.get("ports", {}) or {}
        if isinstance(parameters, list):
            parameters = {str(x["name"]): x.get("value", x.get("default", 0)) for x in parameters}
        if isinstance(ports, list):
            ports = {str(x.get("name", x.get("port"))): x.get("signal", x.get("connection")) for x in ports}
        header = module_name
        if parameters:
            values = ",\n".join(f"        .{name}({_expr(value)})" for name, value in parameters.items())
            header += f" #(\n{values}\n    )"
        connections = ",\n".join(f"        .{name}({_expr(value)})" for name, value in ports.items())
        lines.extend([f"{header} {instance_name} (", connections, ");", ""])
    return lines


def generate_verilog(model):
    ports = model.port_map()
    states = model.state_map()
    derived_names = {str(item.get("name", "")).strip() for item in model.derived_signals}
    combinational_targets = {
        action.base_target
        for transition in model.transitions if transition.transition_type == "combinational"
        for action in transition.actions
    }
    sequential_targets = {
        action.base_target
        for transition in model.transitions if transition.transition_type == "sequential"
        for action in transition.actions
    }
    initial_targets = {
        state.name for state in model.states if state.initial_value is not None
    }
    cdc_targets = set()
    for index, entry in enumerate(model.cdc):
        _, _, _, registers = _cdc_info(model, entry, index)
        cdc_targets.update(registers)
    registered_targets = sequential_targets | cdc_targets | initial_targets

    lines = ["// Generated deterministically from Hardware-aware Petri Net IR.",
             "// Do not edit generated RTL; edit the IR/specification instead."]
    if model.parameters:
        lines.append(f"module {model.module_name} #(")
        for index, parameter in enumerate(model.parameters):
            comma = "," if index + 1 < len(model.parameters) else ""
            lines.append(f"    parameter {parameter.name} = {_expr(parameter.value)}{comma}")
        lines.append(") (")
    else:
        lines.append(f"module {model.module_name} (")
    for index, port in enumerate(model.ports):
        comma = "," if index + 1 < len(model.ports) else ""
        signed = "signed " if port.signed else ""
        port_kind = ""
        if port.direction == "output" and port.name in registered_targets:
            port_kind = "reg "
        elif port.direction == "output":
            port_kind = "wire "
        lines.append(
            f"    {port.direction} {port_kind}{signed}{_range(port.width)}{port.name}{comma}")
    lines.extend([");", ""])

    for state in model.states:
        if state.name in ports:
            continue
        signed = "signed " if "signed" in state.datatype and "unsigned" not in state.datatype else ""
        if state.type in {"memory", "ram"}:
            depth = _memory_depth(model, state)
            lines.append(f"reg {signed}{_range(state.width)}{state.name} [0:{_expr(depth)}-1];")
        else:
            lines.append(f"reg {signed}{_range(state.width)}{state.name};")

    for target in sorted(sequential_targets):
        state = states[target]
        if state.type not in {"memory", "ram"}:
            signed = "signed " if "signed" in state.datatype and "unsigned" not in state.datatype else ""
            lines.append(
                f"reg {signed}{_range(state.width)}{_next_signal(target)};")

    for signal in model.derived_signals:
        name = str(signal.get("name", "")).strip()
        if name not in ports:
            lines.append(f"wire {_range(_derived_width(model, signal))}{name};")
    cdc_declarations, cdc_blocks = _render_cdc(model)
    lines.extend(cdc_declarations)
    if model.states or model.derived_signals or cdc_declarations:
        lines.append("")

    initialized_states = [state for state in model.states
                          if state.initial_value is not None]
    if initialized_states:
        lines.append("initial begin")
        for state in initialized_states:
            lines.append(
                f"    {state.name} = {_expr(state.initial_value)};")
        lines.extend(["end", ""])

    for signal in model.derived_signals:
        lines.append(
            f"assign {signal['name']} = {_derived_expression(signal)};")
    for transition in model.transitions:
        if transition.transition_type != "combinational":
            continue
        for action in transition.actions:
            else_action = _find_action(transition, action.base_target, otherwise=True)
            if transition.guard in {"1", "1'b1", "true", "True"}:
                expression = _expr(action.expression)
            else:
                expression = (f"({_expr(transition.guard)}) ? ({_expr(action.expression)}) : "
                              f"({_expr(else_action.expression)})")
            lines.append(f"assign {action.target} = {expression};")
    if model.derived_signals or combinational_targets:
        lines.append("")

    for process in build_processes(model):
        combinational, clocked = _render_process(model, process)
        lines.extend(combinational)
        lines.extend(clocked)
        if clocked:
            lines.append("")
    lines.extend(cdc_blocks)
    lines.extend(_render_instances(model))
    while lines and lines[-1] == "":
        lines.pop()
    lines.extend(["", "endmodule", ""])
    return "\n".join(lines)
