#include <stdio.h>
#include "lex.yy.c"

int main(int argc, char** argv) {
    // we only deal with one input c source file
    if(argc != 2) {
        fprintf(stderr, "usage: ./parser input_c_file\n");
        return 2;
    }

    extern FILE* yyin;
    if (!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        return 1;
    }
    int token_value;
    while((token_value = yylex()) != 0) {
        printf("%s:%s\n", tokens[token_value].name, yytext);
    }
    return 0;
}
