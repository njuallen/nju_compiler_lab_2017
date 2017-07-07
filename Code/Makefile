# 编译器设定和编译选项
CC = gcc
CFLAGS = -std=gnu99 -Wall -g -O0
COMMON = csapp.c csapp.h
ADT = adt.c adt.h

all: parser adt

parser: syntax.tab.c semantic.c semantic.h ir.c ir.h main.c syntax.h mips32.h mips32.o $(COMMON) $(adt)
	$(CC) $(CFLAGS) syntax.tab.c semantic.c ir.c main.c adt.c csapp.c mips32.o -lfl -ly -lstdc++ -o parser
mips32.o:mips32.cpp mips32.h
	g++ -DLINKAGE_CPP -c -std=c++0x -g -Wall -g -O0 mips32.cpp -o mips32.o
lex.yy.c: lex.l
	flex lex.l
syntax.tab.c: syntax.y lex.yy.c
	bison -t -d -v syntax.y

adt: test_adt.cpp $(COMMON) $(adt)
	g++ -Wall -std=c++0x -g test_adt.cpp adt.c csapp.c -o adt

.PHONY: clean test
test: parser
	@python2.7 test_parser.py ../Test/semantics/
test-%:
	@python2.7 test_parser.py ../Test/semantics/ $@
clean:
	@rm -rf lex.yy.c syntax.tab.c syntax.tab.h parser adt mips32.o 2>/dev/null >/dev/null
	@rm -rf ../Test/semantics/*.out ../Test/semantics/*.correct
	@chmod -w ../Test/semantics/*.cmm ../Test/semantics/*.answer
	@chmod -w ../Test/syntax/*.cmm ../Test/syntax/*.answer
submit:
	cd ../../ && tar czf 141242022_lab.tar.gz nju_compiler_lab_2017 --exclude='nju_compiler_lab_2017/.git' --exclude='nju_compiler_lab_2017/Handouts' 
