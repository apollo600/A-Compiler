#include "node.h"
#include "symtable.h"
#include <cassert>
#include <fstream>
#include <stack>
#include <map>
using namespace std;

stack<Scope*> scopes;

static AST_Node* Backtrack(AST_Node* ast, string node_name);
static AST_Node* Track(AST_Node* ast, string node_name);
static inline Scope* get_cur_scope();
static void gen_CompRoot(AST_Node*& ast, ofstream& output);
static void gen_FuncDef(AST_Node*& ast, ofstream& output);
static void gen_Block(AST_Node*& ast, ofstream& output);
static void gen_Stmt(AST_Node*& ast, ofstream& output);
static void gen_Const(AST_Node*& ast, ofstream& output);
static void gen_Var_Decl_With_Ident(AST_Node*& ast, ofstream& output);
static void gen_Just_Pass(AST_Node*& ast, ofstream& output);
static void gen_Just_Concat(AST_Node*& ast, ofstream& output);
static void gen_Var_Decl(AST_Node*& ast, ofstream& output);
static void gen_Just_Continue(AST_Node*& ast, ofstream& output);
static void gen_Var_Def(AST_Node*& ast, ofstream& output, SymbolType type);

map<NodeType, void (*)(AST_Node*&, ofstream&)> IR_handler_Table = {
    {NodeType::COMP_ROOT, gen_CompRoot},
    {NodeType::FUNC_DEF, gen_FuncDef},
    {NodeType::BLOCK, gen_Block},
    {NodeType::STMT, gen_Stmt},
    {NodeType::CONST, gen_Const},
    {NodeType::VAR_DECL_WITH_IDENT, gen_Var_Decl_With_Ident},
    {NodeType::JUST_PASS, gen_Just_Pass},
    {NodeType::JUST_CONCAT, gen_Just_Concat},
    {NodeType::VAR_DECL, gen_Var_Decl},
};

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
    if (IR_handler_Table.count(type)) {
        IR_handler_Table[type](ast, output);
    }
    else {
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

static AST_Node* Track(AST_Node* ast, string node_name)
{
    if (ast->name == node_name) {
        return ast;
    }

    for (AST_Node* node : ast->childs) {
        Track(node, node_name);
    }

    return nullptr;
}

static inline Scope* get_cur_scope()
{
    Scope* cur_scope = scopes.top();
    return cur_scope;
}

static void gen_CompRoot(AST_Node*& ast, ofstream& output)
{
    output << "target triple = \"x86_64-pc-windows-msys\"\n" << endl;
    generate_IR(ast->childs[0], output);
}

static void gen_FuncDef(AST_Node*& ast, ofstream& output)
{
    output << "; func def" << endl;
    output << "define ";
    
    // 处理符号表
    if (get_cur_scope()->lookup(ast->childs[1]->name)) {
        // 查表是否被声明过
        printf("Function has been declared, check\n");
    }
    else {
        // add function symbol
        SymbolType type;
        AST_Node* name_child = ast->childs[0];
        if (name_child->childs.size() < 2) {
            cerr << "incorrect node" << endl;
        }
        if (name_child->childs[0]->name == "int") {
            type = SymbolType::INT_FUNC;
        } else if (name_child->childs[0]->name == "void") {
            type = SymbolType::VOID_FUNC;
        } else {
            cerr << "unknown function return type" << endl;
        }
        Symbol* t_symbol = new Symbol(name_child->childs[1]->name, 0, type);
        get_cur_scope()->insert(t_symbol);
        
        // push new scope
        scopes.push(new Scope(get_cur_scope()));
    }
    
    // 遍历子节点
    for (AST_Node*& node : ast->childs) {
        generate_IR(node, output);
    }
}

static void gen_Block(AST_Node*& ast, ofstream& output)
{
    output << "{" << endl;
    generate_IR(ast->childs[0], output);
    output << "}" << endl;
}

static void gen_Stmt(AST_Node*& ast, ofstream& output)
{
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
}

static void gen_Const(AST_Node*& ast, ofstream& output)
{
    if (ast->name == "Number") {
        output << ast->value;
        return;
    } else {
        output << ast->name;
        return;
    }
}

static void gen_Var_Decl_With_Ident(AST_Node*& ast, ofstream& output)
{
    assert(ast->childs.size() == 2);
        
    if (ast->childs[0]->name == "int") {
        output << "i32 ";
    } else if (ast->childs[0]->name == "void") {
        output << "void ";
    } else {
        perror("unknown function type");
    }

    output << "@" << ast->childs[1]->name;
}

static void gen_Just_Pass(AST_Node*& ast, ofstream& output)
{
    assert(ast->childs.size() == 1);
    generate_IR(ast->childs[0], output);
}

static void gen_Just_Concat(AST_Node*& ast, ofstream& output)
{
    for (AST_Node*& node : ast->childs) {
        generate_IR(node, output);
    }
}

static void gen_Var_Decl(AST_Node*& ast, ofstream& output)
{
    SymbolType type;
    string ident;
    AST_Node* var_type = ast->childs[0];
    AST_Node* var_def_list = ast->childs[1];
    assert(var_def_list->name == "VarDefList");

    // proces first ident
    // assign type and first ident
    // TODO 重构了VarWithIdent
    if (var_type->name == "int") {
        type = SymbolType::INT_VAR;
    } else {
        perror("unknown variable type");
    }

    // 遍历VarDefList
    for (AST_Node* var_def : var_def_list->childs) {
        gen_Var_Def(var_def, output, type);
    }
}

static void gen_Var_Def(AST_Node*& ast, ofstream& output, SymbolType type)
{
    AST_Node* ident = ast->childs[0];
    /* 检查是不是数组，即是否有VarDefList
    按照当前具体语法树的写法，直接使用第三个节点 */
    AST_Node* init_val = ast->childs[2];

    // insert node to symbol table
    /* 这个部分比较难，即获取这个表达式的值，参照另一个代码，
    首先，要继续向下遍历，不能跳过这个表达式；
    然后，这个表达式的值要传给这个初始值，这里初始值在运行时可以被查到，但是在编译时不一定
    所以需要通过寄存器+符号表传值，所有对值的改动都应该反应到符号表里 */
    Symbol* t_symbol = new Symbol(ident->name, 0, type, false);
    get_cur_scope()->insert(t_symbol);

    // 递归执行initval部分
    /* 首先需要把后面表达式的结果计算出来，最终保存到一个寄存器，
    然后把这个寄存器的值作为这个变量的初始值，传值可以通过全局变量 */
    generate_IR(init_val, output);

    // form IR
    // ident
    output << "@" << ident << " = ";
    // property
    if (scopes.size() == 1) {
        output << "global ";
    } else {
        output << "private ";
    }
    // type
    output << "i32 ";
    // value
    output << /* register / const */ << " ";
    // align
    output << "align 4" << endl;
}

static void gen_Just_Continue(AST_Node*& ast, ofstream& output)
{
    return;
}