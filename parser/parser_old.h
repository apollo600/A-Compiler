#include <vector>
using namespace std;

enum {
    CompUnit, 
};

struct CompUnit {
    int node_type;
    union {
        struct Decl *decl;
        struct FuncDef *func_def;
    } items[];
};

struct Decl {
    int node_type;
    bool is_const;
    int b_type;
    struct Def *defs;
};

struct Def {
    int node_type;
    bool is_const;
    struct Ident *ident;
    vector<int> shape;
    struct InitVal *init_val;
};

struct InitVal {
    int node_type;
    bool is_const;
    // 用于 {1, 2, 3} 这种形式的初始值，构造一个链表
    struct InitVal *next;
};

struct FuncDef {
    int node_type;
    int func_type;
    struct Ident *ident;
    struct FuncParam *params;
    struct Block *block;
};

struct FuncParam {
    int node_type;
    int b_type;
    struct Ident *ident;
    struct Shape *shape;
    struct FuncParam *next;
};

struct Shape {
    int node_type;
    int value;
    struct Shape *next;
};

struct Stmt {
    int node_type;
    int stmt_type;
    union {
        struct AssignStmt *assign_stmt;
        struct SingleStmt *single_stmt;
        struct Block *block;
        struct IfStmt *if_stmt;
        struct WhileStmt *while_stmt;
        struct BreakStmt *break_stmt;
        struct ContinueStmt *continue_stmt;
        struct ReturnStmt *return_stmt;
    } stmt;
};

struct Block {
    int node_type;
    struct Block *next;
    union {
        struct Decl *decl;
        struct Stmt *stmt;
    } items[];
};

struct AssignStmt {
    int node_type;
    struct LVal *lval;
    struct Exp *exp;
};

struct SingleStmt {
    int node_type;
    struct Exp *exp;
};

struct IfStmt {
    int node_type;
    struct Cond *cond;
    struct Stmt *cond_stmt;
    struct Stmt *else_stmt;
};

struct WhileStmt {
    int node_type;
    struct Cond *cond;
    struct Stmt *stmt;
};

struct BreakStmt {
    int node_type;
};

struct ContinueStmt {
    int node_type;
};

struct ReturnStmt {
    int node_type;
    struct Exp *exp;
};

struct LVal {
    int node_type;
    struct Ident *ident;
    struct Exp *index;
};

struct Number {
    int node_type;
    int value;
};

struct UnaryExp {
    int node_type;
    struct UnaryExp *next;
    union {
        struct PrimaryExp *primary_exp;
        struct FuncExp *func_exp;
        struct MinusExp *minus_exp;
    } unary_exp;
};

// Cond -> LOrExp
struct Cond {

};

struct Exp {

};
