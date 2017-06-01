#ifndef IR_H
#define IR_H

#define MAX_OPERAND 3

// give this enumerators a OP_ prefix 
// so that they won't clash with enumerators from syntax***
// OP_NAME means this operand is a label/function name
// OP_VARIABLE, OP_ADDRESS -> var_no
// OP_CONSTANT -> value
// OP_NAME -> name
struct operand {
    enum { OP_VARIABLE, OP_CONSTANT, OP_ADDRESS, OP_NAME} kind;
    union {
        int var_no;
        int value;
        char *name;
    } u;
};

struct ir_code {
    enum { 
        IR_LABEL, IR_FUNCTION, IR_ASSIGN,
        IR_ADD, IR_SUB, IR_MUL, IR_DIV, 
        IR_ADDRESS, IR_LOAD, IR_STORE, 
        IR_GOTO, IR_IF, IR_RETURN, IR_DEC,
        IR_ARG, IR_CALL, IR_PARAM,
        IR_READ, IR_WRITE
    } kind;
    // we will have up to three operands
    // some may not be used
    struct operand *op[MAX_OPERAND];
    struct ir_code *prev, *next;
};

void generate_ir(struct syntax_node *root);
#endif
