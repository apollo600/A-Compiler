#ifndef SYMTABLE_H
#define SYMTABLE_H

/*
切换Scope条件：FuncDecl, FuncDef, Block, if/else/else if/while
CompRoot创建一个根作用域，parser.ypp中全局维护一个当前Scope
因为C中局部覆盖全局，所以只需要从当前Scope向上遍历，
直到最顶层即可，如果找到则返回，如果没找到则返回nullptr，
构造时维护当前的Scope，从而可以方便地进行插入
*/

#include <vector>
#include <string>
using namespace std;

enum class SymbolType {
    INT_VAR, INT_FUNC, VOID_FUNC
};

enum class ValueType {
    CONST, REGISTER
};

class Symbol
{
public:
    /*
    | name | symbol_type |
            - func       |
            - var        | initialized | value_type | value | is_const | is_global |
    */
    string name;
    SymbolType symbol_type;

    bool initialized;
    ValueType value_type;
    int const_value;
    string reg_value; 
    bool is_const;
    bool is_global;

    // 用于变量的定义
    Symbol(const string& name, const int& value, const SymbolType& type):
        name(name), const_value(value), symbol_type(type), initialized(true) {}

    // 用于函数的声明/定义/变量声明
    Symbol(const string& name, const SymbolType& type):
        name(name), 
        symbol_type(type) 
    {
        if (type == SymbolType::INT_VAR) {
            initialized = false;
        }
    }
};

class Scope
{
public:
    vector<Symbol*> symbols;
    Scope* parent;
    Scope* son;
    
    Scope(Scope* parent);
    ~Scope();
    void insert(Symbol* new_symbol);
    Symbol* lookup(const string& symbol_name);
};

#endif