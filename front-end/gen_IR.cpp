#include "node.h"
#include "symtable.h"
#include "IR_node.h"
#include <cassert>
#include <fstream>
#include <stack>
#include <map>
using namespace std;

stack<Scope*> scopes;

static int global_var_index = 0;
static string last_reg = "";
static int last_const = 0;

static AST_Node* Backtrack(AST_Node* ast, string node_name);
static AST_Node* Track(AST_Node* ast, string node_name);
static inline Scope* get_cur_scope();

static void gen_Comp_Root(AST_Node*& ast, ofstream& output);
static void gen_Func_Def(AST_Node*& ast, ofstream& output);
static void gen_Block(AST_Node*& ast, ofstream& output);
static void gen_Stmt(AST_Node*& ast, ofstream& output);
static void gen_Const(AST_Node*& ast, ofstream& output);
static void gen_Just_Pass(AST_Node*& ast, ofstream& output);
static void gen_Just_Concat(AST_Node*& ast, ofstream& output);
static void gen_LVal(AST_Node*& ast, ofstream& output);
static void gen_Var_Decl(AST_Node*& ast, ofstream& output);
static void gen_Just_Continue(AST_Node*& ast, ofstream& output);
static void gen_Func_Name(AST_Node*& ast, ofstream& output);
static void gen_Func_Type(AST_Node*& ast, ofstream& output);
static void gen_Func_Params(AST_Node*& ast, ofstream& output);
static void gen_Add_Exp(AST_Node*& ast, ofstream& output);

static void gen_Var_Def(AST_Node*& ast, ofstream& output, SymbolType type, bool is_const);
static void gen_Return_Stmt(AST_Node*& ast, ofstream& output);
static string gen_Func_Param(AST_Node*& ast);

map<NodeType, void (*)(AST_Node*&, ofstream&)> IR_handler_Table = {
    {NodeType::ADD_EXP, gen_Add_Exp},
    {NodeType::BLOCK, gen_Block},
    {NodeType::COMP_ROOT, gen_Comp_Root},
    {NodeType::CONST, gen_Const},
    {NodeType::FUNC_DEF, gen_Func_Def},
    {NodeType::FUNC_PARAMS, gen_Func_Params},
    {NodeType::FUNC_NAME, gen_Func_Name},
    {NodeType::FUNC_TYPE, gen_Func_Type},
    {NodeType::JUST_PASS, gen_Just_Pass},
    {NodeType::JUST_CONCAT, gen_Just_Concat},
    {NodeType::LVAL, gen_LVal},
    {NodeType::STMT, gen_Stmt},
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

static void gen_Comp_Root(AST_Node*& ast, ofstream& output)
{
    output << "target triple = \"x86_64-pc-windows-msys\"\n" << endl;
    cout << ">>> Start generating IR" << endl;
    scopes.push(new Scope(nullptr));
    for (AST_Node* comp_unit : ast->childs) {
        generate_IR(comp_unit, output);
    }
}

static void gen_Func_Def(AST_Node*& ast, ofstream& output)
{
    FuncDefIR ir;
    
    // 处理符号表
    if (get_cur_scope()->lookup(ast->childs[1]->name)) {
        // 查表是否被声明过
        printf("Function has been declared, check\n");
        return;
    }
  
    // add function symbol
    SymbolType type;
    if (ast->childs[0]->name == "int") {
        type = SymbolType::INT_FUNC;
    } else if (ast->childs[0]->name == "void") {
        type = SymbolType::VOID_FUNC;
    } else {
        perror("unknown function return type");
    }

    Symbol* t_symbol = new Symbol(ast->childs[1]->name, type);
    get_cur_scope()->insert(t_symbol);
    
    // switch to new scope
    scopes.push(new Scope(get_cur_scope()));

    ir.func_name = t_symbol->name;
    
    if (t_symbol->symbol_type == SymbolType::INT_FUNC)
        ir.var_type = "i32";
    else if (t_symbol->symbol_type == SymbolType::VOID_FUNC)
        ir.var_type = "void";
    else
        perror("unknown func ret type");
    
    // 生成 Block
    for (AST_Node*& node: ast->childs[2]->childs) {
        ir.param_list.push_back(
            gen_Func_Param(node)
        );
    }

    ir.print(output);

    // continue to generate block
    generate_IR(ast->childs[3], output);
}

static string gen_Func_Param(AST_Node*& ast)
{
    perror("unimplemented");
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
        gen_Return_Stmt(ast, output);   
    }
}

static void gen_Return_Stmt(AST_Node*& ast, ofstream& output)
{
    ReturnStmtIR ir;

    // decide return type
    AST_Node* func_def_node = Backtrack(ast, "FuncDef");
    if (!func_def_node) {
        perror("No parent named `FuncDef`");
    }
    string func_name = func_def_node->childs[1]->name;
    Symbol* func_symbol = get_cur_scope()->lookup(func_name);
    if (func_symbol->symbol_type == SymbolType::VOID_FUNC) {
        ir.var_type = "void";  
    } else {
        if (func_symbol->symbol_type == SymbolType::INT_FUNC)
            ir.var_type = "i32";
        else
            perror("unknown function type");
    }

    // get return reg/const       
    if (ast->childs[1]->name == "Number") { /* const */
        ir.is_const = true;
        generate_IR(ast->childs[1], output);
        ir.return_const = last_const;
    } else { /* LVal */
        ir.is_const = false;
        generate_IR(ast->childs[1], output);
        ir.return_reg = last_reg;
    }

    ir.print(output);
}

static void gen_Const(AST_Node*& ast, ofstream& output)
{
    if (ast->name == "Number") {
        // 回溯查看是否是InitVal
        AST_Node* init_val_node = Backtrack(ast, "InitVal");
        if (init_val_node) {
            last_const = ast->value;
        } else {
            output << ast->value;
        }
        return;
    } else {
        output << ast->name;
        return;
    }
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
    if (var_type->name == "int") {
        type = SymbolType::INT_VAR;
    } else {
        perror("unknown variable type");
    }

    // 遍历VarDefList
    for (AST_Node* var_def : var_def_list->childs) {
        gen_Var_Def(var_def, output, type, false);
    }
}

static void gen_Var_Def(AST_Node*& ast, ofstream& output, SymbolType type, bool is_const)
{
    VarDefIR ir;

    // var type
    if (type == SymbolType::INT_VAR) {
        ir.var_type = "i32";
        ir.align_bytes = 4;
    }
    else
        perror("unknown var type");

    // is const
    ir.is_const = is_const;

    // `@` or `%`
    if (scopes.size() == 1) {
        ir.is_global = true;
    } else {
        ir.is_global = false;
    }

    // var name
    AST_Node* ident = ast->childs[0];
    ir.var_name = ident->name;

    /* 检查是不是数组，即是否有VarDefList
    按照当前具体语法树的写法，直接使用第三个节点 */
    AST_Node* init_val = ast->childs[2];

    // 递归执行initval部分
    /* 首先需要把后面表达式的结果计算出来，最终保存到一个寄存器，
    然后把这个寄存器的值作为这个变量的初始值，传值可以通过全局变量 */
    generate_IR(init_val, output);
    if (ir.is_global) { /* global/const */
        ir.is_reg = false;
        ir.init_value = last_const;
    }
    else { /* reg */
        ir.is_reg = true;
        ir.init_reg = last_reg;
    }

    // insert node to symbol table
    /* 这个部分比较难，即获取这个表达式的值，参照另一个代码，
    首先，要继续向下遍历，不能跳过这个表达式；
    然后，这个表达式的值要传给这个初始值，这里初始值在运行时可以被查到，但是在编译时不一定
    所以需要通过寄存器+符号表传值，所有对值的改动都应该反应到符号表里 */
    Symbol* t_symbol;
    if (ir.is_reg) {
        t_symbol = new Symbol(ir.var_name, ir.init_reg, type);
    } else {
        t_symbol = new Symbol(ir.var_name, ir.init_value, type);
        if (ir.is_global)
            t_symbol->reg_value = "@" + ir.var_name;
    }
    t_symbol->is_global = ir.is_global;
    get_cur_scope()->insert(t_symbol);

    ir.print(output);

    /* // form IR
    t_symbol = get_cur_scope()->lookup(ident->name);
    // reg_name
    string reg_name = "";
    // `@` or `%`
    if (scopes.size() == 1) {
        reg_name += "@";
        t_symbol->is_global = true;
    } else {
        reg_name += "%";
        t_symbol->is_global = false;
    }
    // ident
    reg_name += t_symbol->name;
    t_symbol->reg_value = reg_name;

    output << reg_name << " = ";
    // property
    if (scopes.size() == 1) {
        output << "global ";
    } else {
        output << "private ";
    }
    // type
    if (t_symbol->symbol_type == SymbolType::INT_VAR) {
        output << "i32 ";
    } else {
        perror("unimplemented var type");
    }
    // value
    if (t_symbol->initialized) {
        if (t_symbol->value_type == ValueType::CONST) {
            output << t_symbol->const_value << " ";
        } else if (t_symbol->value_type == ValueType::REGISTER) {
            output << t_symbol->reg_value << " ";
        }
    } else {
        perror("uninitialized symbol value");
    }
    // align
    if (t_symbol->symbol_type == SymbolType::INT_VAR) {
        output << "align 4 ";
    } else {
        perror("unimplemented var type");
    }
    // from IR end
    output << endl; */
}

static void gen_Just_Continue(AST_Node*& ast, ofstream& output)
{
    return;
}

static void gen_Func_Name(AST_Node*& ast, ofstream& output)
{
    output << "@" << ast->name << " ";
}

static void gen_Func_Type(AST_Node*& ast, ofstream& output)
{
    if (ast->name == "int") {
        output << "i32 ";
    } else if (ast->name == "void") {
        output << "void ";
    } else {
        perror("unimplemented function type");
    }
}

static void gen_Func_Params(AST_Node*& ast, ofstream& output)
{
    if (ast->childs.size() == 0) {
        output << "() ";
    } else {
        perror("unimplemented");
        return;
    }
}

static void gen_LVal(AST_Node*& ast, ofstream& output)
{
    AST_Node* ident = ast->childs[0];
    Symbol* t_symbol = get_cur_scope()->lookup(ident->name);
    if (t_symbol) {
        if (t_symbol->is_global) {
            if (t_symbol->symbol_type == SymbolType::INT_VAR) {
                string reg_name = "%" + t_symbol->name;
                output << "\t" << reg_name << " = ";
                output << "load i32, i32* " << t_symbol->reg_value;
                output << ", align 4" << endl;
                last_reg = reg_name;
            }
        } else {
            last_reg = t_symbol->reg_value;
        }
    } else {
        perror("no symbol in table");
    }
}

static void gen_Add_Exp(AST_Node*& ast, ofstream& output)
{
    AddExpIR ir;

    if (ast->name == "+")
        ir.inst_name = "add";
    else if (ast->name == "-")
        ir.inst_name = "sub";
    else
        perror("wrong add op");
    
    global_var_index++;
    string reg_name = "%v" + to_string(global_var_index);
    ir.return_reg = reg_name;

    AST_Node* operand_1 = ast->childs[0];
    AST_Node* operand_2 = ast->childs[1];
    generate_IR(operand_1, output);
    ir.operand_1 = last_reg;
    generate_IR(operand_2, output);
    ir.operand_2 = last_reg;

    ir.var_type = "i32";

    ir.print(output);

    last_reg = ir.return_reg;
}