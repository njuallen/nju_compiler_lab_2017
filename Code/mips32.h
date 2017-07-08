#ifndef MIPS32_H
#define MIPS32_H
#include <stdio.h>
#include "linkage.h"
#include "ir.h"

enum { MIPS32_OP_REGISTER, MIPS32_OP_IMMEDIATE, MIPS32_OP_NAME, MIPS32_OP_ADDRESS};

struct mips32_address {
    // 寄存器名
    char *base_register;
    int bias;
};

struct mips32_operand {
    int kind;
    union {
        int immediate;
        // 寄存器名/label
        char *name;
        struct mips32_address *addr;
    } u;
};

enum {
    MIPS32_LABEL = 0, MIPS32_LI, MIPS32_MOVE,
    MIPS32_ADDI, MIPS32_ADD, MIPS32_SUB,
    MIPS32_MUL, MIPS32_DIV, MIPS32_MFLO,
    MIPS32_LW, MIPS32_SW, MIPS32_J,
    MIPS32_JAL, MIPS32_JR, MIPS32_BEQ,
    MIPS32_BNE, MIPS32_BGT, MIPS32_BLT,
    MIPS32_BGE, MIPS32_BLE
};

#define MIPS32_MAX_OPERAND 3
struct mips32_code {
    int kind;
    // we will have up to three operands
    // some may not be used
    struct mips32_operand *op[MIPS32_MAX_OPERAND];
};

struct mips32_variable_descriptor {
    // 由于我们在这里不打算支持全局变量
    // 所以数据我们全都放在栈上
    // 那这个地址就是相对于当前栈的base pointer的偏移量
    int mem_addr;
};

LINKAGE void mips32_codegen(struct ir_code *code, FILE *f);
#endif
