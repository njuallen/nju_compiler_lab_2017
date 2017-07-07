#ifndef MIPS32_H
#define MIPS32_H
#include <stdio.h>

#ifdef LINKAGE_CPP
#define LINKAGE extern "C"
#else
#define LINKAGE 
#endif

LINKAGE void mips32_codegen(struct ir_code *code, FILE *f);
#endif
