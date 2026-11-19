RV32I Single-Cycle Processor
C reference model → Verilog RTL → functional verification → synthesis → FPGA

An educational processor-design project exploring how 32-bit RISC-V instructions move from architectural behavior in C to synthesizable digital hardware. The goal is to build a single-cycle RV32I processor, verify its execution against a C reference model, examine synthesis and timing results, and eventually demonstrate it on a Digilent Basys3 FPGA.
Status (November 19, 2026): In development. The C model executes a six-instruction subset with instruction fetch and directed regression tests. The Verilog program counter and ALU are implemented and have been simulated independently. The integrated RTL processor is not yet complete, and full RV32I compliance is not claimed.

Current implementation
Component	C reference model	Verilog RTL
Program counter	Implemented (PC + 4)	Implemented; simulated
Register file	32 × 32-bit registers; x0 protected	In progress locally; not yet committed/verified
Instruction decoding	OP and OP-IMM field extraction	Planned
ALU	ADD, SUB, AND, OR, XOR	Implemented; directed self-checking testbench
I-type immediate	12-bit sign extension	Planned
Instruction memory/fetch	Implemented with alignment and bounds checks	Planned
Instruction execution	Decode, execute, writeback, sequential PC update	Not yet integrated
Loads/stores, branches, jumps	Not implemented	Not implemented
Synthesis, timing, FPGA demonstration	Not applicable	Pending


Supported instructions in the C model
Instruction	Encoding format	C model	Integrated RTL CPU
ADD	R-type	Implemented; directed test	Pending
SUB	R-type	Implemented; directed test	Pending
AND	R-type	Implemented; directed test	Pending
OR	R-type	Implemented; directed test	Pending
XOR	R-type	Implemented; directed test	Pending
ADDI	I-type	Implemented; directed test	Pending


The C implementation uses x0 = 0, sign-extends 12-bit immediates, rejects unsupported instruction encodings, and advances the PC by four bytes for supported instructions. Branches, jumps, loads, and stores are outside the current execution subset.
Repository structure
rv32i-single-cycle-core/
├── c_model/        # C CPU state, decode, ALU, and instruction memory
├── rtl/            # Verilog modules (currently PC and ALU on main)
├── tb/             # Individual RTL simulation testbenches
├── tests/          # C instruction regression tests
├── .gitignore
└── README.md
Additional modules and integration tests will be committed as they are implemented and verified.
Build and run the C reference model
Requirement: GCC or another C11-compatible compiler. From the repository root:
gcc -std=c11 -Wall -Wextra -I c_model \
  c_model/main.c c_model/cpu.c c_model/decode.c \
  c_model/alu.c c_model/memory.c -o riscvsim
./riscvsim
The included demonstration loads three encoded instructions into instruction memory:
addi x1, x0, 10
addi x2, x0, 20
add  x3, x1, x2
Expected architectural state after three successful steps:
x1 = 10
x2 = 20
x3 = 30
PC = 12
On Windows, the output may be riscvsim.exe (for example, run ./riscvsim.exe in MSYS2).
Run the C regression tests
gcc -std=c11 -Wall -Wextra -I c_model \
  tests/test_cpu.c c_model/cpu.c c_model/decode.c \
  c_model/alu.c c_model/memory.c -o test_cpu
./test_cpu
tests/test_cpu.c contains six directed instruction tests for ADDI, ADD, SUB, AND, OR, and XOR. Each test uses assertions to check instruction success, the destination register value, and a four-byte PC increment. These are directed tests, not exhaustive RV32I coverage.
RTL design and simulation
The current RTL sources are:
- rtl/pc.v — 32-bit sequential program counter with synchronous reset and PC + 4 behavior.
- rtl/alu.v — combinational 32-bit ADD, SUB, AND, OR, and XOR, selected by a 3-bit control signal.
The testbenches are:
- tb/tb_pc.v — reset and increment simulation stimulus; automatic assertions are still to be added.
- tb/tb_alu.v — directed result comparisons including arithmetic wraparound and an unsupported control value.
These files can be added to an AMD Vivado simulation project and run with tb_pc or tb_alu selected as the simulation top. Individual module simulations are not evidence that a complete CPU works.
Planned single-cycle execution path
Instruction address (PC)
          |
          v
  Instruction memory
          |
          v
   Decode + control ------> Register file reads
                                  |
                       Immediate / operand select
                                  |
                                  v
                                 ALU
                                  |
                                  v
                           Register writeback

              PC advances to next instruction
This illustrates the initial arithmetic-instruction subset, not the full RV32I datapath. Branch/jump selection and load/store data paths will be added later.
Verification strategy
1. Verify each RTL module independently using directed and edge-case testbenches.
2. Integrate the datapath, then execute the same three-instruction program as the C model.
3. Compare register and PC results against expected architectural state.
4. Expand to more instructions and add C-versus-RTL checking.
5. Run lint, synthesis, and timing analysis; record the actual results rather than claiming them in advance.
Roadmap
- [x] C CPU/register model and sequential PC behavior
- [x] C decode, immediate sign extension, and five ALU operations
- [x] C instruction memory/fetch and cpu_step()
- [x] Six directed C instruction regression tests
- [x] Verilog program counter and simulation stimulus
- [x] Verilog ALU and directed self-checking testbench
- [ ] Complete and verify Verilog register file (x0, reset, read/write behavior)
- [ ] Instruction decoder, immediate generator, and control unit
- [ ] RTL instruction memory
- [ ] Integrated single-cycle CPU supporting ADDI, ADD, and SUB
- [ ] Self-checking CPU integration testbench
- [ ] Expand ALU/CPU instruction coverage and edge-case tests
- [ ] Lint, synthesis, timing constraints, and timing/resource reports
- [ ] Basys3 FPGA demonstration
- [ ] Extend toward the remaining RV32I instruction formats
Near-term target: A working, self-checking, integrated RTL instruction subset. Additional instructions, FPGA deployment, and ASIC-oriented analysis follow after the first processor-level test passes.
Engineering focus
This project is intended to develop practical skills in RTL design, CPU datapaths, architectural modeling, functional verification, debug, synthesis, and static timing analysis. Work and results are added incrementally with testable commits.
References
- RISC-V Unprivileged ISA Specification
- RISC-V ISA Manual repository
- UC Berkeley CS61C — Great Ideas in Computer Architecture
Note: This is an independent learning and portfolio project. Unless specifically reported in a future update, the design has not been synthesized, timing-closed, or demonstrated on an FPGA.
