#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct {
    uint32_t pc;
    uint32_t registers[32];
} CPU;

void cpu_reset(CPU *CPU);

#endif