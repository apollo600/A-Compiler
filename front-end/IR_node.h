#ifndef IR_NODE_H
#define IR_NODE_H

#include <string>
#include <vector>
#include <fstream>
using namespace std;

class AddExpIR
{
public:
    string inst_name;
    string var_type;
    string operand_1, operand_2;
    string return_reg;

    void print(ofstream& output);
};

class ReturnStmtIR
{
public:
    bool is_const;
    int return_const;
    string return_reg;
    string var_type;

    void print(ofstream& output);
};

class FuncDefIR
{
public:
    string comment = "\n; func def";
    string var_type;
    string func_name;
    vector<string> param_list;
    
    void print(ofstream& output);
};

#endif