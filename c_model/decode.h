#ifndef DECODE_H
#define DECODE_H

#include <stdint.h>

typedef struct {
    uint32_t inst;
    uint8_t opcode;
    uint8_t rd;
    uint8_t funct3;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t funct7;
    uint16_t imm;
} INSTRUCTION;

INSTRUCTION decode(uint32_t instruction);
uint32_t sign_extend_12(uint16_t imm);

#endif