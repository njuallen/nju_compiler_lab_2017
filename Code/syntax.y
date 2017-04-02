%{
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "syntax.tab.h"
#include "syntax.h"
struct syntax_node *root;
struct syntax_node *create_node(int node_type, int is_empty);
struct syntax_node *connect_node(int argc, ...);
/* use this to let main function know:
 * whether there is no error
 * or we have done some error recovery and 
 * successfully built a syntax tree
 */
int is_successful = 1;
%}

%locations
%define parse.error verbose

/* declared types */
%union {
    int int_value;
    float float_value;
    char *string_value;
    struct syntax_node *node_value;
}

%token <int_value> INT <float_value> FLOAT <string_value> ID <string_value> TYPE
%token STRUCT RETURN IF ELSE WHILE
%token PLUS MINUS STAR DIV
%token AND OR NOT
%token DOT SEMI COMMA ASSIGNOP <string_value> RELOP 
%token LP RP LB RB LC RC
%token NONTREMINAL

/* type of nonterminals */
%type <node_value> Program ExtDefList ExtDef Specifier ExtDecList
%type <node_value> FunDec CompSt VarDec StructSpecifier Tag OptTag VarList
%type <node_value> ParamDec StmtList Stmt Exp DefList Def Dec DecList Args

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT UNARY_MINUS
%left LP RP LB RB DOT

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

/* High-level Definitions */

Program : ExtDefList {
    $$ = create_node(Program, 0);
    $$->child = connect_node(1, $1);
    root = $$;
}
;

ExtDefList : {
    $$ = create_node(ExtDefList, 1);
}
|ExtDef ExtDefList {
    $$ = create_node(ExtDefList, 0);
    $$->child = connect_node(2, $1, $2);
}
;

ExtDef : Specifier ExtDecList SEMI {
    struct syntax_node *semi = create_node(SEMI, 0);
    $$ = create_node(ExtDef, 0);
    $$->child = connect_node(3, $1, $2, semi);
}
| Specifier SEMI {
    struct syntax_node *semi = create_node(SEMI, 0);
    $$ = create_node(ExtDef, 0);
    $$->child = connect_node(2, $1, semi);
}
| error SEMI {
    yyerrok;
    is_successful = 0;
    $$ = create_node(ExtDef, 1);
}
| Specifier FunDec CompSt {
    $$ = create_node(ExtDef, 0);
    $$->child = connect_node(3, $1, $2, $3);
}
;

ExtDecList : VarDec {
    $$ = create_node(ExtDecList, 0);
    $$->child = connect_node(1, $1);
}
| VarDec COMMA ExtDecList {
    struct syntax_node *comma = create_node(COMMA, 0);
    $$ = create_node(ExtDecList, 0);
    $$->child = connect_node(3, $1, comma, $3);
}
;

/* Specifiers */

Specifier : TYPE {
    struct syntax_node *type = create_node(TYPE, 0);
    type->value.string_value = $1;
    $$ = create_node(Specifier, 0);
    $$->child = connect_node(1, type);
}
| StructSpecifier {
    $$ = create_node(Specifier, 0);
    $$->child = connect_node(1, $1);
}
;

StructSpecifier : STRUCT OptTag LC DefList RC {
    struct syntax_node *structure = create_node(STRUCT, 0);
    struct syntax_node *lc = create_node(LC, 0);
    struct syntax_node *rc = create_node(RC, 0);
    $$ = create_node(StructSpecifier, 0);
    $$->child = connect_node(5, structure, $2, lc, $4, rc);
}
| STRUCT OptTag LC error RC {
    yyerrok;
    is_successful = 0;
    $$ = create_node(StructSpecifier, 1);
}
| STRUCT Tag {
    struct syntax_node *structure = create_node(STRUCT, 0);
    $$ = create_node(StructSpecifier, 0);
    $$->child = connect_node(2, structure, $2);
}
;

OptTag : {
    $$ = create_node(OptTag, 1);
}
| ID {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = $1;
    $$ = create_node(OptTag, 0);
    $$->child = connect_node(1, id);
}
;

Tag : ID {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = $1;
    $$ = create_node(Tag, 0);
    $$->child = connect_node(1, id);
}
;

/* Declarators */

VarDec : ID {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = $1;
    $$ = create_node(VarDec, 0);
    $$->child = connect_node(1, id);
}
| VarDec LB INT RB {
    struct syntax_node *lb = create_node(LB, 0);
    struct syntax_node *integer = create_node(INT, 0);
    integer->value.int_value = $3;
    struct syntax_node *rb = create_node(RB, 0);
    $$ = create_node(VarDec, 0);
    $$->child = connect_node(4, $1, lb, integer, rb);
}
| VarDec LB error RB {
    yyerrok;
    is_successful = 0;
    $$ = create_node(VarDec, 1);
}
;

FunDec : ID LP VarList RP {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = $1;
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    $$ = create_node(FunDec, 0);
    $$->child = connect_node(4, id, lp, $3, rp);
}
| ID LP error RP {
    yyerrok;
    is_successful = 0;
    $$ = create_node(FunDec, 1);
}
| ID LP RP {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = $1;
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    $$ = create_node(FunDec, 0);
    $$->child = connect_node(3, id, lp, rp);
}
;

VarList : ParamDec COMMA VarList {
    struct syntax_node *comma = create_node(COMMA, 0);
    $$ = create_node(VarList, 0);
    $$->child = connect_node(3, $1, comma, $3);
}
| ParamDec {
    $$ = create_node(VarList, 0);
    $$->child = connect_node(1, $1);
}
;

ParamDec : Specifier VarDec {
    $$ = create_node(ParamDec, 0);
    $$->child = connect_node(2, $1, $2);
}
;

/* Statements */

CompSt : LC DefList StmtList RC {
    struct syntax_node *lc = create_node(LC, 0);
    struct syntax_node *rc = create_node(RC, 0);
    $$ = create_node(CompSt, 0);
    $$->child = connect_node(4, lc, $2, $3, rc);
}
| LC error RC {
    yyerrok;
    is_successful = 0;
    $$ = create_node(CompSt, 1);
}
;

StmtList : {
    $$ = create_node(StmtList, 1);
}
| Stmt StmtList {
    $$ = create_node(StmtList, 0);
    $$->child = connect_node(2, $1, $2);
}
;

Stmt : Exp SEMI {
    struct syntax_node *semi = create_node(SEMI, 0);
    $$ = create_node(Stmt, 0);
    $$->child = connect_node(2, $1, semi);
}
| CompSt {
    $$ = create_node(Stmt, 0);
    $$->child = connect_node(1, $1);
}
| RETURN Exp SEMI {
    struct syntax_node *return_token = create_node(RETURN, 0);
    struct syntax_node *semi = create_node(SEMI, 0);
    $$ = create_node(Stmt, 0);
    $$->child = connect_node(3, return_token, $2, semi);
}
| error SEMI {
    /* according to this bison manual page
     * link : https://www.gnu.org/software/bison/manual/html_node/Error-Recovery.html#Error-Recovery
     * To prevent an outpouring of error messages, 
     * the parser will output no error message for another syntax 
     * error that happens shortly after the first; 
     * only after three consecutive input tokens have been successfully 
     * shifted will error messages resume. 
     *
     * But our compiler lab requires that for every syntax error line
     * we should output an syntax error message
     * So we use yyerrok to let bison return to its normal mode
     * so that consecutive errors will not be supressed
     */
    yyerrok;
    is_successful = 0;
    /* remember to create an empty production rule node for it
     * or its parent will encounter an segment fault when call connect_node
     */
    $$ = create_node(Stmt, 1);
}
| IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {
    struct syntax_node *if_token = create_node(IF, 0);
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    $$ = create_node(Stmt, 0);
    $$->child = connect_node(5, if_token, lp, $3, rp, $5);
}
| IF LP error RP Stmt %prec LOWER_THAN_ELSE {
    yyerrok;
    is_successful = 0;
    $$ = create_node(Stmt, 1);
}
| IF LP Exp RP Stmt ELSE Stmt {
    struct syntax_node *if_token = create_node(IF, 0);
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    struct syntax_node *else_token = create_node(ELSE, 0);
    $$ = create_node(Stmt, 0);
    $$->child = connect_node(7, if_token, lp, $3, rp, $5, else_token, $7);
}
| IF LP error RP Stmt ELSE Stmt {
    yyerrok;
    is_successful = 0;
    $$ = create_node(Stmt, 1);
}
| WHILE LP Exp RP Stmt {
    struct syntax_node *while_token = create_node(WHILE, 0);
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    $$ = create_node(Stmt, 0);
    $$->child = connect_node(5, while_token, lp, $3, rp, $5);
}
| WHILE LP error RP Stmt {
    yyerrok;
    is_successful = 0;
    $$ = create_node(Stmt, 1);
}
;

/* Local Definitions */

DefList : {
    $$ = create_node(DefList, 1);
}
| Def DefList {
    $$ = create_node(DefList, 0);
    $$->child = connect_node(2, $1, $2);
}
;

Def : Specifier DecList SEMI {
    struct syntax_node *semi = create_node(SEMI, 0);
    $$ = create_node(Def, 0);
    $$->child = connect_node(3, $1, $2, semi);
}
| error SEMI {
    yyerrok;
    is_successful = 0;
    $$ = create_node(Def, 1);
}
;

DecList : Dec {
    $$ = create_node(DecList, 0);
    $$->child = connect_node(1, $1);
}
| Dec COMMA DecList {
    struct syntax_node *comma = create_node(COMMA, 0);
    $$ = create_node(DecList, 0);
    $$->child = connect_node(3, $1, comma, $3);
}
;

Dec : VarDec {
    $$ = create_node(Dec, 0);
    $$->child = connect_node(1, $1);
}
| VarDec ASSIGNOP Exp {
    struct syntax_node *assignop = create_node(ASSIGNOP, 0);
    $$ = create_node(Dec, 0);
    $$->child = connect_node(3, $1, assignop, $3);
}
;

/* Expressions */

Exp : Exp ASSIGNOP Exp {
    struct syntax_node *assignop = create_node(ASSIGNOP, 0);
    $$ = create_node(Exp, 0);
    $$->child = connect_node(3, $1, assignop, $3);
}
| Exp AND Exp {
    struct syntax_node *and = create_node(AND, 0);
    $$ = create_node(Exp, 0);
    $$->child = connect_node(3, $1, and, $3);
}
| Exp OR Exp {
    struct syntax_node *or = create_node(OR, 0);
    $$ = create_node(Exp, 0);
    $$->child = connect_node(3, $1, or, $3);
}
| Exp RELOP Exp {
    struct syntax_node *relop = create_node(RELOP, 0);
    relop->value.string_value = $2;
    $$ = create_node(Exp, 0);
    $$->child = connect_node(3, $1, relop, $3);
}
| Exp PLUS Exp {
    struct syntax_node *plus = create_node(PLUS, 0);
    $$ = create_node(Exp, 0);
    $$->child = connect_node(3, $1, plus, $3);
}
| Exp MINUS Exp {
    struct syntax_node *minus = create_node(MINUS, 0);
    $$ = create_node(Exp, 0);
    $$->child = connect_node(3, $1, minus, $3);
}
| Exp STAR Exp {
    struct syntax_node *star = create_node(STAR, 0);
    $$ = create_node(Exp, 0);
    $$->child = connect_node(3, $1, star, $3);
}
| Exp DIV Exp {
    struct syntax_node *div = create_node(DIV, 0);
    $$ = create_node(Exp, 0);
    $$->child = connect_node(3, $1, div, $3);
}
| LP Exp RP {
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    $$ = create_node(Exp, 0);
    $$->child = connect_node(3, lp, $2, rp);
}
| LP error RP {
    yyerrok;
    is_successful = 0;
    $$ = create_node(Exp, 1);
}
| MINUS Exp %prec UNARY_MINUS {
    struct syntax_node *minus = create_node(MINUS, 0);
    $$ = create_node(Exp, 0);
    $$->child = connect_node(2, minus, $2);
}
| NOT Exp {
    struct syntax_node *not = create_node(NOT, 0);
    $$ = create_node(Exp, 0);
    $$->child = connect_node(2, not, $2);
}
| ID LP Args RP {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = $1;
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    $$ = create_node(Exp, 0);
    $$->child = connect_node(4, id, lp, $3, rp);
}
| ID LP error RP {
    yyerrok;
    is_successful = 0;
    $$ = create_node(Exp, 1);
}
| ID LP RP {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = $1;
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    $$ = create_node(Exp, 0);
    $$->child = connect_node(3, id, lp, rp);
}
| Exp LB Exp RB {
    struct syntax_node *lb = create_node(LB, 0);
    struct syntax_node *rb = create_node(RB, 0);
    $$ = create_node(Exp, 0);
    $$->child = connect_node(4, $1, lb, $3, rb);
}
| Exp LB error RB {
    yyerrok;
    is_successful = 0;
    $$ = create_node(Exp, 1);
}
| Exp DOT ID {
    struct syntax_node *dot = create_node(DOT, 0);
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = $3;
    $$ = create_node(Exp, 0);
    $$->child = connect_node(3, $1, dot, id);
}
| ID {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = $1;
    $$ = create_node(Exp, 0);
    $$->child = connect_node(1, id);
}
| INT {
    struct syntax_node *integer = create_node(INT, 0);
    integer->value.int_value = $1;
    $$ = create_node(Exp, 0);
    $$->child = connect_node(1, integer);
}
| FLOAT {
    struct syntax_node *float_number = create_node(FLOAT, 0);
    float_number->value.float_value = $1;
    $$ = create_node(Exp, 0);
    $$->child = connect_node(1, float_number);
}
;

Args : Exp COMMA Args {
    struct syntax_node *comma = create_node(COMMA, 0);
    $$ = create_node(Args, 0);
    $$->child = connect_node(3, $1, comma, $3);
}
| Exp {
    $$ = create_node(Args, 0);
    $$->child = connect_node(1, $1);
}
;
%%

#include "lex.yy.c"

extern char *yytext;

/* do not print to stderr
 * or my testscript won't work
 */
void yyerror(char *s) {
    printf("Error type B at Line %d: %s.\n", 
        yylloc.first_line, s);
}

struct syntax_node *create_node(int node_type, int is_empty) {
    struct syntax_node *ret = Calloc(1, sizeof(struct syntax_node));
    ret->node_type = node_type;
    ret->is_empty = is_empty;
    ret->prev = ret->next = ret->child = NULL;
    return ret;
}

struct syntax_node *connect_node(int argc, ...) {
    struct syntax_node *ret = NULL, *curr = NULL, *next = NULL;
    va_list args;

    va_start(args, argc);           
    for(int i = 0; i < argc; i++ ) {
        next = va_arg(args, struct syntax_node *); 
        /* first one */
        if(!ret) {
            ret = curr = next;
            curr->prev = NULL;
        }
        else {
            curr->next = next;
            next->prev = curr;
            curr = next;
        }
        curr->next = NULL;
    }
    va_end(args);
    return ret;
}


/* be careful of the order here */
char *syntax_node_name_table[] = {
    "INT", "FLOAT", "ID", "TYPE",
    "STRUCT", "RETURN", "IF", "ELSE", "WHILE",
    "PLUS", "MINUS", "STAR", "DIV",
    "AND", "OR", "NOT",
    "DOT", "SEMI", "COMMA", "ASSIGNOP", "RELOP",
    "LP", "RP", "LB", "RB", "LC", "RC",
    "Program", "ExtDefList", "ExtDef", "Specifier", "ExtDecList",
    "FunDec", "CompSt", "VarDec", "StructSpecifier", "Tag", "OptTag", "VarList",
    "ParamDec", "StmtList", "Stmt", "Exp", "DefList", "Def", "Dec", "DecList", "Args"
};

char *get_syntax_node_name(int node_type) {
    assert(node_type >= INT && node_type <= Args);
    return syntax_node_name_table[node_type - INT];
}

void print_syntax_node(struct syntax_node * node) {
    int node_type = node->node_type;
    printf("%s", get_syntax_node_name(node_type));
    if(node_type == ID || node_type == TYPE)
        printf(": %s", node->value.string_value);
    if(node_type == INT)
        printf(": %d", node->value.int_value);
    if(node_type == FLOAT)
        printf(": %f", node->value.float_value);
}

void delete_syntax_node(struct syntax_node * node) {
    int node_type = node->node_type;
    if(node_type == ID || node_type == TYPE 
        || node_type == RELOP)
        Free(node->value.string_value);
    Free(node);
}

void print_syntax_tree(struct syntax_node *root, int indent_level) {
    /* we do not print invalid node and empty production rule node */
    if(!root || root->is_empty)
        return;
    /* each indentation level == 2 space */
    for(int i = 0; i < indent_level; i++)
        printf("  ");
    print_syntax_node(root);
    printf("\n");
    struct syntax_node *p = root->child;
    while(p) {
        print_syntax_tree(p, indent_level + 1);
        p = p->next;
    }
}

void delete_syntax_tree(struct syntax_node *root) {
    struct syntax_node *p = root->child;
    delete_syntax_node(root);
    while(p) {
        delete_syntax_node(p);
        p = p->next;
    }
}
