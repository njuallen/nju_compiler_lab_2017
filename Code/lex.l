%{
#include <stdio.h>
#include "lex.h"
struct token tokens[] = {
    {0, "JUST_A_PLACE_HOLDER"},
    {INT, "INT"}, {FLOAT, "FLOAT"}, {ID, "ID"},
    {SEMI, "SEMI"}, {COMMA, "COMMA"}, {ASSIGNOP, "ASSIGNOP"},
    {RELOP, "RELOP"}, {PLUS, "PLUS"}, {MINUS, "MINUS"},
    {STAR, "STAR"}, {DIV, "DIV"}, {AND, "AND"},
    {OR, "OR"}, {DOT, "DOT"}, {NOT, "NOT"},
    {TYPE, "TYPE"}, {LP, "LP"}, {RP, "RP"},
    {LB, "LB"}, {RB, "RB"}, {LC, "LC"},
    {RC, "RC"}, {STRUCT, "STRUCT"}, {RETURN, "RETURN"},
    {IF, "IF"}, {ELSE, "ELSE"}, {WHILE, "WHILE"},
    {INVALID, "INVALID"}
};
%}

digit [0-9]
digits {digit}+

/* integer literal
 * read this link: http://en.cppreference.com/w/cpp/language/integer_literal
 */

/* decimal-literal is a non-zero decimal digit (1, 2, 3, 4, 5, 6, 7, 8, 9), 
 * followed by zero or more decimal digits (0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
 */
decimal ((0|([1-9]{digit}*)))

/* octal-literal is the digit zero (0) 
 * followed by zero or more octal digits (0, 1, 2, 3, 4, 5, 6, 7)
 */
oct (0[0-7]*)

/* hex-literal is the character sequence 0x or the character sequence 0X 
 * followed by one or more hexadecimal digits 
 * (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, A, b, B, c, C, d, D, e, E, f, F) 
 */
hex (0[xX][0-9a-fA-F]+)

/* floating point literal
 * link: http://en.cppreference.com/w/cpp/language/floating_literal
 */

significand_full {digits}\.{digits}
significand_no_integer \.{digits}
significand_no_fraction {digits}\.
exp_part ([eE][+-]?{digits})
white_spaces ([ \t\n]+)

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

letter_ [a-zA-Z_]
letter_s [a-zA-Z_]+

%%
({decimal}|{oct}|{hex}) { return INT; }
{significand_full}({exp_part})? { return FLOAT; }
({significand_no_integer}|{significand_no_fraction})({exp_part})? { return FLOAT; }
{digits}{exp_part} { return FLOAT; }
";" { return SEMI; }
"," { return COMMA; }
"=" { return ASSIGNOP; }
("<"|">"|">="|"<="|"!="|"==") { return RELOP; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return STAR; }
"/" { return DIV; }
"&&" { return AND; }
"||" { return OR; }
"." { return DOT; }
"!" { return NOT; }
"(" { return LP; }
")" { return RP; }
"[" { return LB; }
"]" { return RB; }
"{" { return LC; }
"}" { return RC; }
"int"|"float" { return TYPE; }
"struct" { return STRUCT; }
"return" { return RETURN; }
"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
{letter_s}({letter_s}|{digit})* { return ID; }
{white_spaces} { ; }
. { return INVALID; }
%%
