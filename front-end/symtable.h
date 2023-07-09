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
    INT_VAR, INT_FUNC, VOID_FUNC, 
};

class Symbol
{
public:
    string name;
    int value;
    SymbolType type;

    Symbol(const string& name, const int& value, const SymbolType& type):
        name(name), value(value), type(type) {}
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