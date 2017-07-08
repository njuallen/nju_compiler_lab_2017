#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include "csapp.h"
#include "adt.h"
#include "syntax.h"
#include "semantic.h"
#include "ir.h"
#include "mips32.h"

using std::set;
using std::string;
using std::vector;
using std::list;

// 用来描述一个基本块
// 由于我这里不准备进行全局数据流分析
// 只准备做局部处理
// 所以我这里只要将代码分为基本块并将基本块线性排列即可
struct basic_block {
    // 基本块内的首条指令
    struct ir_code *code;
    list<struct mips32_code *> machine_code;
};

// 一个函数由若干个基本块组成
struct function {
    vector<struct basic_block> basic_blocks;
    char *name;
};

vector<function> functions;

// 函数声明
struct mips32_operand *create_mips32_operand(int kind, ...);
struct mips32_code *create_mips32_code(int kind, int argc, ...);
struct mips32_address *create_mips32_address(char *base, int bias);
void print_mips32_codes(list<mips32_code *> &l, FILE *f);
struct mips32_operand *get_register_operand(struct operand *op, list<struct mips32_code *> &l);

// 将代码分割为基本块的大小
void find_basic_blocks(struct ir_code *code) {
    struct ir_code *head = code;

    // the first step is to remove unused label
    // a label is used only it is a target of a jump

    // find the labels that are used
    set<string> used_labels;
    while(code) {
        switch(code->kind) {
            case IR_GOTO:
                used_labels.insert(string(get_operand_name(code->op[0])));
                break;
            case IR_IF:
                used_labels.insert(string(get_operand_name(code->op[3])));
                break;
            default:
                break;
        }
        code = code->next;
    }

    // remove the labels that are unused
    code = head;
    while(code) {
        if(code->kind == IR_LABEL) {
            std::set<string>::iterator it;
            it = used_labels.find(string(get_operand_name(code->op[0])));
            if(it == used_labels.end()) {
                // delete_code返回的code就是下一条code的地址
                // 因此直接continue
                code = delete_code(code);
                continue;
            }
        }
        code = code->next;
    }

    // 接下来我们再将其分割为函数
    code = head;
    vector<struct ir_code *> function_codes;
    vector<char *> function_names;
    struct ir_code *start = NULL;
    char *function_name = NULL;
    while(code) {
        struct ir_code *next = code->next;
        if(code->kind == IR_FUNCTION) {
            if(start) {
                code->prev->next = NULL;
                function_codes.push_back(start);
                function_names.push_back(function_name);
            }
            start = next;
            function_name = get_operand_name(code->op[0]);
        }
        code = next;
    }
    // 将最后一个函数的指令加入到function_codes中
    if(start) {
        function_codes.push_back(start);
        function_names.push_back(function_name);
    }

    unsigned num_functions = function_codes.size();
    /*
    // 检查函数分割得对不对
    for(unsigned i = 0; i < num_functions; i++) {
        fprintf(stderr, "%s\n", function_names[i]);
        fprintf(stderr, "--------------------\n");
        print_ir_codes(function_codes[i], stderr);
        fprintf(stderr, "\n");
    }
    */

    functions.resize(num_functions);

    // 接着，我们将每个函数分割成基本块的大小
    for(unsigned i = 0; i < num_functions; i++) {
        start = code = function_codes[i];
        struct basic_block curr_block;
        struct function &curr_function = functions[i];
        curr_function.name = function_names[i];
        while(code) {
            struct ir_code *next = code->next;
            switch(code->kind) {
                case IR_IF:
                case IR_GOTO:
                    // 如果遇到的是跳转，要把当前指令算到当前block里面去
                    if(start) {
                        code->next = NULL;
                        curr_block.code = start;
                        curr_function.basic_blocks.push_back(curr_block);
                    }
                    start = next;
                    break;
                case IR_LABEL:
                    // 如果遇到的是label，则当前指令不算到当前block里面去
                    // 我们这个划分，有一个问题，即如果出现了
                    // goto + label这种情况
                    // 则label对应的那个basic block会被我们加进去两次
                    // 所以如果我们上一条指令是跳转类型的，则我们不必在此新建block
                    if(start && (!code->prev || (code->prev->kind != IR_IF
                                    && code->prev->kind != IR_GOTO))) {
                        code->prev->next = NULL;
                        curr_block.code = start;
                        curr_function.basic_blocks.push_back(curr_block);
                    }
                    start = code;
                default:
                    break;
            }
            code = next;
        }
        if(start) {
            curr_block.code = start;
            curr_function.basic_blocks.push_back(curr_block);
        }
    }
}

// 扫描基本块，对每个基本块进行指令选择，但是不进行寄存器分配
void select_instruction() {
    for(unsigned i = 0; i < functions.size(); i++) {
        for(unsigned j = 0; j < functions[i].basic_blocks.size(); j++) {
            struct ir_code *code = functions[i].basic_blocks[j].code;
            list<struct mips32_code *> &l = functions[i].basic_blocks[j].machine_code;
            struct mips32_code *c = NULL;
            struct mips32_operand *op1 = NULL, *op2 = NULL, *op3 = NULL;
            struct mips32_address *addr = NULL;
            int ir_op1_kind, ir_op2_kind;
            // 比较运算符和算术运算符
            char *relop = NULL, *aop = NULL;
            int mips_code_kind;
            while(code) {
                switch(code->kind) {
                    case IR_LABEL:
                        // LABEL x:
                        // translate into
                        // x:
                        op1 = create_mips32_operand(MIPS32_OP_NAME, get_operand_name(code->op[0]));
                        c = create_mips32_code(MIPS32_LABEL, 1, op1);
                        l.push_back(c);
                        break;
                    case IR_ASSIGN:
                        ir_op1_kind = code->op[0]->kind;
                        ir_op2_kind = code->op[1]->kind;
                        if(ir_op1_kind == OP_VARIABLE 
                                && ir_op2_kind == OP_VARIABLE) {
                            // x := y
                            // translate into
                            // move reg(x), reg(y)
                            op1 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[0]));
                            op2 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[1]));
                            c = create_mips32_code(MIPS32_MOVE, 2, op1, op2);
                            l.push_back(c);
                        }
                        else if(ir_op1_kind == OP_VARIABLE 
                                && ir_op2_kind == OP_CONSTANT) {
                            // x := #k
                            // translate into
                            // li reg(x), k
                            op1 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[0]));
                            op2 = create_mips32_operand(MIPS32_OP_IMMEDIATE, code->op[1]->u.value);
                            c = create_mips32_code(MIPS32_LI, 2, op1, op2);
                            l.push_back(c);
                        }
                        else if(ir_op1_kind == OP_VARIABLE 
                                && ir_op2_kind == OP_ADDRESS) {
                            // load
                            // x := *y
                            // translate into
                            // lw reg(x), 0(reg(y))
                            op1 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[0]));
                            // bias is 0
                            addr = create_mips32_address(Asprintf("t%d", code->op[1]->u.var_no), 0);
                            op2 = create_mips32_operand(MIPS32_OP_ADDRESS, addr);
                            c = create_mips32_code(MIPS32_LW, 2, op1, op2);
                            l.push_back(c);
                        }
                        else if(ir_op1_kind == OP_ADDRESS) {
                            // store
                            // *x = y 
                            // translate into
                            // sw reg(y), 0(reg(x))
                            op1 = get_register_operand(code->op[1], l);
                            // bias is 0
                            addr = create_mips32_address(Asprintf("t%d", code->op[0]->u.var_no), 0);
                            op2 = create_mips32_operand(MIPS32_OP_ADDRESS, addr);
                            c = create_mips32_code(MIPS32_SW, 2, op1, op2);
                            l.push_back(c);
                        }
                        else
                            app_error(Asprintf("Line %d: Invalid operand", __LINE__));
                        break;
                    case IR_ARITHMETIC:
                        // op[0] = op[1] op[2](operator) op[3]
                        aop = get_operand_name(code->op[2]);
                        ir_op1_kind = code->op[1]->kind;
                        ir_op2_kind = code->op[3]->kind;
                        if(!strcmp(aop, "+")) {
                            /*
                               if(ir_op1_kind == OP_VARIABLE 
                               && ir_op2_kind == OP_VARIABLE) {
                            // x := y + z
                            // translate into
                            // add reg(x), reg(y), reg(z)
                            op1 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[0]));
                            op2 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[1]));
                            op3 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[3]));
                            c = create_mips32_code(MIPS32_ADD, 3, op1, op2, op3);
                            l.push_back(c);
                            }
                            else if(ir_op1_kind == OP_VARIABLE 
                            && ir_op2_kind == OP_CONSTANT) {
                            // x := y + #k
                            // translate into
                            // addi reg(x), reg(y), k
                            op1 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[0]));
                            op2 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[1]));
                            op3 = create_mips32_operand(MIPS32_OP_IMMEDIATE, code->op[3]->u.value);
                            c = create_mips32_code(MIPS32_ADDI, 3, op1, op2, op3);
                            l.push_back(c);
                            }
                            else
                            app_error("Invalid operand");
                            */
                            op1 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[0]));
                            op2 = get_register_operand(code->op[1], l);
                            op3 = get_register_operand(code->op[3], l);
                            c = create_mips32_code(MIPS32_ADD, 3, op1, op2, op3);
                            l.push_back(c);
                        }
                        else if(!strcmp(aop, "-")) {
                            /*
                               if(ir_op1_kind == OP_VARIABLE 
                               && ir_op2_kind == OP_VARIABLE) {
                            // x := y - z
                            // translate into
                            // sub reg(x), reg(y), reg(z)
                            op1 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[0]));
                            op2 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[1]));
                            op3 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[3]));
                            c = create_mips32_code(MIPS32_SUB, 3, op1, op2, op3);
                            l.push_back(c);
                            }
                            else if(ir_op1_kind == OP_VARIABLE 
                            && ir_op2_kind == OP_CONSTANT) {
                            // x := y - #k
                            // translate into
                            // addi reg(x), reg(y), -k
                            op1 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[0]));
                            op2 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[1]));
                            op3 = create_mips32_operand(MIPS32_OP_IMMEDIATE, -code->op[3]->u.value);
                            c = create_mips32_code(MIPS32_ADDI, 3, op1, op2, op3);
                            l.push_back(c);
                            }
                            else
                            app_error("Invalid operand");
                            */
                            op1 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[0]));
                            op2 = get_register_operand(code->op[1], l);
                            op3 = get_register_operand(code->op[3], l);
                            c = create_mips32_code(MIPS32_SUB, 3, op1, op2, op3);
                            l.push_back(c);
                        }
                        else if(!strcmp(aop, "*")) {
                            // x := y * z
                            // translate into
                            // mul reg(x), reg(y), reg(z)
                            op1 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[0]));
                            op2 = get_register_operand(code->op[1], l);
                            op3 = get_register_operand(code->op[3], l);
                            c = create_mips32_code(MIPS32_MUL, 3, op1, op2, op3);
                            l.push_back(c);
                        }
                        else if(!strcmp(aop, "/")) {
                            // x := y / z
                            // translate into
                            // div reg(y), reg(z)
                            // mflo reg(x)
                            op1 = get_register_operand(code->op[1], l);
                            op2 = get_register_operand(code->op[3], l);
                            c = create_mips32_code(MIPS32_DIV, 2, op1, op2);
                            l.push_back(c);
                            op1 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[0]));
                            c = create_mips32_code(MIPS32_MFLO, 1, op1);
                            l.push_back(c);
                        }
                        else
                            app_error("Invalid arithmetic operator");
                        break;
                    case IR_GOTO:
                        // GOTO x
                        // translate into
                        // j x
                        op1 = create_mips32_operand(MIPS32_OP_NAME, get_operand_name(code->op[0]));
                        c = create_mips32_code(MIPS32_J, 1, op1);
                        l.push_back(c);
                        break;
                    case IR_IF:
                        // IF x relop y GOTO z
                        // translate into
                        // opcode reg(x) reg(y) z
                        op1 = get_register_operand(code->op[0], l);
                        op2 = get_register_operand(code->op[2], l);
                        op3 = create_mips32_operand(MIPS32_OP_NAME, get_operand_name(code->op[3]));
                        relop = get_operand_name(code->op[1]);
                        if(!strcmp(relop, "=="))
                            mips_code_kind = MIPS32_BEQ;
                        else if(!strcmp(relop, "!="))
                            mips_code_kind = MIPS32_BNE;
                        else if(!strcmp(relop, ">"))
                            mips_code_kind = MIPS32_BGT;
                        else if(!strcmp(relop, "<"))
                            mips_code_kind = MIPS32_BLT;
                        else if(!strcmp(relop, ">="))
                            mips_code_kind = MIPS32_BGE;
                        else if(!strcmp(relop, "<="))
                            mips_code_kind = MIPS32_BLE;
                        else
                            app_error("Invalid relational operand");
                        c = create_mips32_code(mips_code_kind, 3, op1, op2, op3);
                        l.push_back(c);
                        break;
                    case IR_RETURN:
                        // RETURN x
                        // translate into
                        // move $v0, reg(x)
                        // jr $ra
                        // save return value in $v0
                        op1 = create_mips32_operand(MIPS32_OP_REGISTER, "$v0");
                        if(code->op[0]->kind == OP_VARIABLE) {
                            op2 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[0]));
                            c = create_mips32_code(MIPS32_MOVE, 2, op1, op2);
                        }
                        else if(code->op[0]->kind == OP_CONSTANT) {
                            op2 = create_mips32_operand(MIPS32_OP_IMMEDIATE, code->op[0]->u.value);
                            c = create_mips32_code(MIPS32_LI, 2, op1, op2);
                        }
                        else
                            app_error(Asprintf("Line %d: Invalid operand", __LINE__));
                        l.push_back(c);

                        // jump back
                        op1 = create_mips32_operand(MIPS32_OP_REGISTER, "$ra");
                        c = create_mips32_code(MIPS32_JR, 1, op1);
                        l.push_back(c);
                        break;
                    case IR_DEC:
                        break;
                    case IR_ARG:
                        break;
                    case IR_CALL:
                        // x := CALL f
                        // translate into
                        // jal f
                        // move reg(x), $v0
                        op1 = create_mips32_operand(MIPS32_OP_NAME, get_operand_name(code->op[1]));
                        c = create_mips32_code(MIPS32_JAL, 1, op1);
                        l.push_back(c);
                        op1 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(code->op[0]));
                        op2 = create_mips32_operand(MIPS32_OP_REGISTER, "$v0");
                        c = create_mips32_code(MIPS32_MOVE, 2, op1, op2);
                        l.push_back(c);
                        break;
                    case IR_PARAM:
                        break;
                    case IR_READ:
                        break;
                    case IR_WRITE:
                        break;
                    default:
                        break;
                }
                code = code->next;
            }
        }
    }
}

// given a immediate/register operand, return a register operand
// the li code is generated for immediate operand
struct mips32_operand *get_register_operand(struct operand *op, list<struct mips32_code *> &l) {
    if(op->kind == OP_CONSTANT) {
        extern int var_no_counter;
        // create a new virtual register to hold the value
        struct operand *reg = create_operand(OP_VARIABLE, var_no_counter++);
        struct mips32_operand *op1 = create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(reg));
        struct mips32_operand *op2 = create_mips32_operand(MIPS32_OP_IMMEDIATE, op->u.value);
        struct mips32_code *c = create_mips32_code(MIPS32_LI, 2, op1, op2);
        l.push_back(c);
        return op1;
    }
    else if(op->kind == OP_VARIABLE) {
        return create_mips32_operand(MIPS32_OP_REGISTER, get_operand_name(op));
    }
    else if(op->kind == OP_GET_ADDRESS) {
        // 取数组首地址
        // DEC t2 8
        // 则我们在实现时，是不允许再向t2这个virtal register复制
        // 这个virtual register里面装的值就是数组的首地址
        return create_mips32_operand(MIPS32_OP_REGISTER, Asprintf("t%d", op->u.var_no));
    }
    else {
        app_error(Asprintf("Line %d: Invalid operand", __LINE__));
        return NULL;
    }
}

LINKAGE void mips32_codegen(struct ir_code *code, FILE *f) {
    print_ir_codes(code, f);
    // the first step is to find basic block
    find_basic_blocks(code);
    // 输出分块后的指令
    FILE *tmp = Fopen("1.ir", "w");
    for(unsigned i = 0; i < functions.size(); i++) {
        fprintf(tmp, "*************************\n");
        for(unsigned j = 0; j < functions[i].basic_blocks.size(); j++) {
            ;
            fprintf(tmp, "-------------------------\n");
            print_ir_codes(functions[i].basic_blocks[j].code, tmp);
        }
    }
    select_instruction();
    // 输出选择的指令
    for(unsigned i = 0; i < functions.size(); i++) {
        fprintf(stderr, "*************************\n");
        for(unsigned j = 0; j < functions[i].basic_blocks.size(); j++) {
            list<struct mips32_code *> &l = functions[i].basic_blocks[j].machine_code;
            fprintf(stderr, "-------------------------\n");
            print_mips32_codes(l, stderr);
        }
    }
}


struct mips32_address *create_mips32_address(char *base, int bias) {
    struct mips32_address *addr = (struct mips32_address *)Calloc(1, sizeof(struct mips32_address));
    addr->base_register = Strdup(base);
    addr->bias = bias;
    return addr;
}

struct mips32_operand *create_mips32_operand(int kind, ...) {
    struct mips32_operand *op = (struct mips32_operand *)Calloc(1, sizeof(struct mips32_operand));
    op->kind = kind;
    va_list args;
    va_start(args, kind);
    switch(kind) {
        case MIPS32_OP_IMMEDIATE:
            op->u.immediate = va_arg(args, int);
            break;
        case MIPS32_OP_REGISTER:
        case MIPS32_OP_NAME:
            op->u.name = Strdup(va_arg(args, char *));
            break;
        case MIPS32_OP_ADDRESS:
            op->u.addr = va_arg(args, mips32_address *);
            break;
        default:
            app_error("No such kind of operand");
            break;
    }
    va_end(args);
    return op;
}

struct mips32_code *create_mips32_code(int kind, int argc, ...) {
    struct mips32_code *code = (struct mips32_code *)Calloc(1, sizeof(struct mips32_code));
    code->kind = kind;
    if(argc > MIPS32_MAX_OPERAND)
        app_error("Too much operand for MIPS32 code");
    va_list args;
    va_start(args, argc);
    for(int i = 0; i < argc; i++)
        code->op[i] = va_arg(args, struct mips32_operand *);
    va_end(args);
    return code;
}

char *get_mips32_operand_name(struct mips32_operand *op) {
    if(op) {
        switch(op->kind) {
            case MIPS32_OP_IMMEDIATE:
                return Asprintf("%d", op->u.immediate);
                break;
            case MIPS32_OP_REGISTER:
            case MIPS32_OP_NAME:
                return Asprintf("%s", op->u.name);
                break;
            case MIPS32_OP_ADDRESS:
                return Asprintf("%d(%s)", op->u.addr->bias, op->u.addr->base_register);
                break;
            default:
                app_error("Unknown type of operand");
                return NULL;
                break;
        }
    }
    else
        return NULL;
}

const char *mips32_code_fmt[] = {
    "%s:", "li %s, %s", "move %s, %s", 
    "addi %s, %s, %s", "add %s, %s, %s", "sub %s, %s, %s",
    "mul %s, %s, %s", "div %s, %s", "mflo %s",
    "lw %s, %s", "sw %s, %s", "j %s",
    "jal %s", "jr %s", "beq %s, %s, %s",
    "bne %s, %s, %s", "bgt %s, %s, %s", "blt %s, %s, %s", 
    "bge %s, %s, %s", "ble %s, %s, %s" 
};

void print_mips32_code(struct mips32_code *code, FILE *f);

void print_mips32_codes(list<mips32_code *> &l, FILE *f) {
    list<mips32_code *>::iterator it;
    for(it = l.begin(); it != l.end(); it++)
        print_mips32_code(*it, f);
}

void print_mips32_code(struct mips32_code *code, FILE *f) {
    fprintf(f, mips32_code_fmt[code->kind], get_mips32_operand_name(code->op[0]), 
            get_mips32_operand_name(code->op[1]), get_mips32_operand_name(code->op[2]));
    fprintf(f, "\n");
}
