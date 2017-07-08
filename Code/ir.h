#ifndef IR_H
#define IR_H
#include <stdio.h>
#include "linkage.h"

#define MAX_OPERAND 4

// give this enumerators a OP_ prefix 
// so that they won't clash with enumerators from syntax***
// OP_NAME means this operand is a label/function name
// OP_VARIABLE, OP_ADDRESS -> var_no
// OP_CONSTANT -> value
// OP_NAME -> name
enum { OP_VARIABLE, OP_CONSTANT, OP_ADDRESS, OP_GET_ADDRESS, OP_NAME};

struct operand {
    int kind;
    union {
        int var_no;
        int value;
        char *name;
    } u;
};

enum {
    IR_LABEL = 0, IR_FUNCTION, IR_ASSIGN,
    IR_ARITHMETIC, IR_GOTO, IR_IF, 
    IR_RETURN, IR_DEC, IR_ARG, 
    IR_CALL, IR_PARAM, IR_READ, 
    IR_WRITE
};

struct ir_code {
    int kind;
    // we will have up to three operands
    // some may not be used
    struct operand *op[MAX_OPERAND];
    struct ir_code *prev, *next;
};

LINKAGE struct ir_code *generate_ir(struct syntax_node *root);
LINKAGE void print_ir_code(struct ir_code *code, FILE *f);
LINKAGE void print_ir_codes(struct ir_code *code, FILE *f);
LINKAGE struct ir_code *delete_code(struct ir_code *code);
LINKAGE char *get_operand_name(struct operand *op);
LINKAGE struct operand *create_operand(int kind, ...);
#endif
