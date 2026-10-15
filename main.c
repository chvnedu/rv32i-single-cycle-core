#include <stdio.h>
#include <inttypes.h>
#include "cpu.h"

int main(){
    CPU cpu;
    cpu.pc = 0;
    cpu_reset(&cpu);
    printf("%" PRIu32, cpu.pc);
    printf("%" PRIu32, cpu.registers[1]);
    return 0;
}