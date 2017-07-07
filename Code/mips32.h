#ifndef MIPS32_H
#define MIPS32_H
#include <stdio.h>
#include "linkage.h"
#include "ir.h"

LINKAGE void mips32_codegen(struct ir_code *code, FILE *f);
#endif
