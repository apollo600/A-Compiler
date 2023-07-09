#include <string>
#include <vector>
using namespace std;

enum Node_Type {
    NODE_CONST,
    NODE_IDENT,
    NODE_EXP,
    NODE_CALL_EXP,
    NODE_TYPE,
    NODE_STMT,
    NODE_OP,
};

enum Op_Type {
    OP_NONE,
    OP_INDEX,
    OP_MULT,
    OP_MOD,
    OP_PLUS,
    OP_MINUS,
    OP_NOT,
    OP_OR,
    OP_AND,
    OP_EQ,
    OP_NE,
    OP_LESS,
    OP_GREATER,
    OP_LE,
    OP_GE,
    OP_ASSIGN,
};

enum Stmt_Type {
    STMT_BLOCK,
    STMT_DECL,
    STMT_SKIP,
    
};

class Node {
public:
    string file_name;
    int lineno;
    Node_Type node_type;
    Op_Type op_type;
    Stmt_Type stmt_type;

    int number_value;
    string var_name;

    vector<Node *> childs;

    Node(string &file_name, int &lineno, Node_Type node_type, Op_Type Op_Type = OP_NONE): 
        file_name(file_name), lineno(lineno), node_type(node_type), op_type(op_type)
    {}

    void addChild(Node *new_node) {
        childs.push_back(new_node);
    }
};
