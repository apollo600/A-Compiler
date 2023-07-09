%{

    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    // #include "scanner/scanner.h"
    #include "parser/parser.tab.hpp"
    #include "parser/node.h"

    using namespace std;
    string filename;
    int lineno = 1;
    Node *flex_node;

%}

/* 产生yywrap函数 */
%option noyywrap

/* flex 生成的扫描器用全局变量lineno 维护着输入文件的当前行编号 */
/* %option yylineno */

/* 区分大小写 */
%option case-sensitive

/* yytext的类型为指针类型，即char * */
%option pointer

/* COMMENT 状态，表示一个多行注释 */
%x COMMENT

/***** 正则式定义 *****/
%%

"void"                      {
                                // void 类型
                                printf("Void\n");
                                return VOID;
                            }

"int"                       {
                                // int 类型
                                printf("Int\n");
                                return INT;
                            }

"if"                        {
                                // 关键字，if
                                printf("If\n");
                                return IF;
                            }

"else"                      {
                                // 关键字，else
                                printf("Else\n");
                                return ELSE;
                            }

"while"                     {
                                // 关键字，while
                                printf("While\n");
                                return WHILE;
                            }

"break"                     {
                                // 关键字，break
                                printf("Break\n");
                                return BREAK;
                            }

"continue"                  {
                                // 关键字，continue
                                printf("Continue\n");
                                return CONTINUE;
                            }

"return"                    {
                                // 关键字，return
                                printf("Return\n");
                                return RETURN;
                            }

[_a-zA-Z][0-9a-zA-Z]*       {
                                // 标识符
                                printf("Ident: `%s`\n", yytext);
                                Node *node = new Node(filename, lineno, NODE_IDENT);
                                node->var_name = yytext;
                                flex_node = node;
                                return IDENT;
                            }

0[0-7]*                     {
                                // 数字常量，八进制
                                printf("Digit oct: `%s`\n", yytext);
                                Node *node = new Node(filename, lineno, NODE_CONST);
                                node->number_value = (int)strtol(yytext, (char **)NULL, 8);
                                flex_node = node;
                                return NUMBER;
                            }

[0-9]+                      {
                                // 数字常量，十进制
                                printf("Digit dec: `%s`\n", yytext);
                                Node *node = new Node(filename, lineno, NODE_CONST);
                                node->number_value = (int)strtol(yytext, (char **)NULL, 10);
                                flex_node = node;
                                return NUMBER;
                            }

("0x"|"0X")[0-9a-fA-F]+     {
                                // 数字常量，十六进制
                                printf("Digit hex: `%s`\n", yytext);
                                Node *node = new Node(filename, lineno, NODE_CONST);
                                node->number_value = (int)strtol(yytext, (char **)NULL, 16);
                                flex_node = node;
                                return NUMBER;
                            }

"=" |
";" |
"," |
"(" |
")" |
"[" |
"]" |
"{" |
"}" |
"!" |
"+" |
"-" |
"*" |
"/" |
"%" |
"<" |
">"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return yytext[0];
                            }

"&&"                        {
                                // 逻辑运算符，与
                                printf("And\n");
                                return AND;
                            }

"||"                        {
                                // 逻辑运算符，或
                                printf("Or\n");
                                return OR;
                            }

"=="                        {
                                // 关系运算符，等于
                                printf("Equal\n");
                                return EQ;
                            }

"!="                        {
                                // 关系运算符，不等于
                                printf("Not equal\n");
                                return NE;
                            }

"<="                        {
                                // 关系运算符，小于等于
                                printf("Less equal\n");
                                return LE;
                            }

">="                        {
                                // 关系运算符，大于等于
                                printf("Greater equal\n");
                                return GE;
                            }

"/*"                        {
                                // 进入注释子有限自动机
                                BEGIN(COMMENT);
                            }

<COMMENT>"*/"               {
                                // 结束注释子有限自动机
                                BEGIN(INITIAL);
                            }    

<COMMENT>\n                 {
                                lineno++;
                            }

<COMMENT>[^*]+|.            {
                                ; // 注释子有限自动机中，忽略所有字符，含换行符等
                            }

<COMMENT><<EOF>>            {
                                // 没遇到 */ 但是文件结束
                                printf("-- SRC ERROR: Line %d: Unterminated comment\n", lineno);
                                // return YYerror;
                            }

"//".*\n                    {
                                lineno++;
                                ; // 忽略行注释
                            }

\n                          {
                                ECHO;
                                lineno++;
                            }

[ \t]                       {
                                // 空白符
                                // printf("-- IGNORED: space\n");
                            }

<<EOF>>                     {
                                // 文件结尾
                                exit(0);
                            }

.                           {
                                // 自检查
                                printf("-- SCANNER ERROR: Line %d: `%s` not recognized\n", lineno, yytext);
                            }

%%

// int main(int argc, char **argv) {
//     FILE *f;
//     YY_BUFFER_STATE bs;

//     if (argc < 2) {
//         printf("-- Use stdin as input\n");
//     } else {
//         printf("-- Use %s as input\n", argv[1]);
//         filename = argv[1];
//         f = fopen(argv[1], "r");
//         bs = yy_create_buffer(f, YY_BUF_SIZE);
//         yy_switch_to_buffer(bs);
//     }
//     // 循环解析，直至遇到 EOF
//     while (1) {
//         yylex();
//     }
//     return 0;
// }
