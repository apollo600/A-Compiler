CC := g++
CFLAGS := -I /usr/include/llvm-14 -I /usr/include/llvm-c-14
CFLAGS += -L /usr/lib/llvm-14/lib -lLLVM

parser.out : scanner.lex.cpp parser.tab.cpp main.cpp functions.cpp
	${CC} -o $@ ${CFLAGS} $^

scanner.lex.cpp : scanner.l parser.tab.cpp
	flex -o $@ $<

parser.tab.cpp : parser.ypp node.h
	bison -d $<