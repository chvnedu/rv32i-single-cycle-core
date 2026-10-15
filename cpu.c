#include "cpu.h"

int main(){
    CPU cpu;
    cpu.pc = 0;

    for(int i = 0; i < 32; i++){
        cpu->registers[i] = 0;
    }
    void cpu_reset(CPU *cpu) {
        cpu->pc = 0;
    }
}
