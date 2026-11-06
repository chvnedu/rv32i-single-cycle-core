#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include "cpu.h"
#include "alu.h"
#include "decode.h"

void test_instruction(CPU *cpu, uint32_t instruction, uint8_t rd, uint32_t expected) {
    uint32_t previous_pc = cpu->pc;
    bool success = execute_instruction(cpu, instruction);
    assert(success);
    assert(reg_read(cpu, rd) == expected);
    assert(cpu->pc == previous_pc + 4);
}

int main() {
    CPU cpu;
    cpu_reset(&cpu);
    reg_write(&cpu, 1, 10);
    test_instruction(&cpu, 0xFFC08193, 3, 6); //addi x3, x1, -4
    
    reg_write(&cpu, 1, 20);
    reg_write(&cpu, 2, 7);
    test_instruction(&cpu, 0x002081B3, 3, 27); //add x3, x1, x2
    test_instruction(&cpu, 0x402081B3, 3, 13); //sub x3, x1, x2

    reg_write(&cpu, 1, 9); // 1001
    reg_write(&cpu, 2, 5); // 0101

    test_instruction(&cpu, 0x0020f1b3, 3, 1); //and x3, x1, x2
    test_instruction(&cpu, 0x0020e1b3, 3, 13); //or x3, x1, x2
    test_instruction(&cpu, 0x0020c1b3, 3, 12); //xor x3, x1, x2

    printf("All CPU instruction tests passed!\n");
    return 0;
}
