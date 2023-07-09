#include "node.h"
#include "functions.h"
#include <iostream>

extern int yyparse();
extern AddExpNode* root_node;
extern FILE* yyin;

int main(int argc, char **argv) {
    if (argc >= 2) {
        yyin = fopen(argv[1], "r");
        int result = yyparse();
        if (!result) {
            traverseAddExpNode(root_node);
        } else {
            fprintf(stderr, "ERROR: parser report error\n");
        }
    } else {
        fprintf(stderr, "ERROR: need src filename\n");
    }
    return 0;
}