#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

extern int lineno;
extern std::string filename;

enum class NodeType {
    error, JUST_CONCAT, JUST_PASS, FUNC_DEF, FUNC_DECL, BLOCK, 
    STMT, ADD_EXP, CONST, VAR_DECL_WITH_IDENT, COMP_ROOT,
    VAR_DECL, JUST_CONTINUE, VAR_DEF
};

class AST_Node {
public:
    // used to build AST
    NodeType type;
    std::vector<AST_Node*> childs;
    AST_Node* parent;

    // attribute
    /*
    any node terminal attribute can be saved in string/int.
    */
    std::string name;
    unsigned int value;

    // default constructor
    AST_Node();

    // constructor with childs, it should end with nullptr
    AST_Node(AST_Node* child1, ...);

    // default deconstructor
    ~AST_Node();

    // add child
    void add_child(AST_Node* child);

    // set parent
    void set_parent(AST_Node* parent);

    // set name
    void set_name(const std::string &name);

    // set value
    void set_value(unsigned int value);

    // set type label
    void set_type(NodeType type);
};

void traverse_AST(AST_Node*& ast);

void generate_IR(AST_Node*& ast, std::ofstream& output);

#endif