#include <iostream>
#include <vector>
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

// 用来描述一个基本块
// 由于我这里不准备进行全局数据流分析
// 只准备做局部处理
// 所以我这里只要将代码分为基本块并将基本块线性排列即可
struct basic_block {
    // 基本块内的首条指令
    struct ir_code *code;
};

// 一个函数由若干个基本块组成
struct function {
    vector<struct basic_block> basic_blocks;
};

vector<function> functions;

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
    struct ir_code *start = code;
    while(code) {
        struct ir_code *next = code->next;
        if(code->kind == IR_FUNCTION) {
            if(start) {
                code->next = NULL;
                function_codes.push_back(start);
            }
            start = next;
        }
        code = next;
    }
    // 将最后一个函数的指令加入到function_codes中
    if(start)
        function_codes.push_back(start);

    // 输出每个函数
    /*
       for(int i = 0; i < function_codes.size(); i++) {
       fprintf(stderr, "******************\n");
       print_ir_codes(function_codes[i], stderr);
       }
       */

    // 接着，我们将每个函数分割成基本块的大小
    for(unsigned i = 0; i < function_codes.size(); i++) {
        start = code = function_codes[i];
        struct basic_block curr_block;
        struct function curr_function;
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
        functions.push_back(curr_function);
    }

    // print functions and basic blocks
    /*
       for(unsigned i = 0; i < functions.size(); i++) {
       fprintf(stderr, "*******************\n");
       for(unsigned j = 0; j < functions[i].basic_blocks.size(); j++) {
       fprintf(stderr, "----------------------\n");
       print_ir_codes(functions[i].basic_blocks[j].code, stderr);
       }
       }
       */
}

LINKAGE void mips32_codegen(struct ir_code *code, FILE *f) {
    // the first step is to find basic block
    print_ir_codes(code, f);
    find_basic_blocks(code);
}
