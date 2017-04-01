#ifndef SYNTAX_H
#define SYNTAX_H
#include "syntax.tab.h"

/* these enum values should follow the enum values 
 * of meaningful tokens(NONTREMINAL, UNARY_MINUS, LOWER_THAN_ELSE excluded)
 * in yytokentype in "syntax.tab.h"
 * be careful not to clash with them
 */
enum node_types {
    Program = NONTREMINAL, ExtDefList, ExtDef, Specifier, ExtDecList,
    FunDec, CompSt, VarDec, StructSpecifier, Tag, OptTag, VarList,
    ParamDec, StmtList, Stmt, Exp, DefList, Def, Dec, DecList, Args, EMPTY_PRODUCTION_RULE
};

union token_value {
    int int_value;
    float float_value;
    char *string_value;
};

struct syntax_node {
    int node_type;
    /* produce an empty string */
    int is_empty;
    union token_value value;
    struct syntax_node *prev, *next, *child;
};
char *get_syntax_node_name(int node_type);
void print_syntax_node(struct syntax_node * node);
void delete_syntax_tree(struct syntax_node *root);
void print_syntax_tree(struct syntax_node *root, int indent_level);
#endif
