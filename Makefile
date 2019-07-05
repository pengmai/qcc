CC=gcc
DEPS = abstract-syntax.h codegen.h

all: qcc

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

tag-query.tab.c tag-query.tab.h:
	bison -d tag-query.y

lex.yy.c: tag-query.tab.c tag-query.tab.h
	flex tag-query.l

qcc: tag-query.tab.o lex.yy.o abstract-syntax.o codegen.o main.o
	$(CC) tag-query.tab.o lex.yy.o abstract-syntax.o codegen.o main.o -o qcc

clean:
	rm -f qcc tag-query.tab.c tag-query.tab.h lex.yy.c ./*.o
