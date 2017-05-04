#include <stdarg.h>
#include "csapp.h"
#include "adt.h"
#include "syntax.h"
#include "semantic.h"

#define HASH_TABLE_SIZE 1024

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

struct hash_table *variable_symbol_table, *function_symbol_table,
                  *structure_symbol_table;

/* variable_scopes stores pointer to linked lists
 * each linked lists chain together variable definitions in the same scope
 * scope_types tells the type(VARIABLE_SCOPE/STRUCTURE_SCOPE) of each scope
 */
struct cstack *variable_scopes, *scope_types;

#define MAX_MSG_SIZE 1024;
char msg_buffer[1024];

enum scope_type {
    VARIABLE_SCOPE = 0,
    STRUCTURE_SCOPE
};


// find the id'th child of a parent node
struct syntax_node *find_child(struct syntax_node *root, int id) {
    struct syntax_node *ret = root->child;
    for(int i = 0; i < id - 1; i++) {
        if(!ret)
            app_error("Can not find specified child node");
        ret = ret->next;
    }
    if(!ret)
        app_error("Can not find specified child node");
    return ret;
}

#define child_number(id) \
struct syntax_node *child_##id(struct syntax_node *root) { \
    return find_child(root, id); \
} \

child_number(1);
child_number(2);
child_number(3);
child_number(4);
child_number(5);
child_number(6);
child_number(7);

#define MAX_NESTED_SCOPES 100

void handle_Program(struct syntax_node *root);
void handle_ExtDefList(struct syntax_node *root);
void handle_ExtDef(struct syntax_node *root);
void handle_ExtDecList(struct syntax_node *root, struct semantic_type *type);
void handle_VarDec(struct syntax_node *root, struct semantic_type *type);
struct semantic_type *handle_Specifier(struct syntax_node *root);
char *handle_OptTag(struct syntax_node *root);
char *handle_Tag(struct syntax_node *root);
void handle_DefList(struct syntax_node *root);
void handle_Def(struct syntax_node *root);
void handle_DecList(struct syntax_node *root, struct semantic_type *type);
void handle_Dec(struct syntax_node *root, struct semantic_type *type);
struct semantic_type *handle_StructSpecifier(struct syntax_node *root);
void semantic_error(int error_type, int line_no, ...);

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
    UNDEFINED_STRUCTURE
};

int check_semantics(struct syntax_node *root) {
    variable_symbol_table = 
        create_hash_table(HASH_TABLE_SIZE, hash_variable, compare_variable);
    function_symbol_table = 
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
    Free(cstack_pop(scope_types));
    struct hash_node **top = cstack_pop(variable_scopes);
    struct hash_node *curr = *top;
    while(curr) {
        struct hash_node *next = curr->brother;
        hash_table_delete(variable_symbol_table, curr);
        curr = next;
    }
    Free(top);
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
    delete_scope();
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
    // ExtDef : Specifier ExtDecList SEMI
    if(child_2(root)->node_type == ExtDecList) {
        handle_ExtDecList(child_2(root), type);
    }
}

void handle_ExtDecList(struct syntax_node *root, struct semantic_type *type) {
    struct syntax_node *var_dec = child_1(root);
    handle_VarDec(var_dec, type);

    // ExtDecList : VarDec COMMA ExtDecList
    if(var_dec->next)
        handle_ExtDecList(child_3(root), type);
}

void handle_VarDec(struct syntax_node *root, struct semantic_type *type) {
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
    }
    else {
        // VarDec : VarDec LB INT RB
        // array type
        struct semantic_type *ret = Calloc(1, sizeof(struct semantic_type));
        ret->kind = ARRAY;
        ret->u.array.elem = type;
        ret->u.array.size = child_3(root)->value.int_value;
        handle_VarDec(child_1(root), ret);
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
    handle_VarDec(var_dec, type);

    if(var_dec->next) {
        // Dec : VarDec ASSIGNOP Exp
        if(get_inner_most_scope_type() == STRUCTURE_SCOPE) {
            sprintf(msg_buffer, "Structure field initialized at definition");
            semantic_error(STRUCTURE_FIELD_ERROR, child_2(root)->line_no, msg_buffer);
        }
    }
}

static char *error_msg_format[] = {
    "Undefined variable \"%s\"",
    "Undefined function \"%s\"",
    "Redefined variable \"%s\"",
    "Redefined function \"%s\"",
    "Type mismatched for assignment",
    "The left-hand side of an assignment must be a variable",
    "Type mismatched for operands",
    "Type mismatched for return",
    "Function \"%s\" is not applicable for arguments \"%s\"",
    "\"%s\" is not an array",
    "\"%s\" is not a function",
    "\"%s\" is not an integer",
    "Illegal use of \".\"",
    "Non-existent field \"%s\"",
    "%s",
    "Duplicated name \"%s\"",
    "Undefined structure \"%s\""
};

void semantic_error(int error_type, int line_no, ...) {
    va_list args;
    va_start(args, line_no);          
    printf("Error type %d at Line %d: ", error_type, line_no);
    vprintf(error_msg_format[error_type], args);
    va_end(args);
    printf(".\n");
}
