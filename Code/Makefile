# 编译器设定和编译选项
CC = gcc
CFLAGS = -std=gnu99 -Wall

parser: syntax.tab.c main.c csapp.c csapp.h syntax.h
	$(CC) $(CFLAGS) syntax.tab.c main.c csapp.c -lfl -ly -o parser
lex.yy.c: lex.l
	flex lex.l
syntax.tab.c: syntax.y lex.yy.c
	bison -t -d -v syntax.y

.PHONY: clean test
test: parser
	@python2.7 test_parser.py
test-%:
	@python2.7 test_parser.py $@
clean:
	@rm -rf lex.yy.c syntax.tab.c syntax.tab.h parser 2>/dev/null >/dev/null
submit:
	cd ../../
	tar czf 141242022_lab1.tar.gz nju_compiler_lab_2017
