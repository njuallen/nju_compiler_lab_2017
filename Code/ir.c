#include <stdarg.h>
#include "csapp.h"
#include "adt.h"
#include "syntax.h"
#include "semantic.h"
#include "ir.h"

#define HASH_TABLE_SIZE 1024

#define DEBUG 0

int generate_ir_successful = 1;

extern struct hash_table *variable_symbol_table, *function_definition_symbol_table,
       *function_declaration_symbol_table, *structure_symbol_table;

struct ir_code *translate_Program(struct syntax_node *root);
struct ir_code *translate_ExtDefList(struct syntax_node *root);
struct ir_code *translate_ExtDef(struct syntax_node *root);
struct ir_code *translate_FunDec(struct syntax_node *root);
struct ir_code *translate_VarList(struct syntax_node *root);
struct ir_code *translate_ParamDec(struct syntax_node *root);
void ir_error(int line_no, char *msg);
int get_variable_var_no(char *name);
struct ir_code *concat_code(struct ir_code *code1, struct ir_code *code2);
struct operand *create_operand(int kind, ...);
struct ir_code *create_ir_code(int kind, int argc, ...);
void print_ir_code(struct ir_code *code);

void generate_ir(struct syntax_node *root) {
    // generate ir
    struct ir_code *code = translate_Program(root);
    if(generate_ir_successful) {
        // output ir
        while(code) {
            print_ir_code(code);
            code = code->next;
        }
    }
}

struct ir_code *translate_Program(struct syntax_node *root) {
    // Program : ExtDefList
    return translate_ExtDefList(child_1(root));
}

struct ir_code *translate_ExtDefList(struct syntax_node *root) {
    if(!root->is_empty) {
        // ExtDefList : ExtDef ExtDefList
        struct ir_code *code1 = translate_ExtDef(child_1(root));
        struct ir_code *code2 = translate_ExtDefList(child_2(root));
        code1 = concat_code(code1, code2);
        return code1;
    }
    return NULL;
}

struct ir_code *translate_ExtDef(struct syntax_node *root) {
    if(child_2(root)->node_type == ExtDecList) {
        // ExtDef : Specifier ExtDecList SEMI
        ir_error(root->line_no, "Global variable not supported");
    }else if(child_2(root)->node_type == FunDec) {

        if(child_3(root)->node_type == CompSt) {
            // ExtDef : Specifier FunDec CompSt
            // function definition
            struct ir_code *code1 = translate_FunDec(child_2(root));
            return code1;
            // we get the function signature
            // now we generate code for function name and params
            // struct ir_code * code2 = translate_CompSt(child_3(root), type);
        }
        else {
            // ExtDef : Specifier FunDec SEMI
            // function declaration
            ir_error(root->line_no, "Function declaration not supported");
        }
    }

    return NULL;
}

struct ir_code *translate_FunDec(struct syntax_node *root) {
    struct syntax_node *id = child_1(root);
    struct function_symbol_table_entry *entry = 
        Calloc(1, sizeof(struct function_symbol_table_entry));
    entry->name = Strdup(id->value.string_value);
    struct function_symbol_table_entry *old = NULL;
    old = 
        hash_table_search(function_definition_symbol_table, entry);
    // 实际上，我感觉我们这边实际上不用做这么多检查
    // 因为助教给的测试样例肯定满足这些要求
    // check return type, it should be basic type
    struct semantic_type *t = old->return_type;
    if(t->kind != BASIC) {
        ir_error(root->line_no, "Function return type not basic type");
        return NULL;
    }
    // check parameters, it should be basic type
    int i;
    for(i = 0; i < old->argc; i++)
        if(old->args[i]->kind != BASIC) {
            ir_error(root->line_no, "Function parameter type not basic type");
            return NULL;
        }

    struct ir_code *code1 = create_ir_code(IR_FUNCTION, 
            1, create_operand(OP_NAME, entry->name));

    if(child_3(root)->node_type == VarList) {
        // FunDec : ID LP VarList RP
        // this add parameters to the inner most scope
        struct ir_code *code2 = translate_VarList(child_3(root));
        code1 = concat_code(code1, code2);
    }
    else {
        // FunDec : ID LP RP
    }
    return code1;
}

struct ir_code *translate_VarList(struct syntax_node *root) {
    struct ir_code *code1 = translate_ParamDec(child_1(root));
    if(num_child(root) > 1) {
        // VarList : ParamDec COMMA VarList
        struct ir_code *code2 = translate_VarList(child_3(root));
        code1 = concat_code(code1, code2);
    }
    return code1;
}

struct ir_code *translate_ParamDec(struct syntax_node *root) {
    // ParamDec : Specifier VarDec
    // since we assume that function parameters will not be complex types such as arrays and structures
    // VarDec : ID
    struct syntax_node *vardec = child_2(root);
    struct syntax_node *id = child_1(vardec);
    int var_no = get_variable_var_no(id->value.string_value);
    struct ir_code *code = create_ir_code(IR_PARAM, 
            1, create_operand(OP_VARIABLE, var_no));
    return code;
}

void ir_error(int line_no, char *msg) {
    printf("IR generation error at Line %d: %s.\n", line_no, msg);
    generate_ir_successful = 0;
}

int var_no_counter = 1;

int get_variable_var_no(char *name) {
    struct variable_symbol_table_entry *entry =
        Calloc(1, sizeof(struct variable_symbol_table_entry));
    entry->name = Strdup(name);
    struct variable_symbol_table_entry *old = hash_table_search(variable_symbol_table, entry);
    // since all variable_symbol_table_entry are calloced
    // so by default, their var_no is 0
    // so we can use this to check whether this variable has been allocated a var_no
    if(old->var_no == 0)
        old->var_no = var_no_counter++;
    return old->var_no;
}

// 将链表1与链表2连接起来
struct ir_code *concat_code(struct ir_code *code1, struct ir_code *code2) {
    if(!code1)
        return code2;
    if(!code2)
        return code1;
    // 找到链表1的尾元素
    struct ir_code *curr = code1;
    while(curr->next)
        curr = curr->next;
    curr->next = code2;
    code2->prev = curr;
    return code1;
}

struct operand *create_operand(int kind, ...) {
    struct operand *op = Calloc(1, sizeof(struct operand));
    op->kind = kind;
    va_list args;
    va_start(args, kind);
    switch(kind) {
        case OP_VARIABLE:
            op->u.var_no = va_arg(args, int);
            break;
        case OP_CONSTANT:
            op->u.value = va_arg(args, int);
            break;
        case OP_ADDRESS:
            app_error("No such kind of operand");
            break;
        case OP_NAME:
            op->u.name = Strdup(va_arg(args, char *));
            break;
        default:
            app_error("No such kind of operand");
            break;
    }
    va_end(args);
    return op;
}

struct ir_code *create_ir_code(int kind, int argc, ...) {
    struct ir_code *code = Calloc(1, sizeof(struct ir_code));
    code->kind = kind;
    if(argc > MAX_OPERAND)
        app_error("Too much operand for IR code");
    va_list args;
    va_start(args, argc);
    for(int i = 0; i < argc; i++)
        code->op[i] = va_arg(args, struct operand *);
    va_end(args);
    return code;
}

void print_ir_code(struct ir_code *code) {
    switch(code->kind) {
        case IR_FUNCTION:
            printf("FUNCTION %s :\n", code->op[0]->u.name);
            break;
        case IR_PARAM:
            // our variable name starts with t
            printf("PARAM t%d\n", code->op[0]->u.var_no);
            break;
        default:
            break;
    }
}
