#include "node.h"
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

extern FILE* yyin;
extern int yyparse(AST_Node*& ast);
extern int yylex_destroy(void);

// used for debug
// extern int yydebug;

int main(int argc, char *argv[]) {
    /* yydebug = 1; */

    if (argc < 2) {
        cout << ">>> Using stdin as input" << endl;
    } else {
        cout << ">>> Using " << argv[1] << " as input" << endl;
        yyin = fopen(argv[1], "r");
    }

    string IR_name;
    bool Output_AST = true;
    for (int i = 2; i < argc; ++i) {
        if (string(argv[i]) == "-o" && i + 1 < argc) {
            IR_name = argv[i + 1];
        }
        else if (string(argv[i]) == "--hide-AST") {
            Output_AST = false;
        }
    }

    int result;
    AST_Node* ast;
    result = yyparse(ast);

    if (!result) {
        cerr << ">>> Parser finished successfully" << endl;
        if (Output_AST)
            traverse_AST(ast);

        if (!IR_name.empty()) {
            ofstream llvm_ir;
            llvm_ir.open(IR_name, ios::out);
            generate_IR(ast, llvm_ir);
            llvm_ir.close();
        }
    }

    fclose(yyin);
    yylex_destroy();
}
