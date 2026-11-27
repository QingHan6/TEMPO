# TEMPO

## Directory Structure

```text
final_work/
├── main.py                    # Single command-line entry point
├── IRgeneration/              # Spec→HW-IR, checker1/2, general-purpose LLM calls
├── Compiler/                  # Deterministic RTL compiler, LLM RTL backend, HLS backend
├── sva_generation/            # Property IR and SVA generation/injection
├── iteration/                 # Verilator verification, failure feedback, HW-IR/SVA repair loop
├── tests/                     # Reorganized regression tests
└── example/                   # Test examples
```

`iteration/` exists as a separate package because the full feedback after an RTL failure, the SVA diagnostics, and the transactional HW-IR repair loop are not a good fit for the top-level entry point. `main.py` is only responsible for starting the unified pipeline.

## Environment and Verification

The LLM stages read `OPENAI_API_KEY`, `OPENAI_BASE_URL`, and `OPENAI_MODEL`, and also support the corresponding command-line arguments. `source .env` can configure the variables in your environment (fill in your own API key).

Python dependencies can be installed with `pip install -r requirements.txt`.

RTL verification requires `verilator` to be available on the system.

## Four Main Usage Modes

Run the following from this directory:

```bash
python main.py path/to/spec.md
python main.py path/to/spec.md --no-sva
python main.py path/to/spec.md --no-compiler
python main.py path/to/spec.md --hls
```

- Default: Spec → HW-IR → checker1/2 → deterministic compiler → RTL → RTL-first Verilator; Property IR/SVA is generated only when the RTL simulation actually fails, and the diagnostics are fed back into the HW-IR repair loop.
- `--no-sva`: Completely disables Property IR, SVA generation/injection, and SVA compilation repair; RTL-only failures can still be fed back to repair the HW-IR.
- `--no-compiler`: Skips the deterministic compiler and uses an LLM to turn the checked HW-IR into RTL; subsequent verification and optional SVA diagnostics remain unchanged.
- `--hls`: Generates `generated_hls.cpp` after checker1/2, producing no RTL and running no Verilator/Property IR/SVA. This option is mutually exclusive with `--no-compiler`.

You can also start from an existing IR:

```bash
python main.py --ir path/to/ir.yaml
```

By default, artifacts are written to a `generation/` directory next to the input file; this can be overridden with `--generation-dir DIR`. For the full set of options, see:

```bash
python main.py --help
```



