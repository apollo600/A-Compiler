all: main

include parser/makefrag
include scanner/makefrag

main: main.cpp scanner/scanner.lex.cpp parser/parser.tab.cpp
	g++ $^ -I . -o $@

# 单元测试规则
.PHONY:
test_scanner: build/test_scanner.out

.PHONY:
clean:
	rm scanner/scanner.lex.cpp parser/parser.tab.cpp parser/parser.tab.hpp
