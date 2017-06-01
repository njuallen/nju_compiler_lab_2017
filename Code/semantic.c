#include <stdarg.h>
#include "csapp.h"
#include "adt.h"
#include "syntax.h"
#include "semantic.h"

#define HASH_TABLE_SIZE 1024

#define DEBUG 0

// number of buckets of the hash table
int hash_string(char *s, int size) {
    int val = 0, i;
    for (; *s; ++s) {
        val = (val << 2) + *s;
        if ((i = val & size))
            val = (val ^ (i >> 12)) & size;
    }
    return val;
}

#define make_hash_function(function_name, entry_type, size) \
int function_name(void *elem) { \
    struct entry_type *entry = (struct entry_type *)elem; \
    return hash_string(entry->name, size); \
} \

make_hash_function(hash_variable, variable_symbol_table_entry, HASH_TABLE_SIZE);
make_hash_function(hash_function, function_symbol_table_entry, HASH_TABLE_SIZE);
make_hash_function(hash_structure, structure_symbol_table_entry, HASH_TABLE_SIZE);

#define make_compare_function(function_name, entry_type) \
int function_name(void *elem_1, void *elem_2) { \
    struct entry_type *entry_1 = (struct entry_type *)elem_1; \
    struct entry_type *entry_2 = (struct entry_type *)elem_2; \
    return strcmp(entry_1->name, entry_2->name); \
} \

make_compare_function(compare_variable, variable_symbol_table_entry);
make_compare_function(compare_function, function_symbol_table_entry);
make_compare_function(compare_structure, structure_symbol_table_entry);

struct hash_table *variable_symbol_table, *function_definition_symbol_table,
                  *function_declaration_symbol_table, *structure_symbol_table;

/* variable_scopes stores pointer to linked lists
 * each linked lists chain together variable definitions in the same scope
 * scope_types tells the type(VARIABLE_SCOPE/STRUCTURE_SCOPE) of each scope
 */
struct cstack *variable_scopes, *scope_types;

#define MAX_MSG_SIZE 1024
char msg_buffer[MAX_MSG_SIZE];

enum scope_type {
    VARIABLE_SCOPE = 0,
    STRUCTURE_SCOPE
};

#define MAX_NESTED_SCOPES 100

void handle_Program(struct syntax_node *root);
void handle_ExtDefList(struct syntax_node *root);
void handle_ExtDef(struct syntax_node *root);
void handle_ExtDecList(struct syntax_node *root, struct semantic_type *type);
struct semantic_type *handle_VarDec(struct syntax_node *root, struct semantic_type *type);
struct semantic_type *handle_Specifier(struct syntax_node *root);
char *handle_OptTag(struct syntax_node *root);
char *handle_Tag(struct syntax_node *root);
struct semantic_type *handle_StructSpecifier(struct syntax_node *root);
void handle_DefList(struct syntax_node *root);
void handle_Def(struct syntax_node *root);
void handle_DecList(struct syntax_node *root, struct semantic_type *type);
void handle_Dec(struct syntax_node *root, struct semantic_type *type);
struct function_symbol_table_entry * handle_FunDec(
        struct syntax_node *root, struct semantic_type *type);
int handle_VarList(struct syntax_node *root);
void handle_ParamDec(struct syntax_node *root);
void handle_CompSt(struct syntax_node *root, struct semantic_type *function_return_type);
void handle_StmtList(struct syntax_node *root, struct semantic_type *function_return_type);
void handle_Stmt(struct syntax_node *root, struct semantic_type *function_return_type);
struct semantic_type *handle_Exp(struct syntax_node *root, int *is_left_value);
struct semantic_type **handle_Args(struct syntax_node *root, int *argc);
int compare_semantic_type(struct semantic_type *t1, 
        struct semantic_type *t2);
int compare_function_type(struct function_symbol_table_entry *f1, 
        struct function_symbol_table_entry *f2);
void check_undefined_functions();
void semantic_error(int error_type, int line_no, ...);
void dbg_printf(const char *format, ...);
void print_variable_symbol_table_entry(struct variable_symbol_table_entry *entry);
void print_semantic_type(struct semantic_type *type);

enum error_type {
    UNDEFINED_VARIABLE = 0,
    UNDEFINED_FUNCTION,
    REDEFINED_VARIABLE,
    REDEFINED_FUNCTION,
    ASSIGNMENT_TYPE_MISMATCH,
    NOT_LEFT_VALUE,
    OPERANDS_TYPE_MISMATCH,
    RETURN_TYPE_MISMATCH,
    FUNCTION_TYPE_MISMATCH,
    NOT_AN_ARRAY,
    NOT_A_FUNCTION,
    ARRAY_INDEX_NOT_INTEGER,
    NOT_A_STRUCTURE,
    NON_EXISTEND_FIELD,
    STRUCTURE_FIELD_ERROR,
    DUPLICATE_STRUCTURE,
    UNDEFINED_STRUCTURE,
    FUNCTION_DECLARED_NOT_DEFINED,
    FUNCTION_DEFINITION_DECLARATION_CONFLICT
};

int check_semantics(struct syntax_node *root) {
    variable_symbol_table = 
        create_hash_table(HASH_TABLE_SIZE, hash_variable, compare_variable);
    function_declaration_symbol_table = 
        create_hash_table(HASH_TABLE_SIZE, hash_function, compare_function);
    function_definition_symbol_table = 
        create_hash_table(HASH_TABLE_SIZE, hash_function, compare_function);
    structure_symbol_table = 
        create_hash_table(HASH_TABLE_SIZE, hash_structure, compare_structure);
    variable_scopes = create_cstack(MAX_NESTED_SCOPES);
    scope_types = create_cstack(MAX_NESTED_SCOPES);
    handle_Program(root);
    return 0;
}

// create a scope of type scope_type
void create_scope(int scope_type) {
    struct hash_node **curr_scope = Calloc(1, sizeof(struct hash_node **));
    *curr_scope = NULL;
    cstack_push(variable_scopes, curr_scope);

    int *type = Calloc(1, sizeof(int));
    *type = scope_type;
    cstack_push(scope_types, type);
}

void delete_scope() {
#ifdef NESTED_SCOPE
    // if nested_scope is supported, scopes needs to be deleted
    // if not, we do not delete scope
    // lab3 does not require nested scope
    Free(cstack_pop(scope_types));
    struct hash_node **top = cstack_pop(variable_scopes);
    struct hash_node *curr = *top;
    while(curr) {
        struct hash_node *next = curr->brother;
        struct variable_symbol_table_entry *entry = curr->elem;
        hash_table_delete(variable_symbol_table, entry);
        curr = next;
    }
    Free(top);
#endif
}

struct hash_node *search_inner_most_variable_scope(char *name) {
    struct hash_node **top = cstack_top(variable_scopes);
    struct hash_node *curr = *top;
    while(curr) {
        if(!strcmp(name, ((struct variable_symbol_table_entry *)curr->elem)->name))
            return curr;
        curr = curr->brother;
    }
    return NULL;
}

void insert_into_inner_most_variable_scope(struct hash_node *node) {
    struct hash_node **top = cstack_top(variable_scopes);
    struct hash_node *head = *top;
    *top = node;
    node->brother = head;
}

int get_inner_most_scope_type(){
    return *(int *)cstack_top(scope_types);
}

void handle_Program(struct syntax_node *root) {
    create_scope(VARIABLE_SCOPE);
    // Program : ExtDefList
    handle_ExtDefList(child_1(root));
    check_undefined_functions();
    delete_scope();
}

// looking for functions that are declared but not defined
void check_undefined_functions() {
    struct hash_node *node = NULL;
    for(int i = 0; i < HASH_TABLE_SIZE; i++) {
        node = function_declaration_symbol_table->nodes[i];
        while(node) {
            struct function_symbol_table_entry *entry = node->elem;
            struct function_symbol_table_entry *old = 
                hash_table_search(function_definition_symbol_table, entry);
            if(!old)
                semantic_error(FUNCTION_DECLARED_NOT_DEFINED, entry->line_no, entry->name);
            node = node->next;
        }
    }
}

void handle_ExtDefList(struct syntax_node *root) {
    if(!root->is_empty) {
        // ExtDefList : ExtDef ExtDefList
        handle_ExtDef(child_1(root));
        handle_ExtDefList(child_2(root));
    }
}

void handle_ExtDef(struct syntax_node *root) {
    struct syntax_node *specifier = child_1(root);
    struct semantic_type *type = handle_Specifier(specifier);
    if(child_2(root)->node_type == ExtDecList) {
        // ExtDef : Specifier ExtDecList SEMI
        handle_ExtDecList(child_2(root), type);
    }else if(child_2(root)->node_type == FunDec) {

        /* there should not be more than one entry 
         * with the same name in the same hash table.
         * so in case of function redefinition and declaration conflict
         * we should not insert the entry.
         */

        struct function_symbol_table_entry *entry = handle_FunDec(child_2(root), type);
        struct function_symbol_table_entry *old = NULL;
        if(child_3(root)->node_type == CompSt) {
            // ExtDef : Specifier FunDec CompSt
            // function definition
            // check for redefinition
            old = 
                hash_table_search(function_definition_symbol_table, entry);
            if(old) {
                semantic_error(REDEFINED_FUNCTION, entry->line_no, entry->name);
                goto out;
            }

            // check whether this definition conflicts with existing declaration
            old = 
                hash_table_search(function_declaration_symbol_table, entry);
            if(old) {
                if(!compare_function_type(old, entry)) {
                    sprintf(msg_buffer, "Function definition conflicts with function" 
                            " declaration at Line %d", old->line_no);
                    semantic_error(FUNCTION_DEFINITION_DECLARATION_CONFLICT, 
                            entry->line_no, msg_buffer);
                }
                /* even if definition conflicts with declaration
                 * we still needs to insert the definition into definition table.
                 * anyway, the function is defined.
                 * If we do not insert it, we are likely to throw 
                 * a function declared but not defined error
                 */
            }
            hash_table_insert(function_definition_symbol_table, entry);
            /* we should do this after we have insert the entry into the 
             * function_definition_symbol_table
             * or we will throw an undefined function error when we 
             * try to call the function in the function's body
             */
            handle_CompSt(child_3(root), type);
        }
        else {
            // ExtDef : Specifier FunDec SEMI
            // function declaration

            // check whether this declaration conflicts with existing definition
            old = 
                hash_table_search(function_definition_symbol_table, entry);
            if(old) {
                if(!compare_function_type(old, entry)) {
                    sprintf(msg_buffer, "Function declaration conflicts with function" 
                            " definition at Line %d", old->line_no);
                    semantic_error(FUNCTION_DEFINITION_DECLARATION_CONFLICT, 
                            entry->line_no, msg_buffer);
                }
            }

            // check whether this declaration conflicts with existing declaration
            old = 
                hash_table_search(function_declaration_symbol_table, entry);
            if(old) {
                if(!compare_function_type(old, entry)) {
                    sprintf(msg_buffer, "Function declaration conflicts with function" 
                            " declaration at Line %d", old->line_no);
                    semantic_error(FUNCTION_DEFINITION_DECLARATION_CONFLICT, 
                            entry->line_no, msg_buffer);
                }
                /* even if these declarations do not conflict
                 * we only store the first declaration in the hash_table
                 */
                goto out;
            }
            hash_table_insert(function_declaration_symbol_table, entry);
        }
out:
        // delete the function scope created in handle_FunDec
        delete_scope();
    }
}

int compare_semantic_type(struct semantic_type *t1, 
        struct semantic_type *t2) {
    if(!t1 || !t2 || t1->kind != t2->kind)
        return 0;
    switch(t1->kind) {
        case BASIC:
            return t1->u.basic == t2->u.basic;
            break;
        case ARRAY:
            /* just like common C compilers, 
             * we do not take array size into consideration
             */
            return compare_semantic_type(t1->u.array.elem, t2->u.array.elem);
            break;
        case STRUCTURE:
            /* we use name equivalence for structures
             * every structure has a name(even anonymous ones)
             * so we only need to compare their names
             */
            return !strcmp(t1->u.structure.name, t2->u.structure.name);
            break;
        default:
            break;
    }
    return 0;
}

int compare_function_type(struct function_symbol_table_entry *f1, 
        struct function_symbol_table_entry *f2) {
    if(!f1 || !f2 || strcmp(f1->name, f2->name) || f1->argc != f2->argc)
        return 0;
    if(!compare_semantic_type(f1->return_type, f2->return_type))
        return 0;
    for(int i = 0; i < f1->argc; i++)
        if(!compare_semantic_type(f1->args[i], f2->args[i]))
            return 0;
    return 1;
}

void handle_ExtDecList(struct syntax_node *root, struct semantic_type *type) {
    struct syntax_node *var_dec = child_1(root);
    handle_VarDec(var_dec, type);

    // ExtDecList : VarDec COMMA ExtDecList
    if(var_dec->next)
        handle_ExtDecList(child_3(root), type);
}

struct semantic_type *handle_VarDec(struct syntax_node *root, struct semantic_type *type) {
    if(child_1(root)->node_type == ID) {
        // VarDec : ID
        struct syntax_node *id = child_1(root);
        struct variable_symbol_table_entry *entry = 
            Calloc(1, sizeof(struct variable_symbol_table_entry));
        entry->name = Strdup(id->value.string_value);
        entry->type = type;
        entry->line_no = id->line_no;
        struct hash_node *old = 
            search_inner_most_variable_scope(entry->name);
        if(old) {
            int curr_scope_type = get_inner_most_scope_type();
            if(curr_scope_type == VARIABLE_SCOPE)
                // variable redefinition
                semantic_error(REDEFINED_VARIABLE, entry->line_no, entry->name);
            else {
                // structure field redefinition
                sprintf(msg_buffer, "Redefined field \"%s\"", entry->name);
                semantic_error(STRUCTURE_FIELD_ERROR, entry->line_no, msg_buffer);
            }
        }
        else {
            // insert into symbol table
            struct hash_node *curr = hash_table_insert(variable_symbol_table, entry);
            // insert into current scope
            insert_into_inner_most_variable_scope(curr);
        }
        return type;
    }
    else {
        // VarDec : VarDec LB INT RB
        // array type
        struct semantic_type *ret = Calloc(1, sizeof(struct semantic_type));
        ret->kind = ARRAY;
        ret->u.array.elem = type;
        ret->u.array.size = child_3(root)->value.int_value;
        return handle_VarDec(child_1(root), ret);
    }
}

struct semantic_type *handle_Specifier(struct syntax_node *root) {
    struct semantic_type *ret = NULL;
    if(child_1(root)->node_type == TYPE) {
        // Specifier : TYPE
        ret = Calloc(1, sizeof(struct semantic_type));
        ret->kind = BASIC;
        if(!strcmp(child_1(root)->value.string_value, "int"))
            ret->u.basic = INT;
        else
            ret->u.basic = FLOAT;
    }
    else {
        // Specifier : StructSpecifier
        ret = handle_StructSpecifier(child_1(root));
    }
    return ret;
}

char *handle_OptTag(struct syntax_node *root) {
    if(!root->is_empty)
        // copy it, in case we free the syntax tree later
        return Strdup(root->child->value.string_value);
    else {
        // anonymous structure, we give it a unique name
        static int counter = 0;
        char buf[100];
        sprintf(buf, "<struct>_%d", counter++);
        return Strdup(buf);
    }
}

struct semantic_type *handle_StructSpecifier(struct syntax_node *root) {

    struct structure_symbol_table_entry *old = NULL;

    struct structure_symbol_table_entry *entry = 
        Calloc(1, sizeof(struct structure_symbol_table_entry));
    entry->line_no = child_1(root)->line_no;

    if(child_2(root)->node_type == OptTag) {
        // STRUCT OptTag LC DefList RC
        /* we are defining a new structure
         * check for redefinition
         */
        entry->name = handle_OptTag(child_2(root));
        old = hash_table_search(structure_symbol_table, entry);
        if(old) {
            semantic_error(DUPLICATE_STRUCTURE, entry->line_no, entry->name);
            return NULL;
        }

        struct semantic_type *ret = Calloc(1, sizeof(struct semantic_type));
        ret->kind = STRUCTURE;
        ret->u.structure.name = Strdup(entry->name);

        create_scope(STRUCTURE_SCOPE);

        // field definition
        handle_DefList(child_4(root));

        /* the fields are chained in the inner most scope
         * we build the structure fields according to them
         */
        struct structure_field *curr_field = NULL;
        struct hash_node **top = cstack_top(variable_scopes);
        struct hash_node *curr = *top;
        while(curr) {
            struct variable_symbol_table_entry *entry = curr->elem;
            struct structure_field *field = Calloc(1, sizeof(struct structure_field));
            field->name = Strdup(entry->name);
            field->type = entry->type;
            field->next = NULL;
            if(!curr_field)
                ret->u.structure.field = curr_field = field;
            else {
                curr_field->next = field;
                curr_field = field;
            }
            curr = curr->brother;
        }

        delete_scope();
        /* structure type has been built
         * we need to insert it into structure_symbol_table_entry
         */
        entry->type = ret;
        hash_table_insert(structure_symbol_table, entry);
        return ret;
    }
    else {
        // STRUCT Tag
        /* this is not a structure definition
         * we are using a structure
         * it must be defined
         */
        entry->name = Strdup(child_2(root)->child->value.string_value);
        old = hash_table_search(structure_symbol_table, entry);
        if(!old) {
            semantic_error(UNDEFINED_STRUCTURE, entry->line_no, entry->name);
            return NULL;
        }
        else
            return old->type;
    }
}

void handle_DefList(struct syntax_node *root) {
    if(!root->is_empty) {
        // ExtDefList : ExtDef ExtDefList
        handle_Def(child_1(root));
        handle_DefList(child_2(root));
    }
}

void handle_Def(struct syntax_node *root) {
    struct syntax_node *specifier = child_1(root);
    struct semantic_type *type = handle_Specifier(specifier);
    // ExtDef : Specifier DecList SEMI
    if(child_2(root)->node_type == DecList) {
        handle_DecList(child_2(root), type);
    }
}

void handle_DecList(struct syntax_node *root, struct semantic_type *type) {
    handle_Dec(child_1(root), type);
    if(child_1(root)->next) {
        // DecList : Dec COMMA DecList
        handle_DecList(child_3(root), type);
    }
}

void handle_Dec(struct syntax_node *root, struct semantic_type *type) {
    struct syntax_node *var_dec = child_1(root);
    struct semantic_type *t = handle_VarDec(var_dec, type);

    if(var_dec->next) {
        // Dec : VarDec ASSIGNOP Exp
        if(get_inner_most_scope_type() == STRUCTURE_SCOPE) {
            sprintf(msg_buffer, "Structure field initialized at definition");
            semantic_error(STRUCTURE_FIELD_ERROR, child_2(root)->line_no, msg_buffer);
        }
        else {
            struct semantic_type *exp_type = NULL;
            int exp_is_left_value = 0;
            exp_type = handle_Exp(child_3(root), &exp_is_left_value);
            if(!t || !exp_type ||
                    !compare_semantic_type(t, exp_type) ||
                    t->kind == ARRAY) {
                // only basic and structure types can be assigned directly
                semantic_error(ASSIGNMENT_TYPE_MISMATCH, child_2(root)->line_no);
            }
        }
    }
}

struct function_symbol_table_entry * handle_FunDec(struct syntax_node *root, struct semantic_type *type) {
    struct syntax_node *id = child_1(root);
    struct function_symbol_table_entry *entry = 
        Calloc(1, sizeof(struct function_symbol_table_entry));
    entry->name = Strdup(id->value.string_value);
    entry->return_type = type;
    entry->line_no = id->line_no;
    // create a new scope, parameters will be put into it
    create_scope(VARIABLE_SCOPE);
    if(child_3(root)->node_type == VarList) {
        // FunDec : ID LP VarList RP
        // this add parameters to the inner most scope
        int count = handle_VarList(child_3(root));
        entry->argc = count;
        entry->args = Calloc(count, sizeof(struct semantic_type *));
        int i = 0;
        struct hash_node **top = cstack_top(variable_scopes);
        struct hash_node *curr = *top;
        while(curr) {
            struct variable_symbol_table_entry *e = curr->elem;
            entry->args[i] = e->type;
            curr = curr->brother;
            i++;
        }
    }
    else {
        // FunDec : ID LP RP
        entry->argc = 0;
        entry->args = NULL;
    }
    return entry;
}

// return the number of parameters
int handle_VarList(struct syntax_node *root) {
    int count = 1;
    handle_ParamDec(child_1(root));
    if(num_child(root) > 1) {
        // VarList : ParamDec COMMA VarList
        count += handle_VarList(child_3(root));
    }
    return count;
}

void handle_ParamDec(struct syntax_node *root) {
    // ParamDec : Specifier VarDec
    struct semantic_type *type = handle_Specifier(child_1(root));
    handle_VarDec(child_2(root), type);
}

void handle_CompSt(struct syntax_node *root, struct semantic_type *function_return_type) {
    // CompSt : LC DefList StmtList RC
    handle_DefList(child_2(root));
    handle_StmtList(child_3(root), function_return_type);
}

void handle_StmtList(struct syntax_node *root, struct semantic_type *function_return_type) {
    if(!root->is_empty) {
        // StmtList : Stmt StmtList
        handle_Stmt(child_1(root), function_return_type);
        handle_StmtList(child_2(root), function_return_type);
    }
}

void handle_Stmt(struct syntax_node *root, struct semantic_type *function_return_type) {
    int is_left_value = 0;
    struct semantic_type *exp_type = NULL;
    switch(child_1(root)->node_type) {
        case Exp:
            // Stmt : Exp SEMI
            handle_Exp(child_1(root), &is_left_value);
            break;
        case CompSt:
            // Stmt : CompSt
            create_scope(VARIABLE_SCOPE);
            handle_CompSt(child_1(root), function_return_type);
            delete_scope();
            break;
        case RETURN:
            // Stmt : RETURN Exp SEMI
            exp_type = handle_Exp(child_2(root), &is_left_value);
            if(!compare_semantic_type(function_return_type, exp_type))
                semantic_error(RETURN_TYPE_MISMATCH, child_1(root)->line_no);
            break;
        case IF:
            // Stmt : IF LP Exp RP Stmt
            // Stmt : IF LP Exp RP Stmt ELSE Stmt
            exp_type = handle_Exp(child_3(root), &is_left_value);
            /* condition must be of basic type
             * float type is OK, I have tried with clang
             * when float value != 0.0, it's true
             * else it's false.
             * Just like with integer
             */
            if(!exp_type || exp_type->kind != BASIC ||
                    exp_type->u.basic != INT) {
                sprintf(msg_buffer, "\"if\" expects condition of integer type");
                semantic_error(OPERANDS_TYPE_MISMATCH, 
                        child_1(root)->line_no, msg_buffer);
            }
            handle_Stmt(child_5(root), function_return_type);
            if(num_child(root) > 5)
                handle_Stmt(child_7(root), function_return_type);
            break;
        case WHILE:
            // Stmt : WHILE LP Exp RP Stmt
            exp_type = handle_Exp(child_3(root), &is_left_value);
            if(!exp_type || exp_type->kind != BASIC ||
                    exp_type->u.basic != INT) {
                sprintf(msg_buffer, "\"while\" expects condition of integer type");
                semantic_error(OPERANDS_TYPE_MISMATCH, 
                        child_1(root)->line_no, msg_buffer);
            }
            handle_Stmt(child_5(root), function_return_type);
            break;
        default:
            break;
    }
}

/* return the type of the expresession
 * is_left_value is set to indicate the left/right value type of the expresession
 */
struct semantic_type *handle_Exp(struct syntax_node *root, int *is_left_value) {
    struct semantic_type *ret = NULL;
    struct variable_symbol_table_entry *entry = NULL, *old = NULL;
    struct semantic_type *exp1_type = NULL, *exp2_type = NULL;
    int exp1_is_left_value, exp2_is_left_value;

    switch(child_1(root)->node_type) {
        case Exp:
            exp1_type = handle_Exp(child_1(root), &exp1_is_left_value);
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
                    exp2_type = handle_Exp(child_3(root), &exp2_is_left_value);
                    if(!exp1_type || !exp2_type || exp1_type->kind != BASIC || 
                            exp2_type->kind != BASIC || 
                            exp1_type->u.basic != exp2_type->u.basic) {
                        sprintf(msg_buffer, "arithmetic and relational operators expect operand of basic type");
                        semantic_error(OPERANDS_TYPE_MISMATCH, 
                                child_2(root)->line_no, msg_buffer);
                        ret = NULL;
                    }
                    else {
                        if(child_2(root)->node_type == RELOP) {
                            ret = Calloc(1, sizeof(struct semantic_type));
                            ret->kind = BASIC;
                            ret->u.basic = INT;
                        }
                        else
                            ret = exp1_type;
                    }
                    *is_left_value = 0;
                    break;
                case AND:
                case OR:
                    /*
                     * Exp : Exp AND Exp
                     * Exp : Exp OR Exp
                     */
                    exp2_type = handle_Exp(child_3(root), &exp2_is_left_value);
                    if(!exp1_type || !exp2_type || exp1_type->kind != BASIC || 
                            exp2_type->kind != BASIC || 
                            exp1_type->u.basic != INT ||
                            exp2_type->u.basic != INT) {
                        sprintf(msg_buffer, "logical operators expect operand of basic type");
                        semantic_error(OPERANDS_TYPE_MISMATCH, 
                                child_2(root)->line_no, msg_buffer);
                        ret = NULL;
                    }
                    else
                        ret = exp1_type;
                    *is_left_value = 0;
                    break;
                case ASSIGNOP:
                    // Exp : Exp ASSIGNOP Exp
                    exp2_type = handle_Exp(child_3(root), &exp2_is_left_value);
                    if(!exp1_is_left_value) {
                        semantic_error(NOT_LEFT_VALUE, child_2(root)->line_no);
                        ret = NULL;
                    }else if(!exp1_type || !exp2_type ||
                            !compare_semantic_type(exp1_type, exp2_type) ||
                            exp1_type->kind == ARRAY) {
                        // only basic and structure types can be assigned directly
                        semantic_error(ASSIGNMENT_TYPE_MISMATCH, child_2(root)->line_no);
                        ret = NULL;
                    }
                    else
                        ret = exp1_type;
                    *is_left_value = 0;
                    break;
                case LB:
                    // array
                    // Exp : Exp LB Exp RB
                    exp2_type = handle_Exp(child_3(root), &exp2_is_left_value);
                    if(!exp1_type || exp1_type->kind != ARRAY) {
                        semantic_error(NOT_AN_ARRAY, child_2(root)->line_no);
                        ret = NULL;
                    }
                    else {
                        if(!exp2_type || exp2_type->kind != BASIC || 
                                exp2_type->u.basic != INT)
                            semantic_error(ARRAY_INDEX_NOT_INTEGER, child_2(root)->line_no);
                        ret = exp1_type->u.array.elem;
                    }
                    *is_left_value = 1;
                    break;
                case DOT:
                    // structure
                    // Exp : Exp DOT ID
                    if(!exp1_type || exp1_type->kind != STRUCTURE) {
                        semantic_error(NOT_A_STRUCTURE, child_2(root)->line_no);
                        ret = NULL;
                    }
                    else {
                        // check whether this field exists
                        struct structure_field *field = exp1_type->u.structure.field;
                        int found = 0;
                        while(field) {
                            if(!strcmp(field->name, child_3(root)->value.string_value)) {
                                found = 1;
                                break;
                            }
                            field = field->next;
                        }
                        if(!found) {
                            semantic_error(NON_EXISTEND_FIELD, child_2(root)->line_no, 
                                    child_3(root)->value.string_value);
                            ret = NULL;
                        }
                        else
                            ret = field->type;
                    }
                    *is_left_value = 1;
                    break;
                default:
                    break;
            }
            break;
        case LP:
            // Exp : LP Exp RP
            exp1_type = handle_Exp(child_2(root), &exp1_is_left_value);
            ret = exp1_type;
            *is_left_value = exp1_is_left_value;
            break;
        case MINUS:
            // Exp : NOT Exp
            exp1_type = handle_Exp(child_2(root), &exp1_is_left_value);
            if(!exp1_type || exp1_type->kind != BASIC) {
                sprintf(msg_buffer, "arithmetic operators expect operand of basic type");
                semantic_error(OPERANDS_TYPE_MISMATCH, 
                        child_1(root)->line_no, msg_buffer);
                ret = NULL;
            }
            else
                ret = exp1_type;
            *is_left_value = 0;
            break;
        case NOT:
            // Exp : NOT Exp
            exp1_type = handle_Exp(child_2(root), &exp1_is_left_value);
            if(!exp1_type || exp1_type->kind != BASIC ||
                    exp1_type->u.basic != INT) {
                sprintf(msg_buffer, "logical operators expect operand of basic type");
                semantic_error(OPERANDS_TYPE_MISMATCH, 
                        child_1(root)->line_no, msg_buffer);
                ret = NULL;
            }
            else
                ret = exp1_type;
            *is_left_value = 0;
            break;
        case ID:
            if(num_child(root) > 1) {
                // function call
                struct function_symbol_table_entry *entry = 
                    Calloc(1, sizeof(struct function_symbol_table_entry));
                entry->name = Strdup(child_1(root)->value.string_value);
                entry->line_no = child_1(root)->line_no;
                struct function_symbol_table_entry *old = NULL;
                // check whether this function has been defined
                old = hash_table_search(function_definition_symbol_table, entry);

                // if not defined check whether this function has been declared
                if(!old)
                    old = hash_table_search(function_declaration_symbol_table, entry);

                if(!old) {
                    // check whether it's a variable
                    struct variable_symbol_table_entry *e = 
                        Calloc(1, sizeof(struct variable_symbol_table_entry));
                    e->name = Strdup(child_1(root)->value.string_value);
                    e->line_no = child_1(root)->line_no;
                    struct variable_symbol_table_entry *v = NULL;
                    v = hash_table_search(variable_symbol_table, entry);
                    if(v)
                        // use "()" with variables
                        semantic_error(NOT_A_FUNCTION, entry->line_no, entry->name);
                    else
                        // we have never seen this name
                        semantic_error(UNDEFINED_FUNCTION, entry->line_no, entry->name);
                    ret = NULL;
                }
                else {
                    // check for arguments
                    int argc = 0;
                    struct semantic_type **arg_types = NULL;
                    if(child_3(root)->node_type == Args) {
                        // function call with arguments
                        // Exp : ID LP Args RP
                        arg_types = handle_Args(child_3(root), &argc);
                    }
                    if(argc != old->argc)
                        goto function_parameter_mismatch;
                    for(int i = 0; i < argc; i++)
                        if(!compare_semantic_type(arg_types[i], old->args[i]))
                            goto function_parameter_mismatch;

                    goto function_parameter_match;

function_parameter_mismatch:
                    semantic_error(FUNCTION_TYPE_MISMATCH, entry->line_no, entry->name);
function_parameter_match:
                    ret = old->return_type;
                }
                *is_left_value = 0;
            }
            else {
                /* simply a variable
                 * we look it up in the variable_symbol_table
                 */
                entry = Calloc(1, sizeof(struct variable_symbol_table_entry));
                entry->name = Strdup(child_1(root)->value.string_value);
                entry->line_no = child_1(root)->line_no;
                old = hash_table_search(variable_symbol_table, entry);
                if(!old) {
                    semantic_error(UNDEFINED_VARIABLE, entry->line_no, entry->name);
                    ret = NULL;
                }
                else
                    ret = old->type;
                *is_left_value = 1;
            }
            break;
        case INT:
        case FLOAT:
            // Exp : INT
            // Exp : FLOAT
            ret = Calloc(1, sizeof(struct semantic_type));
            ret->kind = BASIC;
            ret->u.basic = child_1(root)->node_type;
            *is_left_value = 0;
            break;
        default:
            break;
    }
    return ret;
}

struct semantic_type **handle_Args(struct syntax_node *root, int *argc) {
    int is_left_value = 0;
    struct semantic_type *exp_type = handle_Exp(child_1(root), &is_left_value);
    struct semantic_type **ret = NULL, **child_ret = NULL;
    if(num_child(root) > 1) {
        // Args : Exp COMMA Args
        int count = 0;
        child_ret = handle_Args(child_3(root), &count);
        *argc = count + 1;
        ret = Calloc(*argc, sizeof(struct semantic_type *));
        memcpy(&ret[1], child_ret, count * sizeof(struct semantic_type *));
    }
    else {
        // Args : Exp
        *argc = 1;
        ret = Calloc(*argc, sizeof(struct semantic_type *));
    }
    ret[0] = exp_type;
    return ret;
}

static char *error_msg_format[] = {
    "Undefined variable \"%s\"",
    "Undefined function \"%s\"",
    "Redefined variable \"%s\"",
    "Redefined function \"%s\"",
    "Type mismatched for assignment",
    "The left-hand side of an assignment must be a variable",
    "%s",
    "Type mismatched for return",
    "Function \"%s\" is called with wrong arguments",
    "Not an array",
    "\"%s\" is not a function",
    "Array Index not an integer",
    "Illegal use of \".\"",
    "Non-existent field \"%s\"",
    "%s",
    "Duplicated name \"%s\"",
    "Undefined structure \"%s\"",
    "Function \"%s\" declared but no defined",
    "%s"
};

void semantic_error(int error_type, int line_no, ...) {
    va_list args;
    va_start(args, line_no);          
    printf("Error type %d at Line %d: ", error_type + 1, line_no);
    vprintf(error_msg_format[error_type], args);
    va_end(args);
    printf(".\n");
}

// only printf in debug mode
void dbg_printf(const char *format, ...) {
    if(DEBUG) {
        va_list args;
        va_start(args, format); 
        vprintf(format, args);
        va_end(args);
    }
}

void print_variable_symbol_table_entry(struct variable_symbol_table_entry *entry) {
    dbg_printf("(%s, ", entry->name);
    switch(entry->type->kind) {
        case BASIC:
            dbg_printf("BASIC");
            break;
        case STRUCTURE:
            dbg_printf("STRUCTURE");
            break;
        case ARRAY:
            dbg_printf("ARRAY");
            break;
        default:
            break;
    }
    dbg_printf(", %d)\n", entry->line_no);
}

void print_semantic_type(struct semantic_type *type) {
    if(!type) {
        dbg_printf("NULL");
        return;
    }
    switch(type->kind) {
        case BASIC:
            dbg_printf("BASIC");
            break;
        case STRUCTURE:
            dbg_printf("STRUCTURE");
            break;
        case ARRAY:
            dbg_printf("ARRAY");
            break;
        default:
            break;
    }
}
