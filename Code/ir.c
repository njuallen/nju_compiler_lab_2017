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

int var_no_counter = 1;
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
struct ir_code * translate_Stmt(struct syntax_node *root);
struct ir_code *translate_Cond(struct syntax_node *root, 
        struct operand *label_true, struct operand *label_false);
struct ir_code *translate_Args(struct syntax_node *root, struct ir_code **exp_code);

void ir_error(int line_no, char *msg);
int get_variable_var_no(char *name);
struct ir_code *concat_codes(int argc, ...);
struct operand *create_new_label();
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
        code1 = concat_codes(2, code1, code2);
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
            code1 = concat_codes(2, code1, code2);
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
        code1 = concat_codes(2, code1, code2);
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
        code1 = concat_codes(2, code1, code2);
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
    return concat_codes(2, code1, code2);
}

struct ir_code *translate_StmtList(struct syntax_node *root) {
    if(!root->is_empty) {
        // StmtList : Stmt StmtList
        struct ir_code *code1 = translate_Stmt(child_1(root));
        struct ir_code *code2 = translate_StmtList(child_2(root));
        return concat_codes(2, code1, code2);
    }
    return NULL;
}

struct ir_code * translate_Stmt(struct syntax_node *root) {
    struct ir_code *code1 = NULL, *code2 = NULL, *code3 = NULL;
    struct operand *op = NULL, *l1 = NULL, *l2 = NULL, *l3 = NULL;
    switch(child_1(root)->node_type) {
        case Exp:
            // Stmt : Exp SEMI
            code1 = translate_Exp(child_1(root), &op);
            break;
        case CompSt:
            // Stmt : CompSt
            code1 = translate_CompSt(child_1(root));
            break;
        case RETURN:
            // Stmt : RETURN Exp SEMI
            code1 = translate_Exp(child_2(root), &op);
            code2 = create_ir_code(IR_RETURN, 1, op);
            code1 = concat_codes(2, code1, code2);
            break;
        case IF:
            // Stmt : IF LP Exp RP Stmt
            // Stmt : IF LP Exp RP Stmt ELSE Stmt
            l1 = create_new_label();
            l2 = create_new_label();
            code1 = translate_Cond(child_3(root), l1, l2);
            code2 = translate_Stmt(child_5(root));
            if(num_child(root) > 5) {
                l3 = create_new_label();
                code3 = translate_Stmt(child_7(root));
                code1 = concat_codes(7, code1, create_ir_code(IR_LABEL, 1, l1),
                        code2, create_ir_code(IR_GOTO, 1, l3),
                        create_ir_code(IR_LABEL, 1, l2),
                        code3, create_ir_code(IR_LABEL, 1, l3));
            }
            else {
                code1 = concat_codes(4, code1, create_ir_code(IR_LABEL, 1, l1),
                        code2, create_ir_code(IR_LABEL, 1, l2));
            }
            break;
        case WHILE:
            // Stmt : WHILE LP Exp RP Stmt
            l1 = create_new_label();
            l2 = create_new_label();
            l3 = create_new_label();
            code1 = translate_Cond(child_3(root), l2, l3);
            code2 = translate_Stmt(child_5(root));
            code1 = concat_codes(6, create_ir_code(IR_LABEL, 1, l1), 
                    code1, create_ir_code(IR_LABEL, 1, l2),
                    code2, create_ir_code(IR_GOTO, 1, l1),
                    create_ir_code(IR_LABEL, 1, l3));
            break;
        default:
            break;
    }
    return code1;
}

struct ir_code *translate_Cond(struct syntax_node *root, 
        struct operand *label_true, struct operand *label_false) {
    struct operand *op1, *op2, *relop;
    struct ir_code *code1, *code2, *code3, *code4;
    struct operand *label_1;
    if(child_1(root)->node_type == Exp) {
        switch(child_2(root)->node_type) {
            case RELOP:
                code1 = translate_Exp(child_1(root), &op1);
                code2 = translate_Exp(child_3(root), &op2);
                relop = create_operand(OP_NAME, child_2(root)->value.string_value);
                code3 = create_ir_code(IR_IF, 4, op1, relop, op2, label_true);
                code4 = create_ir_code(IR_GOTO, 1, label_false);
                code1 = concat_codes(4, code1, code2, code3, code4);
                return code1;
                break;
            case AND:
                label_1 = create_new_label();
                code1 = translate_Cond(child_1(root), label_1, label_false);
                code2 = translate_Cond(child_3(root), label_true, label_false);
                code3 = create_ir_code(IR_LABEL, 1, label_1);
                code1 = concat_codes(3, code1, code3, code2);
                return code1;
                break;
            case OR:
                label_1 = create_new_label();
                code1 = translate_Cond(child_1(root), label_true, label_1);
                code2 = translate_Cond(child_3(root), label_true, label_false);
                code3 = create_ir_code(IR_LABEL, 1, label_1);
                code1 = concat_codes(3, code1, code3, code2);
                return code1;
                break;
            default:
                break;
        }
    }

    if(child_1(root)->node_type == NOT) {
        return translate_Cond(child_2(root), label_false, label_true);
    }
    else {
        code1 = translate_Exp(root, &op1);
        op2 = create_operand(OP_CONSTANT, 0);
        relop = create_operand(OP_NAME, "!=");
        code2 = create_ir_code(IR_IF, 4, op1, relop, op2, label_true);
        code3 = create_ir_code(IR_GOTO, 1, label_false);
        code1 = concat_codes(3, code1, code2, code3);
        return code1;
    }
}

struct ir_code *translate_DefList(struct syntax_node *root) {
    if(!root->is_empty) {
        // ExtDefList : ExtDef ExtDefList
        struct ir_code *code1 = translate_Def(child_1(root));
        struct ir_code *code2 = translate_DefList(child_2(root));
        return concat_codes(2, code1, code2);
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
        code1 = concat_codes(2, code1, code2);
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
        code1 = concat_codes(3, code1, code2, code3);
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
    struct operand *op1 = NULL, *op2 = NULL, *r = NULL, *label1, *label2, *t1, *t2;
    struct ir_code *code1 = NULL, *code2 = NULL, *code3 = NULL, *code4 = NULL, *code5 = NULL;
    char *function_name = NULL;
    switch(child_1(root)->node_type) {
        case Exp:
            switch(child_2(root)->node_type) {
                case PLUS:
                case MINUS:
                case STAR:
                case DIV:
                    code1 = translate_Exp(child_1(root), &op1);
                    code2 = translate_Exp(child_3(root), &op2);
                    r = create_operand(OP_VARIABLE, var_no_counter++);
                    code3 = create_ir_code(IR_ARITHMETIC, 4, r, 
                            create_operand(OP_NAME, child_2(root)->value.string_value), 
                            op1, op2);
                    code1 = concat_codes(3, code1, code2, code3);
                    break;
                case RELOP:
                case AND:
                case OR:
                    /*
                     * Exp : Exp AND Exp
                     * Exp : Exp OR Exp
                     */
                    label1 = create_new_label();
                    label2 = create_new_label();
                    r = create_operand(OP_VARIABLE, var_no_counter++);
                    code1 = create_ir_code(IR_ASSIGN, 2, r, create_operand(OP_CONSTANT, 0));
                    code2 = translate_Cond(root, label1, label2);
                    code3 = create_ir_code(IR_LABEL, 1, label1);
                    code4 = create_ir_code(IR_ASSIGN, 2, r, create_operand(OP_CONSTANT, 1));
                    code5 = create_ir_code(IR_LABEL, 1, label2);
                    code1 = concat_codes(5, code1, code2, code3, code4, code5);
                    break;
                case ASSIGNOP:
                    // Exp : Exp ASSIGNOP Exp
                    code1 = translate_Exp(child_1(root), &op1);
                    code2 = translate_Exp(child_3(root), &op2);
                    r = create_operand(OP_VARIABLE, var_no_counter++);
                    code3 = create_ir_code(IR_ASSIGN, 2, op1, op2);
                    code4 = create_ir_code(IR_ASSIGN, 2, r, op1);
                    code1 = concat_codes(4, code1, code2, code3, code4);
                    break;
                case LB:
                    // array
                    // Exp : Exp LB Exp RB
                    // op1 should be the base address of the array
                    code1 = translate_Exp(child_1(root), &op1);
                    // op2 is the index
                    code2 = translate_Exp(child_3(root), &op2);
                    // t2 stores the address of the element
                    // but it should be of variable
                    // or we can not assign value to it
                    t2 = create_operand(OP_VARIABLE, var_no_counter++);
                    t1 = create_operand(OP_VARIABLE, var_no_counter++);
                    // size of array element is always 4
                    code3 = create_ir_code(IR_ARITHMETIC, 4, op1, op2);
                    // t1 = op2 * 4
                    code3 = create_ir_code(IR_ARITHMETIC, 4, t1, 
                            create_operand(OP_NAME, "*"), 
                            op2, create_operand(OP_CONSTANT, 4));
                    // t2 = op1 + t1
                    code4 = create_ir_code(IR_ARITHMETIC, 4, t2, 
                            create_operand(OP_NAME, "+"), 
                            op1, t1);
                    // r is of type OP_ADDRESS
                    // but it shares the same virtual register with t2
                    r = Calloc(1, sizeof(struct operand));
                    r->kind = OP_ADDRESS;
                    r->u.var_no = t2->u.var_no;
                    code1 = concat_codes(4, code1, code2, code3, code4);
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
            code1 = translate_Exp(child_2(root), &r);
            break;
        case MINUS:
            // Exp : MINUS Exp
            code1 = translate_Exp(child_2(root), &op1);
            r = create_operand(OP_VARIABLE, var_no_counter++);
            code2 = create_ir_code(IR_ARITHMETIC, 4, r, 
                    create_operand(OP_NAME, "-"), 
                    create_operand(OP_CONSTANT, 0), op1);
            code1 = concat_codes(2, code1, code2);
            break;
        case NOT:
            // Exp : NOT Exp
            label1 = create_new_label();
            label2 = create_new_label();
            r = create_operand(OP_VARIABLE, var_no_counter++);
            code1 = create_ir_code(IR_ASSIGN, 2, r, create_operand(OP_CONSTANT, 0));
            code2 = translate_Cond(root, label1, label2);
            code3 = create_ir_code(IR_LABEL, 1, label1);
            code4 = create_ir_code(IR_ASSIGN, 2, r, create_operand(OP_CONSTANT, 1));
            code5 = create_ir_code(IR_LABEL, 1, label2);
            code1 = concat_codes(5, code1, code2, code3, code4, code5);
            break;
        case ID:
            if(num_child(root) > 1) {
                // Exp : ID LP Args RP
                // function call
                function_name = child_1(root)->value.string_value;
                if(!strcmp(function_name, "read")) {
                    r = create_operand(OP_VARIABLE, var_no_counter++);
                    code1 = create_ir_code(IR_READ, 1, r); 
                }
                else if(!strcmp(function_name, "write")) {
                    // since write only accept one arguments
                    // so Args must produce exp
                    code1 = translate_Exp(child_1(child_3(root)), &op1);
                    code1 = create_ir_code(IR_WRITE, 1, op1); 
                }
                else {
                    code1 = translate_Args(child_3(root), &code2);
                    r = create_operand(OP_VARIABLE, var_no_counter++);
                    code3 = create_ir_code(IR_CALL, 2, r, 
                            create_operand(OP_NAME, child_1(root)->value.string_value));
                    code1 = concat_codes(3, code2, code1, code3);
                }
            }
            else {
                // simply a variable
                // we look it up in the variable_symbol_table
                r = create_operand(OP_VARIABLE, 
                        get_variable_var_no(child_1(root)->value.string_value));
            }
            break;
        case INT:
            // Exp : INT
            r = create_operand(OP_CONSTANT, child_1(root)->value.int_value);
            break;
        case FLOAT:
            // Exp : FLOAT
            r = create_operand(OP_CONSTANT, child_1(root)->value.float_value);
            break;
        default:
            break;
    }
    // No code
    *op = r;
    return code1;
}

// returning value: code for parameter passing
// exp_code: code for parameter expression calculation
struct ir_code *translate_Args(struct syntax_node *root, struct ir_code **exp_code) {
    struct ir_code *code1 = NULL, *code2 = NULL, *code3 = NULL, *exp = NULL;
    struct operand *op;
    if(num_child(root) > 1) {
        // Args : Exp COMMA Args
        // 此处代码要分成两部分，分别是计算实参和压入实参的代码
        code1 = translate_Args(child_3(root), &exp);
        code2 = translate_Exp(child_1(root), &op);
        code3 = create_ir_code(IR_PARAM, 1, op);
        // 压栈要按照逆序进行
        code1 = concat_codes(2, code1, code2);
        *exp_code = concat_codes(2, exp, code3); 
    }
    else {
        // Args : Exp
        *exp_code = translate_Exp(child_1(root), &op);
        code1 = create_ir_code(IR_PARAM, 1, op);
    }
    return code1;
}

void ir_error(int line_no, char *msg) {
    printf("IR generation error at Line %d: %s.\n", line_no, msg);
    generate_ir_successful = 0;
}


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

struct ir_code *concat_codes(int argc, ...) {
    va_list args;
    va_start(args, argc);
    struct ir_code *head = NULL, *curr = NULL;
    for(int i = 0; i < argc; i++) {
        curr = va_arg(args, struct ir_code *);
        head = concat_code(head, curr);
    }
    va_end(args);
    return head;
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
            return Asprintf("%s", op->u.name);
            break;
        default:
            app_error("Unknown type of operand");
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
        case IR_ARITHMETIC:
            // the first operand is the dst operand
            // the second operand is the operator
            // the third operand is the "real first operand"
            // the forth operand is the "real second operand"
            printf("%s := %s %s %s\n", get_operand_name(code->op[0]), 
                    get_operand_name(code->op[2]), 
                    get_operand_name(code->op[1]), 
                    get_operand_name(code->op[3]));
            break;
        case IR_LABEL:
            printf("LABEL %s :\n", get_operand_name(code->op[0]));
            break;
        case IR_GOTO:
            printf("GOTO %s\n", get_operand_name(code->op[0]));
            break;
        case IR_RETURN:
            printf("RETURN %s\n", get_operand_name(code->op[0]));
            break;
        case IR_IF:
            printf("IF %s %s %s GOTO %s\n", get_operand_name(code->op[0]),
                    get_operand_name(code->op[1]), 
                    get_operand_name(code->op[2]), 
                    get_operand_name(code->op[3]));
            break;
        case IR_CALL:
            printf("%s := CALL %s\n", get_operand_name(code->op[0]), 
                    get_operand_name(code->op[1]));
            break;
        case IR_READ:
            printf("READ %s\n", get_operand_name(code->op[0]));
            break;
        case IR_WRITE:
            printf("WRITE %s\n", get_operand_name(code->op[0]));
            break;
        default:
            app_error("Unknown type of ir code");
            break;
    }
}

int label_counter = 1;
struct operand *create_new_label() {
    return create_operand(OP_NAME, Asprintf("label%d", label_counter++));
}
