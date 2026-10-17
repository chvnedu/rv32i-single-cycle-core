#include <stdio.h>

#include "cpu.h"

void cpu_reset(CPU *cpu) {
    cpu->pc = 0;
    for(int i = 0; i < 32; i++){
        cpu->registers[i] = 0;
    }
}

uint32_t reg_read(CPU *cpu, uint8_t index) {
    if (index > 0 && index < 32) {
        return cpu->registers[index];
    } else {
        return 0;
    }
}
void reg_write(CPU *cpu, uint8_t index, uint32_t value) {
    if (index > 0 && index < 32) {
        cpu->registers[index] = value;
    } else {
        return;
    }
}

void pc_increment(CPU *cpu) {
    cpu->pc += 4;
}

bool execute_op(CPU *cpu, INSTRUCTION instruction) {
    uint32_t rdata1 = reg_read(cpu, instruction.rs1);
    uint32_t rdata2 = reg_read(cpu, instruction.rs2);
    uint32_t wdata;
    switch(instruction.funct3){
        case 0x0:
            if(instruction.funct7 == 0x0) {
                wdata = alu_add(rdata1, rdata2);
            } else if (instruction.funct7 == 0x20){
                wdata = alu_sub(rdata1, rdata2);
            } else {
                printf("Invalid Instruction: %#X \n", instruction.inst);
                return false;
            }
            break;
        case 0x4:
            if(instruction.funct7 == 0x0) {
                wdata = alu_xor(rdata1, rdata2);
            } else {
                printf("Invalid Instruction: %#X \n", instruction.inst);
                return false;
            }
            break;
        case 0x6:    
            if(instruction.funct7 == 0x0) {
                wdata = alu_or(rdata1, rdata2);
            } else {
                printf("Invalid Instruction: %#X \n", instruction.inst);
                return false;
            }
            break;
        case 0x7:    
            if(instruction.funct7 == 0x0) {
                wdata = alu_and(rdata1, rdata2);
            } else {
                printf("Invalid Instruction: %#X \n", instruction.inst);
                return false;
            }
            break;
        default:
            printf("Invalid Instruction: %#X \n", instruction.inst);
            return false;
    }
    reg_write(cpu, instruction.rd, wdata);
    pc_increment(cpu);
    return true;
}

bool execute_op_imm(CPU *cpu, INSTRUCTION instruction) {
    uint32_t rdata1 = reg_read(cpu, instruction.rs1);
    uint32_t wdata;
    switch(instruction.funct3){
        case 0x0:
            wdata = alu_add(rdata1, sign_extend_12(instruction.imm));
            break;
        default:
            printf("Invalid Instruction: %#X \n", instruction.inst);
            return false;
    }
    reg_write(cpu, instruction.rd, wdata);
    pc_increment(cpu);
    return true;
}

bool execute_instruction(CPU *cpu, uint32_t instruction) {
    INSTRUCTION inst = decode(instruction);
    switch(inst.opcode) {
        case 0x13:
            return execute_op_imm(cpu, inst);
        case 0x33:
            return execute_op(cpu, inst);
        default:
        printf("Invalid Instruction: %#X \n", instruction);
        return false;
    }
}

