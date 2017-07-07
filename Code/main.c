#include <stdio.h>
#include "syntax.h"
#include "semantic.h"
#include "ir.h"
#include "mips32.h"

extern struct syntax_node *root;

extern int is_syntax_correct;

int main(int argc, char** argv) {
    if(argc != 3) {
        fprintf(stderr, "usage: ./parser input_c_file output_MIPS32_asm_file\n");
        return 2;
    }

    FILE* f = NULL;
    if (!(f = fopen(argv[1], "r"))) {
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    int ret = yyparse();
    struct ir_code *code = NULL;
    if(is_syntax_correct && !ret) {
        if(check_semantics(root) && (code = generate_ir(root)) != NULL) {
            if (!(f = fopen(argv[2], "w"))) {
                perror(argv[1]);
                return 1;
            }
            mips32_codegen(code, f);
        }
        delete_syntax_tree(root);
    }
    return 0;
}
