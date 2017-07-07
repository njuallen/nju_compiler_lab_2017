#include <stdarg.h>
#include "csapp.h"
#include "adt.h"
#include "syntax.h"
#include "semantic.h"
#include "ir.h"
#include "mips32.h"
#include <iostream>

struct basic_block *basic_blocks = NULL;

extern "C" void mips32_codegen(struct ir_code *code, FILE *f) {
    std::cout << "Hello world" << std::endl;
}
