#include "decode.h"

INSTRUCTION decode(uint32_t instruction){
    INSTRUCTION decoded;
    decoded.inst = instruction;
    decoded.opcode = instruction & 0x7F;
    decoded.rd = (instruction >> 7) & 0x1F;
    decoded.funct3 = (instruction >> 12) & 0x7;
    decoded.rs1 = (instruction >> 15) & 0x1F;
    decoded.rs2 = (instruction >> 20) & 0x1F;
    decoded.funct7 = (instruction >> 25) & 0x7F;
    decoded.imm = (instruction >> 20) & 0xFFF;
    return decoded;
}

uint32_t sign_extend_12(uint16_t imm) {
    uint16_t lowest_bits = imm & 0xFFF;
    if(lowest_bits & 0x800) {
        return (lowest_bits) | 0xFFFFF000;
    } else {
        return lowest_bits;
    }
}