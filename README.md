RV32I Single-Cycle Processor
A RISC-V processor development project progressing from a C reference model to a single-cycle Verilog implementation targeting the Digilent Basys3 FPGA.
Status: In development. The C reference model supports a subset of RV32I arithmetic and logical instructions. Instruction fetching, memory operations, control flow, RTL design, and FPGA validation are planned or in progress as indicated below.

Overview
This project explores how a processor executes instructions at both the software-model and register-transfer levels. The first phase builds a C reference model for RV32I instruction decoding, register-file behavior, ALU operations, and program-counter management. The next phase implements a single-cycle processor in Verilog, with simulation and FPGA validation against the reference model.
The long-term goal is a reproducible hardware design with clear architectural documentation and instruction-level verification—not just a collection of HDL modules.
Project objectives
- Implement the RV32I base integer instruction set in a C reference model.
- Design a single-cycle RV32I datapath and control unit in Verilog.
- Verify instruction execution through focused tests and comparison with the C model.
- Simulate and synthesize the hardware design using AMD Vivado.
- Target the Digilent Basys3 FPGA for a final hardware demonstration.
Current implementation
The C reference model currently includes:
- CPU state: 32 general-purpose registers and a program counter.
- Register file: Reads from x0 return zero; writes to x0 are ignored.
- Instruction decoding: Extraction of opcode, register indices, function fields, and 12-bit I-type immediates.
- Immediate handling: 12-bit sign extension.
- ALU: Addition, subtraction, XOR, OR, and AND operations.
- Execution: Dispatch for supported OP and OP-IMM encodings; register writeback and sequential PC + 4 updates.
- Error reporting: Unsupported instruction encodings return a failure status rather than updating architectural state.
Implemented instruction subset
Instruction	Format	Status
ADD	R-type	Implemented
SUB	R-type	Implemented
XOR	R-type	Implemented; regression testing pending
OR	R-type	Implemented; regression testing pending
AND	R-type	Implemented; regression testing pending
ADDI	I-type	Implemented


Scope note: This is not yet a complete RV32I simulator or a completed Verilog core. Instruction fetch, data memory, branches, jumps, remaining instructions, and automated verification are still to come.
Architecture and organization
Planned repository layout (folders are added as their contents are developed):
rv32i-single-cycle-core/
├── README.md           # Project overview and setup
├── c_model/            # C reference CPU, decoder, and ALU
├── rtl/                # Verilog processor modules (planned)
├── tb/                 # HDL testbenches (planned)
├── tests/              # Assembly programs and expected results (planned)
├── docs/               # Architecture notes and engineering log
└── fpga/               # Basys3 integration files (planned)
Current C-model execution flow:
32-bit instruction
       |
       v
     decode()
       |
       v
 execute_instruction()
       |
       +--> OP     (register-register)
       |       |
       |       v
       |    execute_op()
       |
       +--> OP-IMM (register-immediate)
               |
               v
         execute_op_imm()
               |
               v
      ALU result / writeback
               |
               v
       sequential PC update
At present, test code supplies the encoded instruction directly to execute_instruction(). The next milestone is to fetch instructions from memory using the PC.
Build the C model
Requirements: A C11-compatible compiler such as GCC.
From the repository root, if source files are in c_model/:
gcc -Wall -Wextra -std=c11 c_model/main.c c_model/cpu.c c_model/decode.c c_model/alu.c -o riscvsim
Run on Linux/macOS or an MSYS2 shell:
./riscvsim
On Windows, the output may be named riscvsim.exe and can be run in PowerShell with:
.\riscvsim.exe
If the source layout or build procedure changes, update these commands accordingly.
Testing and verification
Current manual tests have exercised arithmetic instruction execution and program-counter behavior. The verification plan is to create repeatable tests for:
- Register-file invariants (x0, valid register indices).
- Correct immediate sign extension, including negative values.
- ALU operations and register writeback.
- Invalid encodings that must not modify CPU state.
- Instruction fetch, branches, loads, and stores as those features are added.
- Comparison of C reference outcomes with Verilog simulation results.
Test results and coverage claims will be documented as tests are added; passing all RV32I instructions is not claimed at this stage.
Roadmap
- [x] CPU state, reset, and register-file access
- [x] Program counter and sequential increment
- [x] Basic instruction decoding and sign extension
- [x] Core ALU arithmetic/logic functions
- [x] Instruction execution dispatch and shared writeback
- [ ] Instruction memory, fetch, and cpu_step()
- [ ] Data memory, loads, and stores
- [ ] Branches, jumps, and remaining RV32I operations
- [ ] Automated C-model regression tests
- [ ] Single-cycle Verilog datapath and control
- [ ] RTL testbenches and comparison against the C model
- [ ] Vivado synthesis and Basys3 FPGA validation
Design notes
The C reference model is intentionally modular:
- decode interprets instruction fields without directly changing CPU state.
- alu provides arithmetic and logical operations on operand values.
- cpu manages architectural state, instruction dispatch, and register writeback.
This separation is intended to make expected behavior easier to test before implementing corresponding hardware modules.
References
- RISC-V Unprivileged ISA Specification
- RISC-V Instruction Encodings
- Berkeley CS61C Datapath Notes
Project status
Independent educational and portfolio project. The implementation, tests, and documentation will evolve as development continues.
