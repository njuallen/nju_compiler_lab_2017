#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <utility>
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
using std::map;

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
    list<mips32_code *> prologue;
};

vector<function> functions;

// 函数声明
struct mips32_operand *create_mips32_operand(int kind, ...);
struct mips32_code *create_mips32_code(int kind, int argc, ...);
struct mips32_address *create_mips32_address(char *base, int bias);
void print_mips32_codes(list<mips32_code *> &l, FILE *f);
struct mips32_operand *get_register_operand(struct operand *op, list<struct mips32_code *> &l);
struct mips32_operand *ensure(struct mips32_operand *op, 
        list<mips32_code *> &l,
        list<mips32_code *>::iterator &it, int modified);
void print_variable_descritors(FILE *f);
void print_register_descriptors(FILE *f);
void push_register(char *reg_name, 
        list<mips32_code *> &l,
        list<mips32_code *>::iterator &it);
void pop_register(char *reg_name, 
        list<mips32_code *> &l,
        list<mips32_code *>::iterator &it);
struct mips32_code *move(char *reg_src, char *reg_dst);
void load(char *variable, char *reg_name,
        list<mips32_code *> &l,
        list<mips32_code *>::iterator &it);
void free_register(struct mips32_register_descriptor *r, 
        list<mips32_code *> &l,
        list<mips32_code *>::iterator &it);

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

// 我感觉使用map让我这个写起来变得繁琐了！
list<struct mips32_register_descriptor *> used_registers;
list<struct mips32_register_descriptor *> unused_registers;
map<string, struct mips32_variable_descriptor *> variables;
vector<char *> callee_saved_registers;
vector<char *> callee_saved_variables;

list<mips32_code *> prologue(char *name) {
    list<mips32_code *> l;
    struct mips32_operand *op1 = create_mips32_operand(MIPS32_OP_NAME, name);
    struct mips32_code *c = create_mips32_code(MIPS32_LABEL, 1, op1);
    l.push_back(c);
    auto it = l.end();
    push_register("$ra", l, it);
    push_register("$fp", l, it);
    l.push_back(move("$sp", "$fp"));
    return l;
}

void epilogue(list<mips32_code *> &l,
        list<mips32_code *>::iterator &it) {
    // 我们需要将callee saved register给恢复回去！
    for(auto i = 0; i < callee_saved_variables.size(); i++)
        load(callee_saved_variables[i], callee_saved_registers[i], l, it);
    it = l.insert(it, move("$fp", "$sp"));
    it++;
    pop_register("$fp", l, it);
    pop_register("$ra", l, it);
}


struct mips32_code *move(char *reg_src, char *reg_dst) {
    struct mips32_operand *op1 = create_mips32_operand(MIPS32_OP_REGISTER, reg_src);
    struct mips32_operand *op2 = create_mips32_operand(MIPS32_OP_REGISTER, reg_dst);
    struct mips32_code *c = create_mips32_code(MIPS32_MOVE, 2, op2, op1);
    return c;
}

void push_register(char *reg_name, 
        list<mips32_code *> &l,
        list<mips32_code *>::iterator &it) {

    // addi $sp, $sp, -4
    struct mips32_operand *op1 = create_mips32_operand(MIPS32_OP_REGISTER, "$sp");
    struct mips32_operand *op2 = create_mips32_operand(MIPS32_OP_REGISTER, "$sp");
    struct mips32_operand *op3 = create_mips32_operand(MIPS32_OP_IMMEDIATE, -4);
    struct mips32_code *c = create_mips32_code(MIPS32_ADDI, 3, op1, op2, op3);
    it = l.insert(it, c);
    it++;

    // sw reg, 0($sp)
    op1 = create_mips32_operand(MIPS32_OP_REGISTER, reg_name);
    // bias is 0
    struct mips32_address *addr = create_mips32_address("$sp", 0);
    op2 = create_mips32_operand(MIPS32_OP_ADDRESS, addr);
    c = create_mips32_code(MIPS32_SW, 2, op1, op2);
    it = l.insert(it, c);
    it++;
}

void pop_register(char *reg_name, 
        list<mips32_code *> &l,
        list<mips32_code *>::iterator &it) {
    // lw reg, 0($sp)
    struct mips32_operand *op1 = create_mips32_operand(MIPS32_OP_REGISTER, reg_name);
    // bias is 0
    struct mips32_address *addr = create_mips32_address("$sp", 0);
    struct mips32_operand *op2 = create_mips32_operand(MIPS32_OP_ADDRESS, addr);
    struct mips32_code *c = create_mips32_code(MIPS32_LW, 2, op1, op2);
    it = l.insert(it, c);
    it++;

    // addi $sp, $sp, -4
    op1 = create_mips32_operand(MIPS32_OP_REGISTER, "$sp");
    op2 = create_mips32_operand(MIPS32_OP_REGISTER, "$sp");
    struct mips32_operand *op3 = create_mips32_operand(MIPS32_OP_IMMEDIATE, 4);
    c = create_mips32_code(MIPS32_ADDI, 3, op1, op2, op3);
    it = l.insert(it, c);
    it++;
}

int stack_top = 0;

void init_descriptors() {
    used_registers.clear();
    unused_registers.clear();
    variables.clear();
    callee_saved_registers.clear();
    callee_saved_variables.clear();
    stack_top = 0;

    // 由于所有寄存器都是callee saved，所以刚开始所有寄存器都无法使用
    // 主要是t0-t9 s0-s7
    char *variable_name = NULL, *reg_name = NULL;
    struct mips32_variable_descriptor *v = NULL;
    struct mips32_register_descriptor *reg = NULL;
    /*
       for(int i = 0; i <= 9; i++) {
       reg_name = Asprintf("$t%d", i);
       variable_name = Asprintf("saved_%s", reg_name);
       v.mem_addr = NULL;
       v.reg = reg_name;
       saved_registers[variable_name] = v;
       reg.modified = 0;
       reg.variable = NULL;
    // reg.variable = variable_name;
    unused_registers[reg_name] = reg;
    }
    */
    for(int i = 0; i <= 2; i++) {
        reg_name = Asprintf("$s%d", i);
        variable_name = Asprintf("saved_%s", reg_name);
        v = 
            (struct mips32_variable_descriptor *)
            Calloc(1, sizeof(struct mips32_variable_descriptor));
        reg = 
            (struct mips32_register_descriptor *)
            Calloc(1, sizeof(struct mips32_register_descriptor));
        v->name = variable_name;
        v->mem_addr = NULL;
        v->reg = reg;
        variables[variable_name] = v;
        reg->modified = 1;
        reg->name = Asprintf("$s%d", i);
        reg->variable = v;
        used_registers.push_back(reg);
        callee_saved_registers.push_back(reg_name);
        callee_saved_variables.push_back(variable_name);
    }
}


// 所有variable都是以t开头
// 所有register都是以$开头
bool is_variable(char *s) {
    return s[0] == 't';
}

// 将在这个函数内发生变化的寄存器的值重新存回内存
// 即将所有使用过的寄存器全部刷回内存中去
void flush_used_register(list<mips32_code *> &l,
        list<mips32_code *>::iterator &it) {
    while(!used_registers.empty()) {
        // 将第一个取出来，并将其spill
        struct mips32_register_descriptor *r = used_registers.front();
        used_registers.pop_front();
        free_register(r, l, it);
    }
}

void register_allocation() {
    for(unsigned i = 0; i < functions.size(); i++) {
        // 处理每个函数
        init_descriptors();
        functions[i].prologue = prologue(functions[i].name);
        for(unsigned j = 0; j < functions[i].basic_blocks.size(); j++) {
            list<struct mips32_code *> &l = functions[i].basic_blocks[j].machine_code;
            list<struct mips32_code *>::iterator it;
            bool flushed = false;
            for(it = l.begin(); it != l.end(); it++) {
                struct mips32_code *code = *it;
                struct mips32_operand *op1 = NULL;
                switch(code->kind) {
                    case MIPS32_LI:
                    case MIPS32_MFLO:
                        code->op[0] = ensure(code->op[0], l, it, 1);
                        break;
                    case MIPS32_MOVE:
                    case MIPS32_ADDI:
                        code->op[0] = ensure(code->op[0], l, it, 1);
                        code->op[1] = ensure(code->op[1], l, it, -1);
                        break;
                    case MIPS32_DIV:
                        code->op[0] = ensure(code->op[0], l, it, -1);
                        code->op[1] = ensure(code->op[1], l, it, -1);
                        break;
                    case MIPS32_BEQ:
                    case MIPS32_BNE:
                    case MIPS32_BGT:
                    case MIPS32_BLT:
                    case MIPS32_BGE:
                    case MIPS32_BLE:
                        flushed = true;
                        flush_used_register(l, it);
                        code->op[0] = ensure(code->op[0], l, it, -1);
                        code->op[1] = ensure(code->op[1], l, it, -1);
                        break;
                    case MIPS32_ADD:
                    case MIPS32_SUB:
                    case MIPS32_MUL:
                        code->op[0] = ensure(code->op[0], l, it, 1);
                        code->op[1] = ensure(code->op[1], l, it, -1);
                        code->op[2] = ensure(code->op[2], l, it, -1);
                        break;
                    case MIPS32_LW:
                        code->op[0] = ensure(code->op[0], l, it, 1);
                        op1 = create_mips32_operand(MIPS32_OP_REGISTER, code->op[1]->u.addr->base_register);
                        op1 = ensure(op1, l, it, -1);
                        code->op[1]->u.addr->base_register = op1->u.name;
                    case MIPS32_SW:
                        code->op[0] = ensure(code->op[0], l, it, 0);
                        op1 = create_mips32_operand(MIPS32_OP_REGISTER, code->op[1]->u.addr->base_register);
                        op1 = ensure(op1, l, it, -1);
                        code->op[1]->u.addr->base_register = op1->u.name;
                        break;
                    case MIPS32_JR:
                        // 在return之前必须要加上epilogue
                        flushed = true;
                        flush_used_register(l, it);

                        epilogue(l, it);
                        break;
                    case MIPS32_J:
                        flushed = true;
                        flush_used_register(l, it);
                        break;
                    default:
                        break;
                }
            fprintf(stdout, "***************\n");
            print_variable_descritors(stdout);
            fprintf(stdout, "***************\n");
            print_register_descriptors(stdout);
            }
            if(!flushed)
                flush_used_register(l, it);
            fprintf(stdout, "***************\n");
            print_variable_descritors(stdout);
            fprintf(stdout, "***************\n");
            print_register_descriptors(stdout);
        }
    }
}

void print_variable_descritor(struct mips32_variable_descriptor *v, FILE *f) {
    if(v->reg)
        fprintf(f, "\t%s", v->reg->name);
    else
        fprintf(f, "\tnull");
    if(v->mem_addr)
        fprintf(f, "\t%d(%s)\n", v->mem_addr->bias, v->mem_addr->base_register);
    else
        fprintf(f, "\tnull\n");
}

void print_variable_descritors(FILE *f) {
    for(auto it = variables.begin(); it != variables.end(); it++) {
        fprintf(f, "%s", it->first.c_str());
        print_variable_descritor(it->second, f);
    }
}

void print_register_descriptor(struct mips32_register_descriptor *r, FILE *f) {
    fprintf(f, "%s", r->name);
    if(r->variable)
        fprintf(f, "\t%s", r->variable->name);
    else
        fprintf(f, "\tnull");
    fprintf(f, "\t%d\n", r->modified);
}

void print_register_descriptors(FILE *f) {
    fprintf(f, "used\n");
    for(auto it = used_registers.begin(); it != used_registers.end(); it++) {
        print_register_descriptor(*it, f);
    }
    fprintf(f, "unused\n");
    for(auto it = unused_registers.begin(); it != unused_registers.end(); it++) {
        print_register_descriptor(*it, f);
    }
}

struct mips32_register_descriptor *allocate(char *name, 
        list<mips32_code *> &l,
        list<mips32_code *>::iterator &it);


// 将变量load到指定的寄存器中去
// 这主要是用于callee saved register的恢复
void load(char *variable, char *reg_name,
        list<mips32_code *> &l,
        list<mips32_code *>::iterator &it) {
    bool found = false;
    struct mips32_register_descriptor *r = NULL;
    struct mips32_variable_descriptor *v = variables[variable];
    // 先从正在使用的寄存器中寻找
    for(auto iter = used_registers.begin(); 
            iter != used_registers.end(); iter++) {
        r = *iter;
        if(!strcmp(reg_name, r->name)) {
            found = true;
            if(!strcmp(r->variable->name, variable))
                // already loaded
                return;
            else {
                used_registers.erase(iter);
                free_register(r, l, it);
                break;
            }
        }
    }
    if(!found) {
        for(auto iter = unused_registers.begin(); 
                iter != unused_registers.end(); iter++) {
            r = *iter;
            if(!strcmp(reg_name, r->name)) {
                found = true;
                break;
            }
        }
    }

    // 将它load进去
    struct mips32_operand *op1 = create_mips32_operand(MIPS32_OP_REGISTER, reg_name);
    struct mips32_operand *op2 = create_mips32_operand(MIPS32_OP_ADDRESS, v->mem_addr);
    struct mips32_code *c = create_mips32_code(MIPS32_LW, 2, op1, op2);
    it = l.insert(it, c);
    it++;
    r->modified = 0;
    r->variable = v;
    v->reg = r;
    used_registers.push_back(r);
}

// Ensure(x):
// if (x is already in register r)
//     result = r
// else
//     result = Allocate(x)
//     emit MIPS32 code [lw result, x]
// return result
struct mips32_operand *ensure(struct mips32_operand *op, 
        list<mips32_code *> &l,
        list<mips32_code *>::iterator &it, int modified) {
    char *name = op->u.name;
    struct mips32_operand *op1 = NULL, *op2 = NULL;
    struct mips32_code *c;
    struct mips32_variable_descriptor *v = NULL;
    struct mips32_register_descriptor *r = NULL;
    if(is_variable(name)) {
        // 这个变量是mips32寄存器还是一个尚未分配寄存器的变量？
        if(!variables[name]) {
            variables[name] = (struct mips32_variable_descriptor *)
                Calloc(1, sizeof(struct mips32_variable_descriptor));
            variables[name]->name = Strdup(name);
        }
        v = variables[name];
        if(!v->reg) {
            // 尚未分配寄存器
            r = allocate(name, l, it);
            if(v->mem_addr) {
                // 这个变量之前被spill过
                // 所以在内存中有值
                // 我们先把这个值给load进寄存器中
                // load it
                op1 = create_mips32_operand(MIPS32_OP_REGISTER, r->name);
                op2 = create_mips32_operand(MIPS32_OP_ADDRESS, v->mem_addr);
                c = create_mips32_code(MIPS32_LW, 2, op1, op2);
                it = l.insert(it, c);
                it++;
            }
        }
        else
            r = v->reg;
        op->u.name = r->name;
        if(modified >= 0)
            r->modified = modified;
    }
    return op;
}

// 在stack上分配出size的大小的空间，并返回空间的地址
struct mips32_address *allocate_space_on_stack(int size) {
    stack_top -= size;
    return create_mips32_address(Strdup("$fp"), stack_top);
}

// 将寄存器进行释放
// 必要时进行spill
void free_register(struct mips32_register_descriptor *r, 
        list<mips32_code *> &l,
        list<mips32_code *>::iterator &it) {
    // 这个寄存器确实被使用了
    // 需要进行spill
    struct mips32_variable_descriptor *v = r->variable;
    if(r->modified) {
        // 找到这个变量对应的内存地址
        // 此变量尚未被spill过，没有内存地址
        if(!v->mem_addr)
            v->mem_addr = allocate_space_on_stack(4);
        // 进行spill
        struct mips32_operand *op1 = create_mips32_operand(MIPS32_OP_REGISTER, r->name);
        struct mips32_operand *op2 = create_mips32_operand(MIPS32_OP_ADDRESS, v->mem_addr);
        struct mips32_code *c = create_mips32_code(MIPS32_SW, 2, op1, op2);
        it = l.insert(it, c);
        it++;
    }
    // 重新放到未使用寄存器中
    v->reg = NULL;
    r->modified = 0;
    r->variable = NULL;
    unused_registers.push_back(r);
}

// Allocate(x):
// if (there exists a register r that currently has not been assigned to any variable)
//     result = r
// else
//     result = the register that contains a value whose next use is farthest in the future
//     spill result
// return result
struct mips32_register_descriptor*allocate(char *name, 
        list<mips32_code *> &l,
        list<mips32_code *>::iterator &it) {
    struct mips32_register_descriptor *r = NULL;
    struct mips32_variable_descriptor *v = variables[name];
    // first, try to find an empty register
    if(unused_registers.empty()) {
        // 将第一个取出来，并将其spill
        r = used_registers.front();
        used_registers.pop_front();
        free_register(r, l, it);
    }
    r = unused_registers.front();
    unused_registers.pop_front();
    // 加到used_register最后面
    // 这是一个先进先出队列
    r->variable = v;
    used_registers.push_back(r);
    v->reg = r;
    return r;
}

LINKAGE void mips32_codegen(struct ir_code *code, FILE *f) {
    print_ir_codes(code, f);
    // the first step is to find basic block
    find_basic_blocks(code);
    /*
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
    */
    select_instruction();
    // 输出选择的指令
    FILE *tmp = Fopen("out.s", "w");
    for(unsigned i = 0; i < functions.size(); i++) {
        fprintf(tmp, "*************************\n");
        for(unsigned j = 0; j < functions[i].basic_blocks.size(); j++) {
            list<struct mips32_code *> &l = functions[i].basic_blocks[j].machine_code;
            fprintf(tmp, "-------------------------\n");
            print_mips32_codes(l, tmp);
        }
    }

    register_allocation();
    for(unsigned i = 0; i < functions.size(); i++) {
        // fprintf(stderr, "*************************\n");
        print_mips32_codes(functions[i].prologue, stderr);
        for(unsigned j = 0; j < functions[i].basic_blocks.size(); j++) {
            list<struct mips32_code *> &l = functions[i].basic_blocks[j].machine_code;
            // fprintf(stderr, "-------------------------\n");
            print_mips32_codes(l, stderr);
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
