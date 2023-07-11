#include "symtable.h"

Scope::Scope(Scope* parent): parent(parent), son(nullptr)
{
    printf("Scope created\n");
    if (parent) {
        parent->son = this;
    }
}

Scope::~Scope()
{
    if (son != nullptr) {
        perror("wrong remove sequence");
    }
}

void Scope::insert(Symbol* new_symbol)
{
    this->symbols.push_back(new_symbol);
}

Symbol* Scope::lookup(const string& symbol_name)
{
    Scope* cur = this;
    while (cur != nullptr) {
        for (Symbol* x : cur->symbols) {
            if (x->name == symbol_name) {
                return x;
            }
        }
        cur = cur->parent;
    }
    return nullptr;
}