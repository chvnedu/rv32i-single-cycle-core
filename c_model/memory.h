#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdbool.h>

#define INSTRUCTION_MEMORY_SIZE 256

typedef struct {
    uint32_t inst[INSTRUCTION_MEMORY_SIZE];
} InstructionMemory;

bool instruction_fetch(InstructionMemory *im, uint32_t pc, uint32_t *instruction);
#endif