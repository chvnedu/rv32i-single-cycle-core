#include <stdio.h>
#include <inttypes.h>
#include "cpu.h"
#include "decode.h"
#include "alu.h"
#include "memory.h"

int main(){
    CPU cpu;
    cpu_reset(&cpu);
    InstructionMemory memory = {0};
    memory.inst[0] = 0x00A00093;
    memory.inst[1] = 0x01400113;
    memory.inst[2] = 0x002081B3;


    for (int i = 0; i <3; i++) {
    if (cpu_step(&cpu, &memory)) {
        printf("Result %d: %" PRIu32"\n", i+1, reg_read(&cpu, i+1));
        }else {
            printf("CPU Step Failed");
            break;
        }    
    }
    printf("Final PC: %" PRIu32 "\n", cpu.pc);
}