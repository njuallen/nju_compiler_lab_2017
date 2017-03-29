%{
#include <stdio.h>
#include "lexical.h"
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
/*
INT  // A sequence of digits without spaces1
FLOAT  // A real number consisting of digits and one decimal point. The decimal point must be surrounded by at least one digit2
ID  // A character string consisting of 52 upper- or lower-case alphabetic, 10
numeric and one underscore characters. Besides, an identifier must not start
with a digit3
SEMI  ;
COMMA  ,
ASSIGNOP  =
RELOP  > | < | >= | <= | == | !=
PLUS  +
MINUS  -
STAR  *
DIV  /
AND  &&
OR  ||
DOT  .
NOT  !
TYPE  int | float
LP  (
RP  )
LB  [
RB  ]
LC  {
RC  }
STRUCT  struct
RETURN  return
IF  if
ELSE  else
WHILE  while
*/
%}

%%
; { return SEMI; }
, { return COMMA; }
= { return ASSIGNOP; }
%%
