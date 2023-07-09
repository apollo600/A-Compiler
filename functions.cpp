#include "functions.h"

static int level = 0;

static void makeTable() {
    for (int i = 0; i < level; i++) {
        printf("\t");
    }
}

void traverseAddExpNode(AddExpNode* root) {
    makeTable();
    printf("%s\n", "AddExpNode");

    switch (root->type)
    {
    case AddExpNode::Type::Add:
        level++;
        traverseAddExp(root->value.add_exp);
        level--;
        break;
    case AddExpNode::Type::Mul:
        level++;
        traverseMulExpNode(root->value.mul_exp_node);
        level--;
        break;
    default:
        fprintf(stderr, "ERROR: wrong AddExpNode op_type\n");
    }
}

void traverseAddExp(AddExp* root) {
    // AddExp 作为中间结点，不输出在 AST 中
    // level 也不进行增加

    traverseAddExpNode(root->add_exp_node);

    makeTable();
    switch (root->op_type)
    {
    case AddExp::OpType::Plus:
        printf("+\n");
        break;
    case AddExp::OpType::Minus:
        printf("-\n");
        break;
    }

    traverseMulExpNode(root->mul_exp_node);
}

void traverseMulExpNode(MulExpNode* root) {
    makeTable();
    printf("%s\n", "MulExpNode");

    switch (root->type)
    {
    case MulExpNode::Type::Mul:
        level++;
        traverseMulExp(root->value.mul_exp);
        level--;
        break;
    case MulExpNode::Type::Unary:
        level++;
        traverseUnaryExpNode(root->value.unary_exp_node);
        level--;
        break;
    }
}

void traverseMulExp(MulExp* root) {
    // MulExp 作为中间结点不输出
    // 且不修改 level

    traverseMulExpNode(root->mul_exp_node);

    makeTable();
    switch(root->op_type) {
        case MulExp::OpType::Mult:
            printf("*\n");
            break;
        case MulExp::OpType::Div:
            printf("/\n");
            break;
        case MulExp::OpType::Mod:
            printf("%%\n");
            break;
    }
}

void traverseUnaryExpNode(UnaryExpNode* root) {
    makeTable();
    printf("%s\n", "UnaryExpNode");

    switch (root->type) {
        case UnaryExpNode::Type::FuncCall:
            level++;
            traverseFuncCall(root->value.func_call);
            level--;
        case UnaryExpNode::Type::Primary:
            level++;
            traversePrimaryExpNode(root->value.primary_exp);
            level--;
        case UnaryExpNode::Type::UnaryOp:
            level++;
            traverseUnaryOpExp(root->value.unary_op_exp);
            level--;
    }
}

void traverseFuncCall(FuncCall* root) {
    // FuncCall 为中间层
    // 不输出，不修改 level

    traverseIdentNode(root->ident);
    traverseFuncRParamsNode(root->func_params);
}

void traversePrimaryExpNode(PrimaryExpNode* root) {
    makeTable();
    printf("%s\n", "PrimaryExpNode");

    switch (root->type) {
        case PrimaryExpNode::Type::Expression:
            level++;
            traverseAddExpNode(root->value.exp);
            level--;
            break;
        case PrimaryExpNode::Type::LValue:
            level++;
            traverseLValNode(root->value.lval);
            level--;
            break;
        case PrimaryExpNode::Type::Number:
            level++;
            traverseNumberNode(root->value.number);
            level--;
            break;
    }
}

void traverseUnaryOpExp(UnaryOpExp* root) {
    // UnaryOpExp 为中间层
    // 不输出，不修改 level

    makeTable();
    switch (root->op_type) {
        case UnaryOpExp::OpType::Minus:
            printf("-\n");
            break;
        case UnaryOpExp::OpType::Plus:
            printf("+\n");
            break;
        case UnaryOpExp::OpType::Not:
            printf("!\n");
            break;
    }

    traverseUnaryExpNode(root->unary_exp);
}

void traverseIdentNode(IdentNode* root) {
    makeTable();
    std::cout << "IdentNode" << "`" << root->filename << "`" << std::endl;
}

void traverseFuncRParamsNode(FuncRParamsNode* root) {
    makeTable();
    printf("%s\n", "FuncRParamsNode");

    level++;
    std::vector<AddExpNode*> &params = root->params;
    for (int i = 0; i < root->params.size(); i++) {
        traverseAddExpNode(params[i]);
    }
    level--;
}

void traverseLValNode(LValNode* root) {
    makeTable();
    printf("%s\n", "LValNode");
    
    level++;
    traverseIdentNode(root->ident);
    level--;

    level++;
    std::vector<AddExpNode*> &indexs = root->indexs;
    for (int i = 0; i < indexs.size(); i++) {
        traverseAddExpNode(indexs[i]);
    }
    level--;
}

void traverseNumberNode(IntNode* root) {
    makeTable();
    printf("%s`%d`\n", "IntNode", root->value);
}
