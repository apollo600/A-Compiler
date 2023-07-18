#include "node.h"
#include "symtable.h"
#include "IR_node.h"
#include <cassert>
#include <fstream>
#include <stack>
#include <map>
using namespace std;

extern void make_table(int n, ofstream& output);

stack<Scope*> scopes;

/* used for variant */
static int global_var_index = 0;
bool is_reg = false;
string last_reg = "";
string last_reg_type = "";
static int last_const = 0;

/* used for branch */
int global_if_index = 0;
int global_while_index = 0;

/* used for short-circuit */
int global_short_circuit_index = 0;

static AST_Node* Backtrack(AST_Node* ast, string node_name);
static AST_Node* Track(AST_Node* ast, string node_name);
static inline Scope* get_cur_scope();

/* gen_IR handler */
static void gen_Add_Exp(AST_Node*& ast, ofstream& output);
static void gen_Block(AST_Node*& ast, ofstream& output);
static void gen_Comp_Root(AST_Node*& ast, ofstream& output);
static void gen_Eq_Exp(AST_Node*& ast, ofstream& output);
static void gen_Func_Call(AST_Node*& ast, ofstream& output);
static void gen_Func_Def(AST_Node*& ast, ofstream& output);
static void gen_Ident(AST_Node*& ast, ofstream& output);
static void gen_Just_Concat(AST_Node*& ast, ofstream& output);
static void gen_Just_Continue(AST_Node*& ast, ofstream& output);
static void gen_Just_Pass(AST_Node*& ast, ofstream& output);
static void gen_LAnd_Exp(AST_Node*& ast, ofstream& output);
static void gen_LOr_Exp(AST_Node*& ast, ofstream& output);
static void gen_LVal(AST_Node*& ast, ofstream& output);
static void gen_Mul_Exp(AST_Node*& ast, ofstream& output);
static void gen_Number(AST_Node*& ast, ofstream& output);
static void gen_Rel_Exp(AST_Node*& ast, ofstream& output);
static void gen_Stmt(AST_Node*& ast, ofstream& output);
static void gen_String(AST_Node*& ast, ofstream& output);
static void gen_Unary_Exp(AST_Node*& ast, ofstream& output);
static void gen_Var_Decl(AST_Node*& ast, ofstream& output);

static void gen_Var_Def(AST_Node*& ast, ofstream& output, SymbolType type, bool is_const);
static void gen_Return_Stmt(AST_Node*& ast, ofstream& output);
static void gen_Assign_Stmt(AST_Node*& ast, ofstream& output);
static void gen_If_Else_Stmt(AST_Node*& ast, ofstream& output);
static void gen_While_Stmt(AST_Node*& ast, ofstream& output);
static void gen_Break_Stmt(AST_Node*& ast, ofstream& output);
static void gen_Continue_Stmt(AST_Node*& ast, ofstream& output);
static string gen_Func_Def_Param(AST_Node*& ast);
static string gen_Func_Call_Param(AST_Node*& ast, ofstream& output, string var_type);

map<NodeType, void (*)(AST_Node*&, ofstream&)> IR_handler_Table = {
    {NodeType::ADD_EXP, gen_Add_Exp},
    {NodeType::BLOCK, gen_Block},
    {NodeType::COMP_ROOT, gen_Comp_Root},
    {NodeType::EQ_EXP, gen_Eq_Exp},
    {NodeType::FUNC_DEF, gen_Func_Def},
    {NodeType::FUNC_CALL, gen_Func_Call},
    {NodeType::IDENT, gen_Ident},
    {NodeType::JUST_PASS, gen_Just_Pass},
    {NodeType::JUST_CONCAT, gen_Just_Concat},
    {NodeType::LOR_EXP, gen_LOr_Exp},
    {NodeType::LAND_EXP, gen_LAnd_Exp},
    {NodeType::LVAL, gen_LVal},
    {NodeType::MUL_EXP, gen_Mul_Exp},
    {NodeType::NUMBER, gen_Number},
    {NodeType::REL_EXP, gen_Rel_Exp},
    {NodeType::STMT, gen_Stmt},
    {NodeType::STRING, gen_String},
    {NodeType::UNARY_EXP, gen_Unary_Exp},
    {NodeType::VAR_DECL, gen_Var_Decl},
};

extern map<NodeType, string> node_type2name;

void generate_IR(AST_Node*& ast, ofstream& output)
{
    if (ast == nullptr) {
        return;
    }
    const NodeType& type = ast->type;
    if (IR_handler_Table.count(type)) {
        IR_handler_Table[type](ast, output);
    }
    else {
        string err_msg = "Unimplemented node type `" + node_type2name[type] + "` ";
        perror(err_msg.c_str());
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
            gen_Func_Def_Param(node)
        );
    }

    // func block
    ir.func_BB = ast->childs[3];

    ir.print(output);

    scopes.pop();
}

static string gen_Func_Def_Param(AST_Node*& ast)
{
    // symbol
    AST_Node* func_def_node = Backtrack(ast, "FuncDef");
    string func_name = func_def_node->childs[1]->name;
    Symbol* func_symbol = get_cur_scope()->lookup(func_name);
    // param
    SymbolType param_type;
    if (ast->childs[0]->name == "int")
        param_type = SymbolType::INT_VAR;
    else
        perror("unknown param type");
    string param_name = ast->childs[1]->name;
    // 修改符号表中函数的属性，加上参数列表
    if (param_type == SymbolType::INT_VAR)
        func_symbol->param_type_list.push_back("i32");
    else
        perror("unknown symbol type");
    // 在符号表中声明函数参数
    Symbol* param_symbol = new Symbol(param_name, param_type);
    param_symbol->is_param = true;
    param_symbol->reg_value = "%" + param_name;
    get_cur_scope()->insert(param_symbol);
    // ir中也需要添加函数的参数列表
    if (param_type == SymbolType::INT_VAR) {
        return "i32 %" + param_name;
    } else {
        perror("unknown");
    }

    return "";
}

static void gen_Func_Call(AST_Node*& ast, ofstream& output)
{
    FuncCallIR ir;

    global_var_index++;
    string reg_name = "%v" + to_string(global_var_index);
    ir.ret_reg = reg_name;

    ir.func_name = ast->childs[0]->name;
    
    // func symbol
    Symbol* func_symbol = get_cur_scope()->lookup(ir.func_name);
    if (func_symbol->symbol_type == SymbolType::INT_FUNC) {
        ir.var_type = "i32";
    } else {
        perror("unknown type");
    }

    // param list
    if (ast->childs.size() == 2) {
        AST_Node* param_list_node = ast->childs[1];
        for (int i = 0; i < param_list_node->childs.size(); i++) {
            string var_type = func_symbol->param_type_list[i];
            ir.param_list.push_back(
                gen_Func_Call_Param(param_list_node->childs[i], output, var_type)
            );
        }
    }

    ir.print(output);

    is_reg = true;
    last_reg = reg_name;
    last_reg_type = ir.var_type;
}

static string gen_Func_Call_Param(AST_Node*& ast, ofstream& output, string var_type)
{
    string var_value;
    // 是常数/符号
    // type
    // value
    generate_IR(ast, output);
    if (is_reg) {
        var_value = last_reg;
    } else {
        var_value = to_string(last_const);
    }
    return var_type + " " + var_value;
}

static void gen_Block(AST_Node*& ast, ofstream& output)
{
    // 需要创建新的作用域
    if (ast->parent->name != "FuncDef")
        scopes.push(new Scope(get_cur_scope()));
    generate_IR(ast->childs[0], output);
    // 退出当前作用域
    if (ast->parent->name != "FuncDef")
        scopes.pop();
}

static void gen_Stmt(AST_Node*& ast, ofstream& output)
{
    /* return-stmt */
    if (ast->childs.size() >= 1 && ast->childs[0]->name == "return") {
        gen_Return_Stmt(ast, output);   
    } 
    /* assign-stmt */
    else if (ast->name == "assign =") {
        gen_Assign_Stmt(ast, output);
    }
    /* if-else-stmt */
    else if (ast->childs.size() >= 1 && ast->childs[0]->name == "if") {
        gen_If_Else_Stmt(ast, output);
    }
    /* block */
    else if (ast->childs.size() >= 1 && ast->childs[0]->name == "Block") {
        generate_IR(ast->childs[0], output);
    }
    /* while */
    else if (ast->childs.size() >= 1 && ast->childs[0]->name == "while") {
        gen_While_Stmt(ast, output);
    }
    /* break */
    else if (ast->name == "break") {
        gen_Break_Stmt(ast, output);
    }
    /* continue */
    else if (ast->name == "continue") {
        gen_Continue_Stmt(ast, output);
    }
    else {
        perror("unimplemented statement");
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
    generate_IR(ast->childs[1], output);
    if (is_reg) {
        ir.is_const = false;
        ir.return_reg = last_reg;
    } else {
        ir.is_const = true;
        ir.return_const = last_const;
    }

    ir.print(output);
}

static void gen_Assign_Stmt(AST_Node*& ast, ofstream& output)
{
    // name
    AST_Node* lval_node = ast->childs[0];
    string lval_name = "";
    if (lval_node->childs[0]->type == NodeType::IDENT) {
        lval_name = lval_node->childs[0]->name;
    } else {
        perror("unimplemented");
    }
    // symbol
    Symbol* t_symbol = get_cur_scope()->lookup(lval_name);
    if (!t_symbol)
        perror("symbol not found");
    // 获得值
    generate_IR(ast->childs[1], output);
        
    AssignIR ir;
    // is_param
    ir.is_param = t_symbol->is_param;
    // lval
    ir.left_reg_name = t_symbol->reg_value;
    // right value
    if (is_reg) {
        ir.right_value = last_reg;
    } else {
        ir.right_value = to_string(last_const);
    }
    // type
    if (t_symbol->symbol_type == SymbolType::INT_VAR) {
        ir.var_type = "i32";
    } else {
        perror("unknown type");
    }
    ir.print(output);
    
    // process symbol table
    t_symbol->initialized = true;
}

static void gen_If_Else_Stmt(AST_Node*& ast, ofstream& output)
{
    // 一定要嵌套实现，if成立，进入对应的子树；if不成立，进入对应的子树/直接返回
    // else if可以看成是else{ if ... }
    // 这里需要设置标签点用来跳转, if-i.true, if-i.false, if-i.end
    global_if_index++;
    string label_name = "if-" + to_string(global_if_index);
    // 跳转的结果即Cond存储到最近一次的寄存器中
    assert(ast->childs.size() >= 2);
    generate_IR(ast->childs[1], output);
    assert(is_reg);
    string cond_reg = last_reg;
    /* if (ast->childs[1]->childs[0]->name == "LOrExp") {
        global_var_index++;
        string t_var_name = "%v" + to_string(global_var_index);
        make_table(scopes.size(), output);
        output << t_var_name << " = " << "icmp ne " << last_reg_type << " "
        << last_reg << ", " << "0" << endl;
        cond_reg = t_var_name;
    }  */
    // 然后生成跳转语句
    IfElseStmtIR ir;
    ir.cond_reg = cond_reg;
    ir.label_name = label_name;
    if (ast->childs.size() >= 3)
        ir.true_BB = ast->childs[2];
    else
        ir.true_BB = nullptr;
    if (ast->childs.size() >= 4)
        ir.false_BB = ast->childs[3];
    else
        ir.false_BB = nullptr;
    ir.print(output);
}

static void gen_While_Stmt(AST_Node*& ast, ofstream& output)
{
    WhileStmtIR ir;
    assert(ast->childs.size() == 3);
    // cond reg
    ir.cond = ast->childs[1];
    // label name
    global_while_index++;
    string label_name = "while-" + to_string(global_while_index);
    ir.label_name = label_name;
    // while block
    ir.while_BB = ast->childs[2];
    
    ir.print(output);
}

static void gen_Break_Stmt(AST_Node*& ast, ofstream& output)
{
    BreakStmtIR ir;
    string label_name = "while-" + to_string(global_while_index);
    ir.label_name = label_name;
    
    ir.print(output);
}

static void gen_Continue_Stmt(AST_Node*& ast, ofstream& output)
{
    ContinueStmtIR ir;
    string label_name = "while-" + to_string(global_while_index);
    ir.label_name = label_name;
    
    ir.print(output);
}

static void gen_Number(AST_Node*& ast, ofstream& output)
{
    is_reg = false;
    last_const = ast->value;
    return;
}

static void gen_Ident(AST_Node*& ast, ofstream& output)
{
    output << ast->name;
    return;
}

static void gen_String(AST_Node*& ast, ofstream& output)
{
    output << ast->name;
    return;
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
    bool is_const;
    AST_Node* var_type;
    AST_Node* var_def_list = ast->childs[1];
    if (ast->childs[0]->name == "const") {
        is_const = true;
        var_type = ast->childs[1];
        var_def_list = ast->childs[2];
    } else {
        is_const = false;
        var_type = ast->childs[0];
        var_def_list = ast->childs[1];
    }

    // proces first ident
    // assign type and first ident
    if (var_type->name == "int") {
        type = SymbolType::INT_VAR;
    } else {
        perror("unknown variable type");
    }

    // 遍历VarDefList
    for (AST_Node* var_def : var_def_list->childs) {
        gen_Var_Def(var_def, output, type, is_const);
    }
}

static void gen_Var_Def(AST_Node*& ast, ofstream& output, SymbolType type, bool is_const)
{
    /* symbol part */

    // insert node to symbol table
    /* 这个部分比较难，即获取这个表达式的值，参照另一个代码，
    首先，要继续向下遍历，不能跳过这个表达式；
    然后，这个表达式的值要传给这个初始值，这里初始值在运行时可以被查到，但是在编译时不一定
    所以需要通过寄存器+符号表传值，所有对值的改动都应该反应到符号表里 */
    Symbol* t_symbol;
    AST_Node* ident = ast->childs[0];
    t_symbol = new Symbol(ident->name, type);
    
    // is global
    if (scopes.size() == 1) {
        t_symbol->is_global = true;
        t_symbol->reg_value = "@" + t_symbol->name;
    } else {
        t_symbol->is_global = false;
        t_symbol->reg_value = "%" + t_symbol->name;
    }

    // is const
    t_symbol->is_const = is_const;

    get_cur_scope()->insert(t_symbol);

    // decl / def
    if (!t_symbol->is_global && ast->childs.size() == 1) { /* local decl */
        t_symbol->initialized = false;
    } else if (t_symbol->is_global && ast->childs.size() == 1) { /* global decl */
        t_symbol->initialized = true;
        t_symbol->const_value = 0;
        t_symbol->is_reg = false;
    } else { /* def */
        AST_Node* init_val = ast->childs[2];
        generate_IR(init_val, output);
        t_symbol->is_reg = true;
        t_symbol->initialized = true;
    }

    /* IR part */

    VarDefIR ir;

    // is initialized
    ir.is_initialized = t_symbol->initialized;

    // var type
    if (type == SymbolType::INT_VAR) {
        ir.var_type = "i32";
        ir.align_bytes = 4;
    }
    else {
        perror("unknown var type");
    }

    // is const
    ir.is_const = is_const;

    // is global
    ir.is_global = t_symbol->is_global;

    // var name
    ir.var_name = ident->name;

    // is reg
    ir.is_reg = is_reg;

    // value
    if (is_reg) {
        ir.init_reg = last_reg;
    } else {
        ir.init_value = last_const;
    }

    cout << ir.is_global << " " << ir.is_reg << endl;

    ir.print(output);
}

static void gen_Just_Continue(AST_Node*& ast, ofstream& output)
{
    return;
}

static void gen_LVal(AST_Node*& ast, ofstream& output)
{
    AST_Node* ident = ast->childs[0];
    Symbol* t_symbol = get_cur_scope()->lookup(ident->name);
    cout << "find " << ident->name << endl;
    if (!t_symbol) {
        perror("no symbol in table");
    }

    bool is_left_value = false;
    AST_Node* assign_node = Backtrack(ast, "assign =");
    if (assign_node) {
        is_left_value = true;
    }

    if (t_symbol->is_param) {
        if (!is_left_value) { /* directly use value of param */
            last_reg = t_symbol->reg_value;
            if (t_symbol->symbol_type == SymbolType::BOOL_VAR)
                last_reg_type = "i1";
            else if (t_symbol->symbol_type == SymbolType::INT_VAR)
                last_reg_type = "i32";
            else
                perror("unknown type");
            is_reg = true;
            return;
        } else { /* alloca a new register for param */
            VarDefIR ir;

            // left_reg_name
            global_var_index++;
            string reg_name = "v" + to_string(global_var_index);
            ir.var_name = reg_name;

            // type
            if (t_symbol->symbol_type == SymbolType::BOOL_VAR) {
                ir.align_bytes = 1;
                ir.var_type = "i1";
            }
            else if (t_symbol->symbol_type == SymbolType::INT_VAR) {
                ir.align_bytes = 4;
                ir.var_type = "i32";
            }
            else
                perror("unknown type");
            
            ir.is_initialized = true;
            ir.is_reg = true;
            ir.init_reg = t_symbol->reg_value;
            ir.is_const = t_symbol->is_const;
            ir.is_global = t_symbol->is_global;
            
            ir.print(output);

            // not a param now
            t_symbol->is_param = false;
            t_symbol->is_reg = true;
            t_symbol->reg_value = "%" + reg_name;
        }
    }

    LValIR ir;
    // type
    ir.is_global = true;
    // left_reg_name
    global_var_index++;
    string reg_name = "%v" + to_string(global_var_index);
    ir.left_reg_name = reg_name;
    // right_reg_name
    ir.right_reg_name = t_symbol->reg_value;
    // var type, align bytes
    if (t_symbol->symbol_type == SymbolType::INT_VAR) {
        ir.var_type = "i32";
        ir.align_bytes = 4;
    } else if (t_symbol->symbol_type == SymbolType::BOOL_VAR) {
        ir.var_type = "i1";
        ir.align_bytes = 1;
    } else {
        perror("unknown type");
    }

    ir.print(output);

    last_reg = reg_name;
    last_reg_type = ir.var_type;
    is_reg = true;
}

static void gen_Add_Exp(AST_Node*& ast, ofstream& output)
{
    BinaryExpIR ir;

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
    if (is_reg)
        ir.operand_1 = last_reg;
    else
        ir.operand_1 = to_string(last_const);
    generate_IR(operand_2, output);
    if (is_reg)
        ir.operand_2 = last_reg;
    else
        ir.operand_2 = to_string(last_const);

    ir.var_type = last_reg_type;

    ir.print(output);

    last_reg = ir.return_reg;
    is_reg = true;
}

static void gen_Unary_Exp(AST_Node*& ast, ofstream& output)
{
    string op = ast->name;
    if (op == "-") {
        BinaryExpIR ir;
        // inst
        ir.inst_name = "sub";
        // return reg
        global_var_index++;
        string reg_name = "%v" + to_string(global_var_index);
        ir.return_reg = reg_name;
        // operand 1
        ir.operand_1 = to_string(0);
        // operand 2
        assert(ast->childs.size() == 1);
        generate_IR(ast->childs[0], output);
        if (is_reg) {
            ir.operand_2 = last_reg;
        } else {
            ir.operand_2 = to_string(last_const);
        }
        // reg type
        if (last_reg_type != "")
            ir.var_type = last_reg_type;
        else
            ir.var_type = "i32";

        ir.print(output);

        last_reg = ir.return_reg;
        is_reg = true;
    } else if (op == "!") {
        BinaryExpIR ir;
        /* icmp eq i32 %a, 0 */
        // inst
        ir.inst_name = "icmp eq";
        // return reg
        global_var_index++;
        string reg_name = "%v" + to_string(global_var_index);
        ir.return_reg = reg_name;
        // operand 1
        assert(ast->childs.size() == 1);
        generate_IR(ast->childs[0], output);
        if (is_reg) {
            ir.operand_1 = last_reg;
        } else {
            ir.operand_1 = to_string(last_const);
        }
        // operand 2
        ir.operand_2 = to_string(0);
        ir.var_type = last_reg_type;

        ir.print(output);

        last_reg = ir.return_reg;
        last_reg_type = "i1";
        is_reg = true;

        /* xor i1 %v, true*/
        // inst
        ir.inst_name = "xor";
        // return reg
        global_var_index++;
        reg_name = "%v" + to_string(global_var_index);
        ir.return_reg = reg_name;

        // operand 1
        ir.operand_1 = last_reg;
        // operand 2
        ir.operand_2 = "true";
        ir.var_type = last_reg_type;

        ir.print(output);

        last_reg = ir.return_reg;
        last_reg_type = "i1";
        is_reg = true;

        /* zext */
        // return reg
        global_var_index++;
        reg_name = "%v" + to_string(global_var_index);
        // zext
        make_table(scopes.size(), output);
        output << reg_name << " = " << "zext " << last_reg_type << " "
        << last_reg << " to i32" << endl;

        last_reg = reg_name;
        last_reg_type = "i32";
        is_reg = true;
    } else if (op == "+") {
        BinaryExpIR ir;
        // inst
        ir.inst_name = "add";
        // return reg
        global_var_index++;
        string reg_name = "%v" + to_string(global_var_index);
        ir.return_reg = reg_name;
        // operand 1
        assert(ast->childs.size() == 1);
        generate_IR(ast->childs[0], output);
        if (is_reg) {
            ir.operand_1 = last_reg;
        } else {
            ir.operand_1 = to_string(last_const);
        }
        // operand 2
        ir.operand_2 = to_string(0);
        
        ir.var_type = last_reg_type;

        ir.print(output);

        last_reg = ir.return_reg;
        is_reg = true;
    } else {
        perror("unknown op");
    }
}

static void gen_Mul_Exp(AST_Node*& ast, ofstream& output)
{
    BinaryExpIR ir;
    // inst
    if (ast->name == "*") {
        ir.inst_name = "mul";
    } else if (ast->name == "/") {
        ir.inst_name = "sdiv";
    } else if (ast->name == "%") {
        ir.inst_name = "srem";
    } else {
        perror("unimplemented op type");
    }
    // return reg
    global_var_index++;
    string reg_name = "%v" + to_string(global_var_index);
    ir.return_reg = reg_name;
    // operand 1, 2
    AST_Node* operand_1 = ast->childs[0];
    AST_Node* operand_2 = ast->childs[1];
    generate_IR(operand_1, output);
    if (is_reg)
        ir.operand_1 = last_reg;
    else
        ir.operand_1 = to_string(last_const);
    generate_IR(operand_2, output);
    if (is_reg)
        ir.operand_2 = last_reg;
    else
        ir.operand_2 = to_string(last_const);
    // var type
    ir.var_type = last_reg_type;

    ir.print(output);
    last_reg = ir.return_reg;
    is_reg = true;
}

static void gen_Rel_Exp(AST_Node*& ast, ofstream& output)
{
    BinaryExpIR ir;
    // inst
    if (ast->name == ">") {
        ir.inst_name = "icmp sgt";
    } else if (ast->name == "<") {
        ir.inst_name = "icmp slt";
    } else if (ast->name == ">=") {
        ir.inst_name = "icmp sge";
    } else if (ast->name == "<=") {
        ir.inst_name = "icmp sle";
    } else {
        perror("unimplemented op type");
    }
    // return reg
    global_var_index++;
    string reg_name = "%v" + to_string(global_var_index);
    ir.return_reg = reg_name;
    // operand 1, 2
    AST_Node* operand_1 = ast->childs[0];
    AST_Node* operand_2 = ast->childs[1];
    generate_IR(operand_1, output);
    if (is_reg)
        ir.operand_1 = last_reg;
    else
        ir.operand_1 = to_string(last_const);
    generate_IR(operand_2, output);
    if (is_reg)
        ir.operand_2 = last_reg;
    else
        ir.operand_2 = to_string(last_const);
    // var type
    ir.var_type = last_reg_type;

    ir.print(output);
    last_reg = ir.return_reg;
    is_reg = true;
}

static void gen_Eq_Exp(AST_Node*& ast, ofstream& output)
{
    BinaryExpIR ir;
    // inst
    if (ast->name == "==") {
        ir.inst_name = "icmp eq";
    } else if (ast->name == "!=") {
        ir.inst_name = "icmp ne";
    } else {
        perror("unimplemented op type");
    }
    // return reg
    global_var_index++;
    string reg_name = "%v" + to_string(global_var_index);
    ir.return_reg = reg_name;
    // operand 1, 2
    AST_Node* operand_1 = ast->childs[0];
    AST_Node* operand_2 = ast->childs[1];
    generate_IR(operand_1, output);
    if (is_reg)
        ir.operand_1 = last_reg;
    else
        ir.operand_1 = to_string(last_const);
    generate_IR(operand_2, output);
    if (is_reg)
        ir.operand_2 = last_reg;
    else
        ir.operand_2 = to_string(last_const);
    // var type
    ir.var_type = last_reg_type;

    ir.print(output);
    last_reg = ir.return_reg;
    is_reg = true;
}

static void gen_LOr_Exp(AST_Node*& ast, ofstream& output)
{
    LOrExpIR ir;

    // two BB
    ir.BB_1 = ast->childs[0];
    ir.BB_2 = ast->childs[1];

    // label name
    global_short_circuit_index++;
    string label_name = "short-circuit-" + to_string(global_short_circuit_index);
    ir.label_name = label_name;

    // inst
    ir.inst_name = "or";

    // var type
    ir.var_type = "i1";

    // return reg
    global_var_index++;
    string reg_name = "%v" + to_string(global_var_index);
    ir.return_reg = reg_name;

    ir.print(output);

    last_reg = ir.return_reg;
    is_reg = true;
}

static void gen_LAnd_Exp(AST_Node*& ast, ofstream& output)
{
    LAndExpIR ir;

    // two BB
    ir.BB_1 = ast->childs[0];
    ir.BB_2 = ast->childs[1];

    // label name
    global_short_circuit_index++;
    string label_name = "short-circuit-" + to_string(global_short_circuit_index);
    ir.label_name = label_name;

    // inst
    ir.inst_name = "and";

    // var type
    ir.var_type = "i1";

    // return reg
    global_var_index++;
    string reg_name = "%v" + to_string(global_var_index);
    ir.return_reg = reg_name;

    ir.print(output);

    last_reg = ir.return_reg;
    is_reg = true;
}