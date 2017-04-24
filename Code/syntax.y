%{
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "syntax.tab.h"
#include "syntax.h"
struct syntax_node *root;
struct syntax_node *create_nonterminal_node(int node_type, int argc, ...);
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

%token <node_value> INT FLOAT ID TYPE
%token <node_value> STRUCT RETURN IF ELSE WHILE
%token <node_value> PLUS MINUS STAR DIV
%token <node_value> AND OR NOT
%token <node_value> DOT SEMI COMMA ASSIGNOP RELOP 
%token <node_value> LP RP LB RB LC RC
%token <node_value> NONTREMINAL

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
    $$ = create_nonterminal_node(Program, 1, $1);
    root = $$;
}
;

ExtDefList : {
    $$ = create_nonterminal_node(ExtDefList, 0);
}
|ExtDef ExtDefList {
    $$ = create_nonterminal_node(ExtDefList, 2, $1, $2);
}
;

ExtDef : Specifier ExtDecList SEMI {
    $$ = create_nonterminal_node(ExtDef, 3, $1, $2, $3);
}
| Specifier SEMI {
    $$ = create_nonterminal_node(ExtDef, 2, $1, $2);
}
| error SEMI {
    yyerrok;
    is_successful = 0;
    $$ = create_nonterminal_node(ExtDef, 0);
}
| Specifier FunDec CompSt {
    $$ = create_nonterminal_node(ExtDef, 3, $1, $2, $3);
}
;

ExtDecList : VarDec {
    $$ = create_nonterminal_node(ExtDecList, 1, $1);
}
| VarDec COMMA ExtDecList {
    $$ = create_nonterminal_node(ExtDecList, 3, $1, $2, $3);
}
;

/* Specifiers */

Specifier : TYPE {
    $$ = create_nonterminal_node(Specifier, 1, $1);
}
| StructSpecifier {
    $$ = create_nonterminal_node(Specifier, 1, $1);
}
;

StructSpecifier : STRUCT OptTag LC DefList RC {
    $$ = create_nonterminal_node(StructSpecifier, 5, $1, $2, $3, $4, $5);
}
| STRUCT OptTag LC error RC {
    yyerrok;
    is_successful = 0;
    $$ = create_nonterminal_node(StructSpecifier, 0);
}
| STRUCT Tag {
    $$ = create_nonterminal_node(StructSpecifier, 2, $1, $2);
}
;

OptTag : {
    $$ = create_nonterminal_node(OptTag, 0);
}
| ID {
    $$ = create_nonterminal_node(OptTag, 1, $1);
}
;

Tag : ID {
    $$ = create_nonterminal_node(Tag, 1, $1);
}
;

/* Declarators */

VarDec : ID {
    $$ = create_nonterminal_node(VarDec, 1, $1);
}
| VarDec LB INT RB {
    $$ = create_nonterminal_node(VarDec, 4, $1, $2, $3, $4);
}
| VarDec LB error RB {
    yyerrok;
    is_successful = 0;
    $$ = create_nonterminal_node(VarDec, 0);
}
;

FunDec : ID LP VarList RP {
    $$ = create_nonterminal_node(FunDec, 4, $1, $2, $3, $4);
}
| ID LP error RP {
    yyerrok;
    is_successful = 0;
    $$ = create_nonterminal_node(FunDec, 0);
}
| ID LP RP {
    $$ = create_nonterminal_node(FunDec, 3, $1, $2, $3);
}
;

VarList : ParamDec COMMA VarList {
    $$ = create_nonterminal_node(VarList, 3, $1, $2, $3);
}
| ParamDec {
    $$ = create_nonterminal_node(VarList, 1, $1);
}
;

ParamDec : Specifier VarDec {
    $$ = create_nonterminal_node(ParamDec, 2, $1, $2);
}
;

/* Statements */

CompSt : LC DefList StmtList RC {
    $$ = create_nonterminal_node(CompSt, 4, $1, $2, $3, $4);
}
| LC error RC {
    yyerrok;
    is_successful = 0;
    $$ = create_nonterminal_node(CompSt, 0);
}
;

StmtList : {
    $$ = create_nonterminal_node(StmtList, 0);
}
| Stmt StmtList {
    $$ = create_nonterminal_node(StmtList, 2, $1, $2);
}
;

Stmt : Exp SEMI {
    $$ = create_nonterminal_node(Stmt, 2, $1, $2);
}
| CompSt {
    $$ = create_nonterminal_node(Stmt, 1, $1);
}
| RETURN Exp SEMI {
    $$ = create_nonterminal_node(Stmt, 3, $1, $2, $3);
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
     * or its parent will encounter an segment fault when call create_nonterminal_node
     */
    $$ = create_nonterminal_node(Stmt, 0);
}
| IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {
    $$ = create_nonterminal_node(Stmt, 5, $1, $2, $3, $4, $5);
}
| IF LP error RP Stmt %prec LOWER_THAN_ELSE {
    yyerrok;
    is_successful = 0;
    $$ = create_nonterminal_node(Stmt, 0);
}
| IF LP Exp RP Stmt ELSE Stmt {
    $$ = create_nonterminal_node(Stmt, 7, $1, $2, $3, $4, $5, $6, $7);
}
| IF LP error RP Stmt ELSE Stmt {
    yyerrok;
    is_successful = 0;
    $$ = create_nonterminal_node(Stmt, 0);
}
| WHILE LP Exp RP Stmt {
    $$ = create_nonterminal_node(Stmt, 5, $1, $2, $3, $4, $5);
}
| WHILE LP error RP Stmt {
    yyerrok;
    is_successful = 0;
    $$ = create_nonterminal_node(Stmt, 0);
}
;

/* Local Definitions */

DefList : {
    $$ = create_nonterminal_node(DefList, 0);
}
| Def DefList {
    $$ = create_nonterminal_node(DefList, 2, $1, $2);
}
;

Def : Specifier DecList SEMI {
    $$ = create_nonterminal_node(Def, 3, $1, $2, $3);
}
| error SEMI {
    yyerrok;
    is_successful = 0;
    $$ = create_nonterminal_node(Def, 0);
}
;

DecList : Dec {
    $$ = create_nonterminal_node(DecList, 1, $1);
}
| Dec COMMA DecList {
    $$ = create_nonterminal_node(DecList, 3, $1, $2, $3);
}
;

Dec : VarDec {
    $$ = create_nonterminal_node(Dec, 1, $1);
}
| VarDec ASSIGNOP Exp {
    $$ = create_nonterminal_node(Dec, 3, $1, $2, $3);
}
;

/* Expressions */

Exp : Exp ASSIGNOP Exp {
    $$ = create_nonterminal_node(Exp, 3, $1, $2, $3);
}
| Exp AND Exp {
    $$ = create_nonterminal_node(Exp, 3, $1, $2, $3);
}
| Exp OR Exp {
    $$ = create_nonterminal_node(Exp, 3, $1, $2, $3);
}
| Exp RELOP Exp {
    $$ = create_nonterminal_node(Exp, 3, $1, $2, $3);
}
| Exp PLUS Exp {
    $$ = create_nonterminal_node(Exp, 3, $1, $2, $3);
}
| Exp MINUS Exp {
    $$ = create_nonterminal_node(Exp, 3, $1, $2, $3);
}
| Exp STAR Exp {
    $$ = create_nonterminal_node(Exp, 3, $1, $2, $3);
}
| Exp DIV Exp {
    $$ = create_nonterminal_node(Exp, 3, $1, $2, $3);
}
| LP Exp RP {
    $$ = create_nonterminal_node(Exp, 3, $1, $2, $3);
}
| LP error RP {
    yyerrok;
    is_successful = 0;
    $$ = create_nonterminal_node(Exp, 0);
}
| MINUS Exp %prec UNARY_MINUS {
    $$ = create_nonterminal_node(Exp, 2, $1, $2);
}
| NOT Exp {
    $$ = create_nonterminal_node(Exp, 2, $1, $2);
}
| ID LP Args RP {
    $$ = create_nonterminal_node(Exp, 4, $1, $2, $3, $4);
}
| ID LP error RP {
    yyerrok;
    is_successful = 0;
    $$ = create_nonterminal_node(Exp, 0);
}
| ID LP RP {
    $$ = create_nonterminal_node(Exp, 3, $1, $2, $3);
}
| Exp LB Exp RB {
    $$ = create_nonterminal_node(Exp, 4, $1, $2, $3, $4);
}
| Exp LB error RB {
    yyerrok;
    is_successful = 0;
    $$ = create_nonterminal_node(Exp, 0);
}
| Exp DOT ID {
    $$ = create_nonterminal_node(Exp, 3, $1, $2, $3);
}
| ID {
    $$ = create_nonterminal_node(Exp, 1, $1);
}
| INT {
    $$ = create_nonterminal_node(Exp, 1, $1);
}
| FLOAT {
    $$ = create_nonterminal_node(Exp, 1, $1);
}
;

Args : Exp COMMA Args {
    $$ = create_nonterminal_node(Args, 3, $1, $2, $3);
}
| Exp {
    $$ = create_nonterminal_node(Args, 1, $1);
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

struct syntax_node *create_nonterminal_node(int node_type, int argc, ...) {
    struct syntax_node *head = NULL, *curr = NULL, *next = NULL;
    va_list args;

    va_start(args, argc);          
    for(int i = 0; i < argc; i++ ) {
        next = va_arg(args, struct syntax_node *); 
        /* first one */
        if(!head) {
            head = curr = next;
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

    struct syntax_node *ret = Calloc(1, sizeof(struct syntax_node));
    ret->node_type = node_type;
    ret->prev = ret->next = NULL;
    ret->child = head;
    ret->is_empty = 1;
    if(argc > 0) {
        ret->is_empty = 0;
        ret->line_no = head->line_no;
    }
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

int is_terminal(int node_type) {
    return node_type >= INT && node_type <= RC;
}

void print_syntax_node(struct syntax_node * node) {
    int node_type = node->node_type;
    printf("%s", get_syntax_node_name(node_type));
    if(!is_terminal(node_type))
        printf(" (%d)", node->line_no);
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
