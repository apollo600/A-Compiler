#include "node.h"
#include "symtable.h"
#include <cstdarg>
using namespace std;

map<NodeType, string> node_type2name{
    {NodeType::ADD_EXP, "ADD_EXP"},
    {NodeType::BLOCK, "BLOCK"},
    {NodeType::error, "error"},
    {NodeType::EQ_EXP, "EQ_EXP"},
    {NodeType::FUNC_CALL, "FUNC_CALL"},
    {NodeType::FUNC_DECL, "FUNC_DECL"},
    {NodeType::FUNC_DEF, "FUNC_DEF"},
    {NodeType::FUNC_NAME, "FUNC_NAME"},
    {NodeType::FUNC_PARAMS, "FUNC_PARAMS"},
    {NodeType::FUNC_TYPE, "FUNC_TYPE"},
    {NodeType::IDENT, "IDENT"},
    {NodeType::JUST_CONCAT, "JUST_CONCAT"},
    {NodeType::JUST_PASS, "JUST_PASS"},
    {NodeType::JUST_CONTINUE, "JUST_CONTINUE"},
    {NodeType::LAND_EXP, "LAND_EXP"},
    {NodeType::LOR_EXP, "LOR_EXP"},
    {NodeType::LVAL, "LVAL"},
    {NodeType::MUL_EXP, "MUL_EXP"},
    {NodeType::NUMBER, "NUMBER"},
    {NodeType::REL_EXP, "REL_EXP"},
    {NodeType::STMT, "STMT"},
    {NodeType::STRING, "STRING"},
    {NodeType::UNARY_EXP, "UNARY_EXP"},
    {NodeType::VAR_DECL, "VAR_DECL"},
    {NodeType::VAR_DEF, "VAR_DEF"},
};

static int level = 0;

AST_Node::AST_Node()
{
    type = NodeType::error;
    value = -1;
}

AST_Node::AST_Node(AST_Node* child1, ...) : AST_Node()
{
    va_list args;
    va_start(args, child1);

    AST_Node* value = child1;

    while (value != nullptr) {
        add_child(value);
        value = va_arg(args, AST_Node*);
    }

    va_end(args);
}

AST_Node::~AST_Node()
{
    for (auto child : childs) {
        delete child;
    }
}

void AST_Node::add_child(AST_Node* child)
{
    childs.push_back(child);
    child->set_parent(this);
}

void AST_Node::set_parent(AST_Node* parent)
{
    this->parent = parent;
}

void AST_Node::set_name(const std::string& name)
{
    this->name = name;
    /* std::cout << ">>> " << name << std::endl; */
}

void AST_Node::set_value(unsigned int value)
{
    this->value = value;
}

void AST_Node::set_type(NodeType type)
{
    this->type = type;
}

inline static void make_table()
{
    for (int i = 0; i < level; i++) std::cout << "    ";
}

static void display_node(AST_Node*& node)
{
    make_table();

    std::cout << "<";
    if (node->name != "") {
        std::cout << node->name;
    }
    std::cout << ", ";
    if (node->value != -1) {
        std::cout << node->value;
    }
    std::cout << ", ";
    std::cout << node_type2name[node->type];
    std::cout << "> ";

    std::cout << std::endl;
}

void traverse_AST(AST_Node*& ast)
{
    /*
    AST 的遍历应该按照 childs 去层序遍历，如下格式输出：
    ROOT
    [<child1, child1.type, child1.name, child1.value> <child2, child2.type, child2.name, child2.value>]
    */
    display_node(ast);
    
    for (auto node : ast->childs) {
        level++;
        traverse_AST(node);
        level--;
    }
}
