#include <stdio.h>
#include <inttypes.h>
#include "cpu.h"
#include "decode.h"
#include "alu.h"

int main(){
    CPU cpu;
    cpu_reset(&cpu);
    reg_write(&cpu, 1, 10);
    uint32_t instruction = 0xFFC08193;
    execute_instruction(&cpu, instruction);
    printf("addi x3, x1, -4 \nx3: %" PRIu32 "\nPC: %" PRIu32 "\n", reg_read(&cpu, 3), cpu.pc);
    reg_write(&cpu, 1, 20);
    reg_write(&cpu, 2, 7);
    instruction = 0x002081B3;
    execute_instruction(&cpu, instruction);
    printf("addi x3, x1, x2 \nx3: %" PRIu32 "\nPC: %" PRIu32 "\n", reg_read(&cpu, 3), cpu.pc);

    reg_write(&cpu, 1, 9); // 1001
    reg_write(&cpu, 2, 5); // 0101
    instruction = 0x0020f1b3;
    execute_instruction(&cpu, instruction);
    printf("and x3, x1, x2 \nx3: %" PRIu32 "\nPC: %" PRIu32 "\n", reg_read(&cpu, 3), cpu.pc);

    instruction = 0x0020e1b3;
    execute_instruction(&cpu, instruction);
    printf("or x3, x1, x2 \nx3: %" PRIu32 "\nPC: %" PRIu32 "\n", reg_read(&cpu, 3), cpu.pc);

    instruction = 0x0020c1b3;
    execute_instruction(&cpu, instruction);
    printf("xor x3, x1, x2 \nx3: %" PRIu32 "\nPC: %" PRIu32 "\n", reg_read(&cpu, 3), cpu.pc);

}