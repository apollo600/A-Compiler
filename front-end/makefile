CC := g++
CFLAGS := -std=c++11
OBJ = ../functional-test/parser.out

.PHONY: all clean run

all: ${OBJ}

run: all
	./parser.out test_parser.sy

clean:
	rm parser.out parser.tab.hpp parser.tab.cpp scanner.lex.cpp main.ll main.out 2> /dev/null

${OBJ}: scanner.lex.cpp parser.tab.cpp node.cpp main.cpp gen_IR.cpp symtable.cpp
	${CC} -o $@ ${CFLAGS} $^

parser.tab.cpp: parser.ypp node.h
	@# bison $< -d -v --debug
	bison $< -d

scanner.lex.cpp: scanner.l parser.tab.cpp
	flex -o $@ $<