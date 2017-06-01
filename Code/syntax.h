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
    int line_no;
    int node_type;
    /* produce an empty string */
    int is_empty;
    union token_value value;
    struct syntax_node *prev, *next, *child;
};

void delete_syntax_tree(struct syntax_node *root);
void print_syntax_tree(struct syntax_node *root, int indent_level);
struct syntax_node *find_child(struct syntax_node *root, int id);
int num_child(struct syntax_node *root);
struct syntax_node *child_1(struct syntax_node *root);
struct syntax_node *child_2(struct syntax_node *root);
struct syntax_node *child_3(struct syntax_node *root);
struct syntax_node *child_4(struct syntax_node *root);
struct syntax_node *child_5(struct syntax_node *root);
struct syntax_node *child_6(struct syntax_node *root);
struct syntax_node *child_7(struct syntax_node *root);
#endif
