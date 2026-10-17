#include "alu.h"

uint32_t alu_add(uint32_t a, uint32_t b) {
    return a + b;
}
uint32_t alu_sub(uint32_t a, uint32_t b) {
    return a - b;
}
uint32_t alu_and(uint32_t a, uint32_t b){
    return a & b;
}
uint32_t alu_or(uint32_t a, uint32_t b){
    return a | b;
}
uint32_t alu_xor(uint32_t a, uint32_t b){
    return a ^ b;
}