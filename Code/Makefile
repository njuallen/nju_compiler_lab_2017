# 编译器设定和编译选项
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -std=c99

LFILE = $(shell find ./ -name "*.l")
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
LFO = $(LFC:.c=.o)

parser: lexical
	$(CC) main.c -o parser  -lfl

lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

# 定义的一些伪目标
.PHONY: clean test
test:
	./parser test.cmm
clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f *~
