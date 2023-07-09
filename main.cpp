#include "parser/parser.h"

extern FILE *yyin;

int main(int argc, char **argv) {
    FILE *f;

    // 若指定有参数，则作为词法分析的输入文件
    if ((yyin = fopen(argv[1], "r")) == nullptr) {
        printf("Can't open file %s\n", argv[1]);
        return -1;
    }

    int result;
    result = yyparse();
    return 0;
}