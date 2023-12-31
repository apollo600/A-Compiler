#include "IR_node.h"
#include "symtable.h"
#include <stack>
#include <cassert>

extern stack<Scope*> scopes;
extern bool is_reg;
extern string last_reg;

void make_table(int n, ofstream& output)
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
    // add default return
    make_table(scopes.size(), output);
    output << "ret i32 0" << endl;
    output << "}" << endl;
}

void VarDefIR::print(ofstream& output)
{
    
    if (is_global) {
        make_table(scopes.size(), output);
        output << "@" << var_name << " = " << "global " << var_type << " "
        << init_value << " align " << align_bytes << endl;
    }
    else {
        make_table(scopes.size(), output);
        output << "%" << var_name << " = " << "alloca " << var_type << endl;
        if (is_initialized) {
            make_table(scopes.size(), output);
            if (is_reg) {
                output << "store " << var_type << " " << init_reg << ", "
                << var_type << "* " << "%" << var_name << endl;
            } else {
                output << "store " << var_type << " " << init_value << ", "
                << var_type << "* " << "%" << var_name << endl;
            }
            
        }
    }
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
    if (is_param) {
        output << left_reg_name << " = " << "add i32 " << right_value << ", 0" << endl;
    } else {
        output << "store " << var_type << " " << right_value << ", "
        << var_type << "* " << left_reg_name << endl;
    }
    
}

void LValIR::print(ofstream& output)
{
    make_table(scopes.size(), output);
    output << left_reg_name << " = " << "load " << var_type << ", "
    << var_type << "* " << right_reg_name << endl;
}

void IfElseStmtIR::print(ofstream& output)
{   
    make_table(scopes.size(), output);
    // br i1 <cond_reg>, label %if.true, label %if.false
    output << "br i1 " << cond_reg << ", " << "label %" << label_name + ".true"
    << ", " << "label %" << label_name + ".false" << endl;

    // true BB
    make_table(scopes.size(), output);
    output << label_name + ".true:" << endl;
    if (true_BB != nullptr) {
        generate_IR(true_BB, output);
    } else {
        make_table(scopes.size() + 1, output);
        output << "; emtpy block" << endl;
    }
    // jump to end
    make_table(scopes.size() + 1, output);
    output << "br label %" << label_name + ".end" << endl;
    // false BB
    make_table(scopes.size(), output);
    output << label_name + ".false:" << endl;
    if (false_BB != nullptr) {
        generate_IR(false_BB, output);
    } else {
        make_table(scopes.size() + 1, output);
        output << "; emtpy block" << endl;
    }
    // jump to end
    make_table(scopes.size() + 1, output);
    output << "br label %" << label_name + ".end" << endl;
    // end BB
    make_table(scopes.size(), output);
    output << label_name + ".end:" << endl;
}

void WhileStmtIR::print(ofstream& output)
{
    // jmp to start
    make_table(scopes.size(), output);
    output << "br label " << "%" << label_name + ".start" << endl;
    
    // start label
    make_table(scopes.size(), output);
    output << label_name + ".start:" << endl;
    // test logic, jmp end
    scopes.push(new Scope(scopes.top()));
    
    generate_IR(cond, output);
    assert(is_reg);
    cond_reg = last_reg;
    make_table(scopes.size(), output);
    output << "br i1 " << cond_reg << ", " << "label "
    << "%" << label_name + ".body" << ", " << "label "
    << "%" << label_name + ".end" << endl;
    
    scopes.pop();
    // while block
    make_table(scopes.size(), output);
    output << label_name + ".body:" << endl;
    generate_IR(while_BB, output);
    // jmp start
    make_table(scopes.size(), output);
    output << "br label " << "%" << label_name + ".start" << endl;
    // end label
    make_table(scopes.size(), output);
    output << label_name + ".end:" << endl;
}

void BreakStmtIR::print(ofstream& output)
{
    make_table(scopes.size(), output);
    output << "br label " << "%" << label_name + ".end" << endl;
}

void ContinueStmtIR::print(ofstream& output)
{
    make_table(scopes.size(), output);
    output << "br label " << "%" << label_name + ".start" << endl;
}

void LOrExpIR::print(ofstream& output)
{
    // 求 BB_1
    generate_IR(BB_1, output);
    make_table(scopes.size(), output);
    output << "br i1 " << last_reg << ", label %" << label_name + ".true" 
    << ", label %" << label_name + ".false" << endl;
    // 如果否，继续 BB_2
    make_table(scopes.size(), output);
    output << label_name + ".false:" << endl;
    generate_IR(BB_2, output);
    make_table(scopes.size(), output);
    output << "br label %" << label_name + ".true" << endl;
    // 如果真，跳转到 end
    make_table(scopes.size(), output);
    output << label_name + ".true:" << endl;
    
    return_reg = last_reg;
}

void LAndExpIR::print(ofstream& output)
{
    // 求 BB_1
    generate_IR(BB_1, output);
    make_table(scopes.size(), output);
    output << "br i1 " << last_reg << ", label %" << label_name + ".true" 
    << ", label %" << label_name + ".false" << endl;
    // 如果否，继续 BB_2
    make_table(scopes.size(), output);
    output << label_name + ".true:" << endl;
    generate_IR(BB_2, output);
    make_table(scopes.size(), output);
    output << "br label %" << label_name + ".false" << endl;
    // 如果真，跳转到 end
    make_table(scopes.size(), output);
    output << label_name + ".false:" << endl;
    
    return_reg = last_reg;
}