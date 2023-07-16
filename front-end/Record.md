# 搭建符号表

发现了问题，符号表不能在规约的时候创建，而是在遍历的时候创建。

对于函数的声明/定义，先记录函数到当前符号表，然后切换到新的符号表。分为以下几类：
- 函数声明，`declare`
- 函数定义，`define`
  - 不加修饰符，`externel`
  - 静态函数，`internel`
  - ~~给别的文件使用的全局变量或函数，可以加上`dso_local`，保证不会被抢占~~

对于变量的声明，需要在VarDecl这一层进行符号的创建。关于符号的类型，分为以下几类：
- 全局变量，对应在LLVM IR中使用`@global_variable = global i32 0`/`@global_constant = constant i32 0`，这里需要注意`@`后面的是**变量名称**。
- 局部变量，在LLVM IR中使用`private`修饰，使用`private`修饰的变量不会出现在符号表中，即其他文件看不到。
- 静态变量，在LLVM IR中使用`internel`修饰，会记录在符号表中，但是链接时不会参与符号解析

第一次重构把生成IR的函数分成了多个函数；第二次重构，在AST层面去掉DECL_WITH_IDENT这个结构。

第一次修改后状态：
```
<VarDecl, , VAR_DECL> 
    <int, , CONST> 
    <a, , CONST> 
    <VarDefList, , JUST_CONCAT> 
        <VarDef, , JUST_CONTINUE> 
            <ConstExpList, , error> 
            <InitVal, , error> 
                <Exp, , JUST_PASS> 
                    <AddExp, , JUST_PASS> 
                        <MulExp, , JUST_PASS> 
                            <UnaryExp, , JUST_PASS> 
                                <PrimaryExp, , JUST_PASS> 
                                    <Number, 3, CONST> 
```

显然这是有问题的，因为a应该放在第一个VarDef中。修改后`VarDecl`的情况正确了：
```
<VarDecl, , VAR_DECL> 
    <int, , CONST> 
    <VarDefList, , JUST_CONCAT> 
        <VarDef, , JUST_CONTINUE> 
            <a, , CONST> 
            <ConstExpList, , error> 
            <InitVal, , error> 
                <Exp, , JUST_PASS> 
                    <AddExp, , JUST_PASS> 
                        <MulExp, , JUST_PASS> 
                            <UnaryExp, , JUST_PASS> 
                                <PrimaryExp, , JUST_PASS> 
                                    <Number, 3, CONST> 
```

另一个需要修改的地方是ConstDecl，修改的方法是一样的。

## 表达式生成

​                    <VarDef, , JUST_CONTINUE> 
​                        <a, , CONST> 
​                        <ConstExpList, , error> 
​                        <InitVal, , error> 
​                            <Exp, , JUST_PASS> 
​                                <AddExp, , JUST_PASS> 
​                                    <MulExp, , JUST_PASS> 
​                                        <UnaryExp, , JUST_PASS> 
​                                            <PrimaryExp, , JUST_PASS> 
​                                                <Number, 3, CONST> 

表达式如上，目前只需要向下传送，然后进行常数折叠；如果涉及到变量的表达式，需要逐层返回计算结果，最后通过Exp将结果寄存器返回给InitVal。

传回InitVal的方式通过写**符号表**，这样不需要直接使用全局量。但是这样需要向下传输符号的名称。==之后要去掉中间的冗余节点。==这样需要修改符号表，将value变成一个union，可以存储常数值，或者是寄存器的地址。

## 通过样例情况

0：main

1-3：变量定义

8-10：const变量定义

12-13：函数定义、调用

14-19：AddExp

20-25：MulExp

26-27：简单if语句

28，30-32：复杂if语句

33-36：while语句不带break



## 不成立样例情况

29，33：`putint`
