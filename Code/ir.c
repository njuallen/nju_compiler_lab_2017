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
struct ir_code *translate_CompSt(struct syntax_node *root);
struct ir_code *translate_StmtList(struct syntax_node *root);
struct ir_code *translate_DefList(struct syntax_node *root);
struct ir_code *translate_Def(struct syntax_node *root);
struct ir_code *translate_DecList(struct syntax_node *root);
struct ir_code *translate_Dec(struct syntax_node *root);
struct ir_code *translate_VarDec(struct syntax_node *root, struct operand **op_param);
struct ir_code *translate_Exp(struct syntax_node *root, struct operand **op_param);

void ir_error(int line_no, char *msg);
int get_variable_var_no(char *name);
struct ir_code *concat_code(struct ir_code *code1, struct ir_code *code2);
struct operand *create_operand(int kind, ...);
struct ir_code *create_ir_code(int kind, int argc, ...);
void print_ir_code(struct ir_code *code);
char *get_operand_name(struct operand *op);

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
            // we get the function signature
            // now we generate code for function name and params
            struct ir_code * code2 = translate_CompSt(child_3(root));
            code1 = concat_code(code1, code2);
            return code1;
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

struct ir_code *translate_CompSt(struct syntax_node *root) {
    // CompSt : LC DefList StmtList RC
    struct ir_code *code1 = translate_DefList(child_2(root));
    struct ir_code *code2 = translate_StmtList(child_3(root));
    return concat_code(code1, code2);
}

struct ir_code *translate_StmtList(struct syntax_node *root) {
    return NULL;
}

struct ir_code *translate_DefList(struct syntax_node *root) {
    if(!root->is_empty) {
        // ExtDefList : ExtDef ExtDefList
        struct ir_code *code1 = translate_Def(child_1(root));
        struct ir_code *code2 = translate_DefList(child_2(root));
        return concat_code(code1, code2);
    }
    return NULL;
}

struct ir_code *translate_Def(struct syntax_node *root) {
    // ExtDef : Specifier DecList SEMI
    if(child_2(root)->node_type == DecList) {
        return translate_DecList(child_2(root));
    }
    return NULL;
}

struct ir_code *translate_DecList(struct syntax_node *root) {
    struct ir_code *code1 = translate_Dec(child_1(root));
    if(child_1(root)->next) {
        // DecList : Dec COMMA DecList
        struct ir_code *code2 = translate_DecList(child_3(root));
        code1 = concat_code(code1, code2);
    }
    return code1;
}

struct ir_code *translate_Dec(struct syntax_node *root) {
    struct syntax_node *var_dec = child_1(root);
    struct operand *op1, *op2;
    struct ir_code *code1 = translate_VarDec(var_dec, &op1);

    if(var_dec->next) {
        // Dec : VarDec ASSIGNOP Exp
        // array assignment is not supported
        // so this must be assignment between basic types
        struct ir_code *code2 = translate_Exp(child_3(root), &op2);
        struct ir_code *code3 = create_ir_code(IR_ASSIGN, 2, op1, op2);
        code1 = concat_code(concat_code(code1, code2), code3);
    }
    return code1;
}

struct ir_code *translate_VarDec(struct syntax_node *root, struct operand **op) {
    if(child_1(root)->node_type == ID) {
        // VarDec : ID
        struct syntax_node *id = child_1(root);
        int var_no = get_variable_var_no(Strdup(id->value.string_value));
        *op = create_operand(OP_VARIABLE, var_no);
        // just a declaration, no code
    }
    else {
        // VarDec : VarDec LB INT RB
        // array type
        // since we do not support high dimension arrays(> 1 dimension)
        // VarDec must produce ID
        if(child_1(child_1(root))->node_type != ID) {
            ir_error(root->line_no, "High dimension arrays is not supported");
        }
        else {
            struct syntax_node *id = child_1(child_1(root));
            int var_no = get_variable_var_no(Strdup(id->value.string_value));
            *op = create_operand(OP_VARIABLE, var_no);
            // allocate space for the array
            // since this is an array of basic type
            // so array element size is 4
            struct ir_code *code = create_ir_code(IR_DEC, 2, *op, 
                    create_operand(OP_CONSTANT, child_3(root)->value.int_value * 4));
            return code;
        }
    }
    return NULL;
}

struct ir_code *translate_Exp(struct syntax_node *root, struct operand **op) {
    switch(child_1(root)->node_type) {
        case Exp:
            switch(child_2(root)->node_type) {
                case PLUS:
                case MINUS:
                case STAR:
                case DIV:
                case RELOP:
                    /* Exp arithmetic/comparison operator Exp
                     * Exp must be of basic type
                     *
                     * Exp : Exp PLUS Exp
                     * Exp : Exp MINUS Exp
                     * Exp : Exp STAR Exp
                     * Exp : Exp DIV Exp
                     * Exp : Exp RELOP Exp
                     */
                    break;
                case AND:
                case OR:
                    /*
                     * Exp : Exp AND Exp
                     * Exp : Exp OR Exp
                     */
                    break;
                case ASSIGNOP:
                    // Exp : Exp ASSIGNOP Exp
                    break;
                case LB:
                    // array
                    // Exp : Exp LB Exp RB
                    break;
                case DOT:
                    // structure
                    // Exp : Exp DOT ID
                    break;
                default:
                    break;
            }
            break;
        case LP:
            // Exp : LP Exp RP
            break;
        case MINUS:
            // Exp : NOT Exp
            break;
        case NOT:
            // Exp : NOT Exp
            break;
        case ID:
            if(num_child(root) > 1) {
                // function call
            }
            else {
                /* simply a variable
                 * we look it up in the variable_symbol_table
                 */
            }
            break;
        case INT:
            // Exp : INT
            *op = create_operand(OP_CONSTANT, child_1(root)->value.int_value);
            break;
        case FLOAT:
            // Exp : FLOAT
            *op = create_operand(OP_CONSTANT, child_1(root)->value.float_value);
            break;
        default:
            break;
    }
    // No code
    return NULL;
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
    if(old->var_no == 0) {
        old->var_no = var_no_counter++;
    }
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

char *get_operand_name(struct operand *op) {
    switch(op->kind) {
        case OP_VARIABLE:
            return Asprintf("t%d", op->u.var_no);
            break;
        case OP_CONSTANT:
            // what if we encounter float constant?
            return Asprintf("#%d", op->u.value);
            break;
        case OP_ADDRESS:
            return Asprintf("*t%d", op->u.var_no);
            break;
        case OP_NAME:
            return Asprintf("s", op->u.name);
            break;
        default:
            return NULL;
            break;
    }
}

void print_ir_code(struct ir_code *code) {
    switch(code->kind) {
        case IR_FUNCTION:
            printf("FUNCTION %s :\n", get_operand_name(code->op[0]));
            break;
        case IR_PARAM:
            // our variable name starts with t
            printf("PARAM %s\n", get_operand_name(code->op[0]));
            break;
        case IR_ASSIGN:
            printf("%s := %s\n", get_operand_name(code->op[0]), 
                    get_operand_name(code->op[1]));
            break;
        case IR_DEC:
            printf("DEC %s [%d]\n", get_operand_name(code->op[0]), 
                    code->op[1]->u.value);
            break;
        default:
            break;
    }
}
