#include <stdio.h>
#include "syntax.tab.h"
#include "syntax.h"

extern struct syntax_node *root;

extern int is_successful;

int main(int argc, char** argv) {
    // we only deal with one input c source file
    if(argc != 2) {
        fprintf(stderr, "usage: ./parser input_c_file\n");
        return 2;
    }

    FILE* f = NULL;
    if (!(f = fopen(argv[1], "r"))) {
        perror(argv[1]);
        return 1;
    }
    // yydebug = 1;
    yyrestart(f);
    int ret = yyparse();
    if(is_successful && !ret) {
        print_syntax_tree(root, 0);
        delete_syntax_tree(root);
    }
    return 0;
}
