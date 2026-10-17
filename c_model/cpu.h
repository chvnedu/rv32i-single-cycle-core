#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

#include "decode.h"
#include "alu.h"

typedef struct {
    uint32_t pc;
    uint32_t registers[32];
} CPU;

//Initiliaze CPU Registers
void cpu_reset(CPU *cpu);

//Write and Read Values to Registers
uint32_t reg_read(CPU *cpu, uint8_t index);
void reg_write(CPU *cpu, uint8_t index, uint32_t value);

//Increment program counter
void pc_increment(CPU *cpu);

bool execute_instruction(CPU *cpu, uint32_t instruction);
bool execute_op(CPU *cpu, INSTRUCTION instruction);
bool execute_op_imm(CPU *cpu, INSTRUCTION instruction);

#endif