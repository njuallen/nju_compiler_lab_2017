#include <stdio.h>
#include "syntax.tab.h"
#include "syntax.h"

extern struct syntax_node *root;

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
    yyrestart(f);
    yyparse();

    print_syntax_tree(root, 0);
    delete_syntax_tree(root);
    return 0;
}
