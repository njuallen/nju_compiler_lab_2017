%{
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "syntax.tab.h"
#include "syntax.h"
#include "csapp.h"

int get_integer(int *val, int base, char *msg);
int get_float(float *val, char *msg);
void lexical_error(char *msg);
struct syntax_node *create_terminal_node(int node_type);

int yycolumn = 1;

#define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;
%}

%option yylineno

%x comment

digit [0-9]
digits {digit}+
letter [a-zA-Z]
letter_ ({letter}|_)

/* integer literal
 * read this link: http://en.cppreference.com/w/cpp/language/integer_literal
 */

/* decimal-literal is a non-zero decimal digit (1, 2, 3, 4, 5, 6, 7, 8, 9), 
 * followed by zero or more decimal digits (0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
 */
decimal ((0|([1-9]{digit}*)))

/* octal-literal is the digit zero (0) 
 * followed by zero or more octal digits (0, 1, 2, 3, 4, 5, 6, 7)
 * correct one: oct (0[0-7]*)
 * but we will use the one below to let strtol catch more errors for us
 */
oct (0{digit}*)

/* hex-literal is the character sequence 0x or the character sequence 0X 
 * followed by one or more hexadecimal digits 
 * (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, A, b, B, c, C, d, D, e, E, f, F) 
 * correct one: hex (0[xX][0-9a-fA-F]+)
 * but we will use the one below to let strtol catch more errors for us
 */
hex (0[xX]({digit}|{letter})+)

/* floating point literal
 * link: http://en.cppreference.com/w/cpp/language/floating_literal
 * correct exp_part should be: exp_part ([eE][+-]?{digits})
 * but we will use the one below to catch invalid float numbers with exponents
 */

significand_full {digits}\.{digits}
significand_no_integer \.{digits}
significand_no_fraction {digits}\.

/* define exp_part as this, so invalid float point numbers such as:
 * 1e+7.f1
 * 1E-7F
 */
exp_part ([eE][+-]?({digits}|{letter}|\.)*)
significand_with_dot ({significand_full}|{significand_no_integer}|{significand_no_fraction})
significand_without_dot {digits}
float_number (({significand_with_dot}{exp_part}?)|({significand_without_dot}{exp_part}))

/* identifiers
 * A valid identifier is a sequence of one or more letters, digits, 
 * or underscore characters (_). 
 * Spaces, punctuation marks, and symbols cannot be part of an identifier. 
 * In addition, identifiers shall always begin with a letter. 
 * They can also begin with an underline character (_), 
 * but such identifiers are -on most cases- considered 
 * reserved for compiler-specific keywords or external identifiers, 
 * as well as identifiers containing two successive underscore characters anywhere. 
 * In no case can they begin with a digit.
 */

identifier {letter_}({letter_}|{digit})*

white_spaces ([ \t]+)
%%
{decimal} {
    int val = 0;
    get_integer(&val, 10, "Illegal decimal number");
    /* even if it's a invalid integer
     * we return a token INT
     * so that parsing can go on
     */
    struct syntax_node *ret = create_terminal_node(INT);
    ret->value.int_value = val;
    yylval.node_value = ret;
    return INT;
}

{oct} {
    int val = 0;
    get_integer(&val, 8, "Illegal octal number");
    struct syntax_node *ret = create_terminal_node(INT);
    ret->value.int_value = val;
    yylval.node_value = ret;
    return INT;
}

{hex} {
    int val = 0;
    get_integer(&val, 16, "Illegal hexadecimal number");
    struct syntax_node *ret = create_terminal_node(INT);
    ret->value.int_value = val;
    yylval.node_value = ret;
    return INT;
}

{float_number} {
    float val = 0.0;
    get_float(&val, "Illegal float number");
    struct syntax_node *ret = create_terminal_node(FLOAT);
    ret->value.float_value = val;
    yylval.node_value = ret;
    return FLOAT;
}

";" { yylval.node_value = create_terminal_node(SEMI); return SEMI; }
"," { yylval.node_value = create_terminal_node(COMMA); return COMMA; }
"=" { yylval.node_value = create_terminal_node(ASSIGNOP); return ASSIGNOP; }
("<"|">"|">="|"<="|"!="|"==") { 
    struct syntax_node *ret = create_terminal_node(RELOP);
    ret->value.string_value = Strdup(yytext);
    yylval.node_value = ret;
    return RELOP;
}

"+" {
    struct syntax_node *ret = create_terminal_node(PLUS);
    ret->value.string_value = Strdup(yytext);
    yylval.node_value = ret;
    return PLUS;
}

"-" {
    struct syntax_node *ret = create_terminal_node(MINUS);
    ret->value.string_value = Strdup(yytext);
    yylval.node_value = ret;
    return MINUS;
}

"*" {
    struct syntax_node *ret = create_terminal_node(STAR);
    ret->value.string_value = Strdup(yytext);
    yylval.node_value = ret;
    return STAR;
}

"/" {
    struct syntax_node *ret = create_terminal_node(DIV);
    ret->value.string_value = Strdup(yytext);
    yylval.node_value = ret;
    return DIV;
}

"&&" { yylval.node_value = create_terminal_node(AND); return AND; }
"||" { yylval.node_value = create_terminal_node(OR); return OR; }
"." { yylval.node_value = create_terminal_node(DOT); return DOT; }
"!" { yylval.node_value = create_terminal_node(NOT); return NOT; }
"(" { yylval.node_value = create_terminal_node(LP); return LP; }
")" { yylval.node_value = create_terminal_node(RP); return RP; }
"[" { yylval.node_value = create_terminal_node(LB); return LB; }
"]" { yylval.node_value = create_terminal_node(RB); return RB; }
"{" { yylval.node_value = create_terminal_node(LC); return LC; }
"}" { yylval.node_value = create_terminal_node(RC); return RC; }
"int"|"float" {
    struct syntax_node *ret = create_terminal_node(TYPE);
    ret->value.string_value = Strdup(yytext);
    yylval.node_value = ret;
    return TYPE;
}
"struct" { yylval.node_value = create_terminal_node(STRUCT); return STRUCT; }
"return" { yylval.node_value = create_terminal_node(RETURN); return RETURN; }
"if" { yylval.node_value = create_terminal_node(IF); return IF; }
"else" { yylval.node_value = create_terminal_node(ELSE); return ELSE; }
"while" { yylval.node_value = create_terminal_node(WHILE); return WHILE; }
{identifier} {
    struct syntax_node *ret = create_terminal_node(ID);
    ret->value.string_value = Strdup(yytext);
    yylval.node_value = ret;
    return ID;
}
{white_spaces} { ; }

"/*"         { BEGIN(comment); } /* deal with multi-line comments, 
                                    see these two links: 
                                    http://dinosaur.compilertools.net/flex/flex_11.html
                                    http://web.eecs.utk.edu/~bvz/teaching/cs461Sp11/notes/flex */ 
<comment>[^*\n]*  {}      /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*  {} /* eat up '*'s not followed by '/'s */
<*>\n     { yycolumn = 1; }; /* reset yycolumn in any state */
<comment>"*"+"/"       { BEGIN(INITIAL); } /* resume to initial state */

"//".* { } /* deal with one line comment
              activate this rule only in INITIAL state
              so that one line comment in multi-line comments
              will not be caught by this rule */

. {
    lexical_error("Mysterious characters");
}

%%

int get_integer(int *val, int base, char *msg) {
    char *endptr = NULL;
    long int value = strtol(yytext, &endptr, base);
    if(*endptr != '\0') {
        lexical_error(msg);
        return -1;
    }
    // check for out of range integers
    if(value < INT_MIN || value > INT_MAX) {
        lexical_error("Integer constant is out of range");
        return -1;
    }
    else {
        *val = value;
        return 0;
    }
}

int get_float(float *val, char *msg) {
    char *endptr = NULL;
    float value = strtof(yytext, &endptr);
    if(*endptr != '\0') {
        lexical_error(msg);
        return -1;
    }
    // check for out of range integers
    if(value < -HUGE_VALF || value > HUGE_VALF) {
        lexical_error("Float constant is out of range");
        return -1;
    }
    else {
        *val = value;
        return 0;
    }
}

void lexical_error(char *msg) {
    extern int is_syntax_correct;
    /* when we encounter an lexical error
     * we usually returns nothing in the action part
     * so the parser usually go on as nothing happens
     * we use error to let main function know that
     * there is an error even if the syntax tree is successfully built
     */
    is_syntax_correct = 0;
    printf("Error type A at Line %d: %s \'%s\'.\n",
            yylineno, msg, yytext);
}

struct syntax_node *create_terminal_node(int node_type) {
    struct syntax_node *ret = Calloc(1, sizeof(struct syntax_node));
    ret->line_no = yylineno;
    ret->node_type = node_type;
    ret->is_empty = 0;
    ret->prev = ret->next = ret->child = NULL;
    return ret;
}
