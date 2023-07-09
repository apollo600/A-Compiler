#include "node.h"
#include <cassert>
#include <fstream>
using namespace std;

static AST_Node* Backtrack(AST_Node* ast, string node_name);

void generate_IR(AST_Node*& ast, ofstream& output)
{
    /*

    应当同样进行一个遍历，在每个节点会进行相应的操作
    从根结点开始捏。
    1. CompRoot，这里是一个vector，里面有多个CompUnit，生成的方式是拼接，建议添加一个注释在开头，添加一个空行在后方
    2. CompUnit，有两种类型，Decl和FuncDef，这里只是一个抽象层，不需要执行
    3. FuncDef, 这里就要定义函数的外围内容:
        define <return-type> @<func-name>([arg-list]) {
            [func-body]
        }
    4. VarDeclWithIdent，可以提供函数的return-type和func-name
    5. 接下来应该是函数的参数列表，如果有再说，目前没有
    6. 遇到了一个Block，生成一个大括号包住：
        {
            [BlockItemList]
        }
    7. BlockItem，这是一个中间层，Decl或Stmt，不需要执行
    8. Stmt，分为很多种类型，需要单独去处理
    9. 这里是return-Stmt，那就生成这样一个：
        ret void/<exp>
    10. 接下来会提供上述的exp，根据exp的类型，去详细生成即可

    */

    const NodeType& type = ast->type;
    if (type == NodeType::JUST_PASS) {
        assert(ast->childs.size() == 1);
        generate_IR(ast->childs[0], output);
    } else if (type == NodeType::JUST_CONCAT) {
        for (AST_Node*& node : ast->childs) {
            generate_IR(node, output);
        }
    } else if (type == NodeType::FUNC_DEF) {
        output << "; func def" << endl;
        output << "define ";
        for (AST_Node*& node : ast->childs) {
            generate_IR(node, output);
        }
    } else if (type == NodeType::BLOCK) {
        output << "{" << endl;
        generate_IR(ast->childs[0], output);
        output << "}" << endl;
    } else if (type == NodeType::STMT) {
        /* return-stmt */
        if (ast->childs[0]->name == "return") {
            output << "\tret ";
            // decide return type
            AST_Node* func_def_node = Backtrack(ast, "FuncDef");
            if (!func_def_node) {
                perror("No parent named `FuncDef`");
            }
            AST_Node* return_type_node = func_def_node->childs[0]->childs[0];
            
            if (return_type_node->name == "int")
                output << "i32 ";
            else if (return_type_node->name == "void")
                output << "void" << endl;
            else
                perror("unknown function type");
            generate_IR(ast->childs[1], output);
            output << endl;
        }
    } else if (type == NodeType::CONST) {
        if (ast->name == "Number") {
            output << ast->value;
            return;
        } else {
            output << ast->name;
            return;
        }
    } else if (type == NodeType::VAR_DECL_WITH_IDENT) {
        assert(ast->childs.size() == 2);
        
        if (ast->childs[0]->name == "int") {
            output << "i32 ";
        } else if (ast->childs[0]->name == "void") {
            output << "void ";
        } else {
            perror("unknown function type");
        }

        output << "@" << ast->childs[1]->name;
    } else if (type == NodeType::COMP_ROOT) {
        output << "target triple = \"x86_64-pc-windows-msys\"\n" << endl;
        generate_IR(ast->childs[0], output);
    } else {
        perror("Unimplemented node type");
    }
}

static AST_Node* Backtrack(AST_Node* ast, string node_name)
{
    while (ast != nullptr) {
        if (ast->name == node_name) {
            return ast;
        }
        ast = ast->parent;
    }
    return nullptr;
}
