#include "IR_node.h"

void AddExpIR::print(ofstream& output)
{
    output << "\t" << return_reg << " = " << inst_name << " " << var_type
    << " " << operand_1 << ", " << operand_2 << endl;
}

void ReturnStmtIR::print(ofstream& output)
{
    if (is_const)
        output << "\t" << "ret " << var_type << " " << return_const << endl;
    else
        output << "\t" << "ret " << var_type << " " << return_reg << endl;
}

void FuncDefIR::print(ofstream& output)
{
    output << comment << endl;
    output << "define " << var_type << " @" << func_name << " (";
    for (const string& s: param_list)
        output << s << ", ";
    output << ") ";
}

void VarDefIR::print(ofstream& output)
{
    if (!is_global) {
        return;
    }

    output << "@" << var_name << " = " << "global " << var_type << " "
    << init_value << " align " << align_bytes << endl;
}