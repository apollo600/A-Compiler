#include "IR_node.h"
#include "symtable.h"
#include <stack>

extern stack<Scope*> scopes;

static void make_table(int n, ofstream& output)
{
    for (int i = 1; i < n; i++) {
        output << "\t";
    }
}

void BinaryExpIR::print(ofstream& output)
{
    make_table(scopes.size(), output);
    output << return_reg << " = " << inst_name << " " << var_type
    << " " << operand_1 << ", " << operand_2 << endl;
}

void ReturnStmtIR::print(ofstream& output)
{
    make_table(scopes.size(), output);
    if (is_const)
        output << "ret " << var_type << " " << return_const << endl;
    else
        output << "ret " << var_type << " " << return_reg << endl;
}

void FuncDefIR::print(ofstream& output)
{
    make_table(scopes.size(), output);
    output << comment << endl;
    output << "define " << var_type << " @" << func_name << " (";
    for (int i = 0; i < param_list.size(); i++) {
        output << param_list[i];
        if (i != param_list.size() - 1) {
            output << ", ";
        }
    }
    output << ") ";
    output << "{" << endl;
    generate_IR(func_BB, output);
    output << "}" << endl;
}

void VarDefIR::print(ofstream& output)
{
    if (!is_global) {
        return;
    }

    make_table(scopes.size(), output);
    output << "@" << var_name << " = " << "global " << var_type << " "
    << init_value << " align " << align_bytes << endl;
}

void FuncCallIR::print(ofstream& output)
{
    make_table(scopes.size(), output);
    output << ret_reg << " = " << "call " << var_type 
    << " @" << func_name << "(";
    for (int i = 0; i < param_list.size(); i++) {
        output << param_list[i];
        if (i != param_list.size() - 1) {
            output << ", ";
        }
    }
    output << ")" << endl;
}

void AssignIR::print(ofstream& output)
{
    make_table(scopes.size(), output);
    output << "store " << var_type << " " << right_value << ", "
    << var_type << "* " << left_reg_name << endl;
}

void LValIR::print(ofstream& output)
{
    make_table(scopes.size(), output);
    if (is_global)
        output << left_reg_name << " = " << "load " << var_type << ", "
        << var_type << "* " << right_reg_name << ", " << "align " 
        << align_bytes << endl;
    else
        output << left_reg_name << " = " << "add " << var_type << " " 
        << right_const_value << ", " << "0" << endl;
}

void IfElseStmtIR::print(ofstream& output)
{
    make_table(scopes.size(), output);
    // br i1 <cond_reg>, label %if.true, label %if.false
    output << "br i1 " << cond_reg << ", " << "label %" << label_name + ".true"
    << ", " << "label %" << label_name + ".false" << "\n" << endl;

    // true BB
    make_table(scopes.size(), output);
    output << label_name + ".true:" << endl;
    if (true_BB == nullptr) {
        make_table(scopes.size() + 1, output);
        output << "; emtpy block" << endl;
    } else {
        generate_IR(true_BB, output);
    }
    output << endl;
    // false BB
    make_table(scopes.size(), output);
    output << label_name + ".false:" << endl;
    if (false_BB == nullptr) {
        make_table(scopes.size() + 1, output);
        output << "; emtpy block" << endl;
    } else {
        generate_IR(false_BB, output);
    }
    output << endl;
}