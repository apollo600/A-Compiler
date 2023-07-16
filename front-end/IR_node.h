#ifndef IR_NODE_H
#define IR_NODE_H

#include "node.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class IR
{
public:
    virtual void print(ofstream& output) = 0;
};

class BinaryExpIR: public IR
{
public:
    string inst_name;
    string var_type;
    string operand_1, operand_2;
    string return_reg;

    void print(ofstream& output);
};

class ReturnStmtIR: public IR
{
public:
    bool is_const;
    int return_const;
    string return_reg;
    string var_type;

    void print(ofstream& output);
};

class FuncDefIR: public IR
{
public:
    string comment = "\n; func def";
    string var_type;
    string func_name;
    vector<string> param_list;
    AST_Node* func_BB;

    void print(ofstream& output);
};

class VarDefIR: public IR
{
public:
    bool is_global;

    // global
    // @a = global i32 3 align 4 
    string var_name;
    bool is_const;
    string var_type;

    bool is_reg;
    int init_value;
    string init_reg;
    int align_bytes;

    // local
    // only record in symbol table

    void print(ofstream& output);
};

class FuncCallIR: public IR
{
public:
    string ret_reg;
    string var_type;
    string func_name;
    vector<string> param_list;

    void print(ofstream& output);
};

class AssignIR: public IR
{
public:
    string var_type;
    string left_reg_name;
    string right_value;
    bool is_param;

    void print(ofstream& output);
};

class LValIR: public IR
{
public:
    bool is_global;
    string var_type;

    // global
    string left_reg_name;
    string right_reg_name;
    int align_bytes;

    // local
    int right_const_value;

    void print(ofstream& output);
};

class IfElseStmtIR: public IR
{
public:
    string cond_reg;
    string label_name;
    AST_Node* true_BB;
    AST_Node* false_BB;

    void print(ofstream& output);
};

class WhileStmtIR: public IR
{
public:
    AST_Node* cond;
    string cond_reg;
    string label_name;
    AST_Node* while_BB;

    void print(ofstream& output);
};

class BreakStmtIR: public IR
{
public:
    string label_name;

    void print(ofstream& output);
};

class ContinueStmtIR: public IR
{
public:
    string label_name;

    void print(ofstream& output);
};

#endif