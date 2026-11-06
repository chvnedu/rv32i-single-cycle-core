#include "memory.h"
#include <stddef.h>
bool instruction_fetch(InstructionMemory *im, uint32_t pc, uint32_t *instruction) {
    uint32_t index = pc/4;

    if (im == NULL || instruction == NULL) {
        return false;
    }
    
    if(index < INSTRUCTION_MEMORY_SIZE && pc % 4 == 0 ) {
        *instruction = im->inst[index];
        return true;
    } else {
        return false;
    }
}