# 编译器设定和编译选项
CC = gcc
CFLAGS = -std=gnu99 -Wall

parser: syntax.tab.c main.c csapp.c csapp.h syntax.h
	$(CC) $(CFLAGS) syntax.tab.c main.c csapp.c -lfl -ly -o parser
lex.yy.c: lex.l
	flex lex.l
syntax.tab.c: syntax.y lex.yy.c
	bison -d -v syntax.y

.PHONY: clean test
test: parser
	@python test_parser.py
test-%:
	@python test_parser.py $@
clean:
	rm lex.yy.c syntax.tab.c syntax.tab.h parser
