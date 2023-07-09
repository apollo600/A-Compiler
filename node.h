#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <memory>
// #include "llvm/IR/Value.h"

typedef unsigned int DWORD;

extern int lineno;
extern std::string filename;

// leave for llvm
// class CodeGenContext;

// declarations
class AddExpNode;
class MulExpNode;
class UnaryExpNode;
class LOrExpNode;
class LAndExpNode;
class EqExpNode;
class RelExpNode;

class Node
{
public:
    std::string filename;

    int lineno;

    Node()
        : filename(filename), lineno(lineno) {}

    virtual ~Node() {}

    // virtual void display() {}

    // virtual llvm::Value* codeGen(CodeGenContext &context) { return NULL; }
};

// empty realized
class ExpNode : public Node
{
};

// empty realized
class StmtNode : public Node
{
};

class IdentNode : public ExpNode
{
public:
    std::string name;

    IdentNode(const std::string &name)
        : name(name) {
            std::cout << "> IdentNode `" << name << "` " << this << std::endl;
        }

    IdentNode(const IdentNode &other)
        : name(other.name) {}

    // virtual llvm::Value* codeGen(CodeGenContext &context);
};

class IntNode : public ExpNode
{
public:
    int value;

    IntNode(int value)
        : value(value) {
            std::cout << "> IntNode `" << value << "` " << this << std::endl;
        }

    // virtual llvm::Value* codeGen(CodeGenContext &context);
};

class LValNode : public ExpNode
{
public:
    IdentNode *ident;

    std::vector<AddExpNode *> indexs;

    LValNode(IdentNode *ident)
        : ident(ident) {
            std::cout << "> LValNode " << this << "->" << ident << std::endl;
        }

    LValNode(const LValNode &other, AddExpNode *item)
        : ident(other.ident), indexs(other.indexs)
    {
        indexs.push_back(item);
    }

    // virtual llvm::Value* codeGen(CodeGenContext &context);
};

class PrimaryExpNode : public ExpNode
{
public:
    enum class Type
    {
        Expression,
        LValue,
        Number
    };

    // 存储当前节点的类型
    Type type;

    // 使用 std::variant 存储不同类型的节点
    union Value
    {
        AddExpNode *exp;
        LValNode *lval;
        IntNode *number;
    };

    Value value;

    // 构造函数
    PrimaryExpNode(AddExpNode *exp)
        : type(Type::Expression)
    {
        value.exp = exp;
    }

    PrimaryExpNode(LValNode *lval)
        : type(Type::LValue)
    {
        value.lval = lval;
        std::cout << "> PrimaryExpNode " << this << "->" << lval << std::endl;
    }

    PrimaryExpNode(IntNode *number)
        : type(Type::Number)
    {
        value.number = number;
        std::cout << "> PrimaryExpNode " << this << "->" << number << std::endl;
    }
};

class FuncRParamsNode : ExpNode
{
public:
    std::vector<AddExpNode *> params;

    FuncRParamsNode(AddExpNode *item)
    {
        params.push_back(item);
    }

    FuncRParamsNode(FuncRParamsNode &other, AddExpNode *item)
        : params(other.params)
    {
        params.push_back(item);
    }
};

class FuncCall : public ExpNode
{
public:
    IdentNode *ident;

    FuncRParamsNode *func_params;

    FuncCall(IdentNode *ident)
        : ident(ident), func_params(nullptr) {}

    FuncCall(IdentNode *ident, FuncRParamsNode *func_params)
        : ident(ident), func_params(func_params) {}
};

class UnaryOpExp : public ExpNode
{
public:
    enum class OpType
    {
        Plus,
        Minus,
        Not
    };

    OpType op_type;

    UnaryExpNode *unary_exp;

    UnaryOpExp(char op, UnaryExpNode *unary_exp)
        : unary_exp(unary_exp)
    {
        switch (op)
        {
        case '+':
            op_type = OpType::Plus;
            break;
        case '-':
            op_type = OpType::Minus;
            break;
        case '!':
            op_type = OpType::Not;
            break;
        default:
            printf("ERROR: wrong Unary op type\n");
            break;
        }
    }
};

class UnaryExpNode : public ExpNode
{
public:
    enum class Type
    {
        Primary,
        FuncCall,
        UnaryOp
    };

    Type type;

    union Value
    {
        PrimaryExpNode *primary_exp;
        FuncCall *func_call;
        UnaryOpExp *unary_op_exp;
    };

    Value value;

    UnaryExpNode(PrimaryExpNode *primary_exp)
        : type(Type::Primary)
    {
        value.primary_exp = primary_exp;
        std::cout << "> UnaryExpNode " << this << "->" << primary_exp << std::endl;
    }

    UnaryExpNode(FuncCall *func_call)
        : type(Type::FuncCall)
    {
        value.func_call = func_call;
    }

    UnaryExpNode(UnaryOpExp *unary_op_exp)
        : type(Type::UnaryOp)
    {
        value.unary_op_exp = unary_op_exp;
    }
};

class MulExp : public ExpNode
{
public:
    MulExpNode *mul_exp_node;

    enum class OpType
    {
        Mult,
        Div,
        Mod
    };

    OpType op_type;

    UnaryExpNode *unary_exp_node;

    MulExp(MulExpNode *mul_exp_node, char op, UnaryExpNode *unary_exp_node)
        : mul_exp_node(mul_exp_node), unary_exp_node(unary_exp_node)
    {
        switch (op)
        {
        case '*':
            op_type = OpType::Mult;
            break;
        case '/':
            op_type = OpType::Div;
            break;
        case '!':
            op_type = OpType::Mod;
            break;
        default:
            printf("ERROR: wrong MulExp op type\n");
            break;
        }
    }
};

class MulExpNode : public ExpNode
{
public:
    enum class Type
    {
        Unary,
        Mul
    };

    Type type;

    union Value
    {
        UnaryExpNode *unary_exp_node;
        MulExp *mul_exp;
    };

    Value value;

    MulExpNode(UnaryExpNode *unary_exp_node)
        : type(Type::Unary)
    {
        value.unary_exp_node = unary_exp_node;
        std::cout << "> MulExpNode " << this << "->" << unary_exp_node << std::endl;
    }

    MulExpNode(MulExp *mul_exp)
        : type(Type::Mul)
    {
        value.mul_exp = mul_exp;
    }
};

class AddExp : public ExpNode
{
public:
    AddExpNode *add_exp_node;

    enum class OpType
    {
        Plus,
        Minus
    };

    OpType op_type;

    MulExpNode *mul_exp_node;

    AddExp(AddExpNode *add_exp_node, char op, MulExpNode *mul_exp_node)
        : add_exp_node(add_exp_node), mul_exp_node(mul_exp_node)
    {
        switch (op)
        {
        case '+':
            op_type = OpType::Plus;
            break;
        case '-':
            op_type = OpType::Minus;
            break;
        default:
            printf("ERROR: wrong AddExp op type `%c`\n", op);
            break;
        }
    }
};

class AddExpNode : public ExpNode
{
public:
    enum class Type
    {
        Add,
        Mul
    };

    Type type;

    union Value
    {
        AddExp *add_exp;
        MulExpNode *mul_exp_node;
    };

    Value value;

    AddExpNode(AddExp *add_exp)
        : type(Type::Add)
    {
        value.add_exp = add_exp;
        // new (&value.add_exp) AddExp*(add_exp);
    }

    AddExpNode(MulExpNode *mul_exp_node)
        : type(Type::Mul)
    {
        value.mul_exp_node = mul_exp_node;
        std::cout << "> AddExpNode " << this << "->" << mul_exp_node << std::endl;
        // new (&value.mul_exp_node) MulExpNode*(mul_exp_node);
    }

    AddExpNode()
    {
        
    }
};

class ConstExpNode : public AddExpNode 
{
public:
    ConstExpNode(AddExpNode* add_exp_node)
    {
        type = add_exp_node->type;
        value = add_exp_node->value;
        filename = add_exp_node->filename;
        lineno = add_exp_node->lineno;
    }
};

class LOrExp : public ExpNode
{
public:
    LOrExpNode* l_or_exp_node;
    
    LAndExpNode* l_and_exp_node;

    LOrExp(LOrExpNode* l_or_exp_node, LAndExpNode* l_and_exp_node)
        : l_or_exp_node(l_or_exp_node), l_and_exp_node(l_and_exp_node) {}
};

class LOrExpNode : public ExpNode
{
public:
    enum class Type {
        LAnd,
        LOr
    };

    Type type;

    union Value {
        LAndExpNode* l_and_exp_node;
        LOrExp* l_or_exp;
    };

    Value value;

    LOrExpNode(LAndExpNode* l_and_exp_node)
        : type(Type::LAnd) 
    {
        value.l_and_exp_node = l_and_exp_node;
    }

    LOrExpNode(LOrExp* l_or_exp)
        : type(Type::LOr)
    {
        value.l_or_exp = l_or_exp;
    }
};

class LAndExp : public ExpNode
{
public:
    LAndExpNode* l_and_exp_node;

    EqExpNode* eq_exp_node;

    LAndExp(LAndExpNode* l_and_exp_node, EqExpNode* eq_exp_node)
        : l_and_exp_node(l_and_exp_node), eq_exp_node(eq_exp_node) {}
};

class LAndExpNode : public ExpNode
{
public:
    enum class Type {
        Eq,
        LAnd
    };

    Type type;

    union Value {
        EqExpNode* eq_exp_node;
        LAndExp* l_and_exp;
    };

    Value value;

    LAndExpNode(EqExpNode* eq_exp_node)
        : type(Type::Eq)
    {
        value.eq_exp_node = eq_exp_node;
    }

    LAndExpNode(LAndExp* l_and_exp)
        : type(Type::LAnd)
    {
        value.l_and_exp = l_and_exp;
    }
};

class EqExp : public ExpNode
{
public:
    EqExpNode* eq_exp_node;

    enum class OpType {
        EQ,
        NEQ
    };

    OpType op_type;

    RelExpNode* rel_exp_node;

    EqExp(EqExpNode* eq_exp_node, const std::string& op, RelExpNode* rel_exp_node)
        : eq_exp_node(eq_exp_node), rel_exp_node(rel_exp_node)
    {
        if (op == "==") {
            op_type = OpType::EQ;
        } else if (op == "!=") {
            op_type = OpType::NEQ;
        }
    }
};

class EqExpNode : public ExpNode
{
public:
    enum class Type {
        Rel,
        Eq
    };

    Type type;

    union Value {
        RelExpNode* rel_exp_node;
        EqExp* eq_exp;
    };

    Value value;

    EqExpNode(RelExpNode* rel_exp_node)
        : type(Type::Rel)
    {
        value.rel_exp_node = rel_exp_node;
    }

    EqExpNode(EqExp* eq_exp)
        : type(Type::Eq)
    {
        value.eq_exp = eq_exp;
    }
};

class RelExp : public ExpNode
{
public:
    RelExpNode* rel_exp_node;

    enum class OpType {
        LESS,
        GREATER,
        LE,
        GE
    };

    OpType op_type;

    AddExpNode* add_exp_node;

    RelExp(RelExpNode* rel_exp_node, const std::string& op, AddExpNode* add_exp_node)
        : rel_exp_node(rel_exp_node), add_exp_node(add_exp_node)
    {
        if (op == "<") {
            op_type = OpType::LESS;
        } else if (op == ">") {
            op_type = OpType::GREATER;
        } else if (op == "<=") {
            op_type = OpType::LE;
        } else if (op == ">=") {
            op_type = OpType::GE;
        }
    }
};

class RelExpNode : public ExpNode
{
public:
    enum class Type {
        Add,
        Rel
    };

    Type type;

    union Value {
        AddExpNode* add_exp_node;
        RelExp* rel_exp;
    };

    Value value;

    RelExpNode(AddExpNode* add_exp_node)
    {
        type = Type::Add;
        value.add_exp_node = add_exp_node;
    }

    RelExpNode(RelExp* rel_exp)
    {
        type = Type::Rel;
        value.rel_exp = rel_exp;
    }
};

#endif
