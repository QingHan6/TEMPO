import json
from pathlib import Path

from .backend import generate_verilog
from .lowering import build_processes
from .parser import parse_ir
from .validator import validate_ir


def compile_ir(ir_path, output_path, report_path=None):
    """Compile YAML/JSON Petri Net IR to synthesizable Verilog."""
    model = parse_ir(ir_path)
    warnings = validate_ir(model)
    rtl = generate_verilog(model)
    output = Path(output_path).resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(rtl, encoding="utf-8")

    processes = build_processes(model)
    report = {
        "status": "ok",
        "input_ir": str(Path(ir_path).resolve()),
        "output_rtl": str(output),
        "module": model.module_name,
        "counts": {
            "ports": len(model.ports),
            "clock_domains": len(model.clock_domains),
            "states": len(model.states),
            "transitions": len(model.transitions),
            "sequential_processes": len(processes),
            "resources": len(model.resources),
            "cdc_crossings": len(model.cdc),
        },
        "warnings": list(warnings),
    }
    if report_path:
        report_output = Path(report_path).resolve()
        report_output.parent.mkdir(parents=True, exist_ok=True)
        report_output.write_text(
            json.dumps(report, ensure_ascii=False, indent=2) + "\n",
            encoding="utf-8")
    return output, report
