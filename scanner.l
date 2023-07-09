%{
#include <string>
#include <cstdlib>
#include "node.h"
#include "parser.tab.hpp"

#define STRING_TOKEN        yylval.string = new std::string(yytext, yyleng)
#define INT_TOKEN(value)    yylval.value = value
#define KEYWORD_TOKEN(t)    yylval.token = t

int lineno = 1;
%}

%option noyywrap

/* COMMENT 状态，表示一个多行注释 */
%x COMMENT

%%

"void"                      {
                                // void 类型
                                printf("Void\n");
                                KEYWORD_TOKEN(T_VOID);
                                return T_VOID;
                            }

"int"                       {
                                // int 类型
                                printf("Int\n");
                                KEYWORD_TOKEN(T_INT);
                                return T_INT;
                            }

"if"                        {
                                // 关键字，if
                                printf("If\n");
                                KEYWORD_TOKEN(T_IF);
                                return T_IF;
                            }

"else"                      {
                                // 关键字，else
                                printf("Else\n");
                                KEYWORD_TOKEN(T_ELSE);
                                return T_ELSE;
                            }

"while"                     {
                                // 关键字，while
                                printf("While\n");
                                KEYWORD_TOKEN(T_WHILE);
                                return T_WHILE;
                            }

"break"                     {
                                // 关键字，break
                                printf("Break\n");
                                KEYWORD_TOKEN(T_BREAK);
                                return T_BREAK;
                            }

"continue"                  {
                                // 关键字，continue
                                printf("Continue\n");
                                KEYWORD_TOKEN(T_CONTINUE);
                                return T_CONTINUE;
                            }

"return"                    {
                                // 关键字，return
                                printf("Return\n");
                                KEYWORD_TOKEN(T_RETURN);
                                return T_RETURN;
                            }

"const"                     {
                                // 关键字，return
                                printf("Const\n");
                                KEYWORD_TOKEN(T_CONST);
                                return T_CONST;
                            }

[_a-zA-Z][0-9a-zA-Z]*       {
                                // 标识符
                                printf("Ident: `%s`\n", yytext);
                                STRING_TOKEN;
                                return T_IDENT;
                            }

0[0-7]*                     {
                                // 数字常量，八进制
                                printf("Digit oct: `%s`\n", yytext);
                                int a = strtol(yytext, NULL, 8);
                                // INT_TOKEN(a);
                                yylval.value = a;
                                return T_NUMBER;
                            }

[0-9]+                      {
                                // 数字常量，十进制
                                printf("Digit dec: `%s`\n", yytext);
                                int a = strtol(yytext, NULL, 10);
                                // INT_TOKEN(a);
                                yylval.value = a;
                                return T_NUMBER;
                            }

("0x"|"0X")[0-9a-fA-F]+     {
                                // 数字常量，十六进制
                                printf("Digit hex: `%s`\n", yytext);
                                int a = strtol(yytext, NULL, 16);
                                // INT_TOKEN(a);
                                yylval.value = a;
                                return T_NUMBER;
                            }

"="                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_ASSIGN;
                            }

";"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_SEMI;
                            }

","                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_COMMA;
                            }

"("                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_LBRACE;
                            }

")"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_RBRACE;
                            }

"["                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_LBRACKET;
                            }

"]"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_RBRACKET;
                            }

"{"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_LCURLY;
                            }

"}"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_RCURLY;
                            }

"!"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_NOT;
                            }

"+"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_ADD;
                            }

"-"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_MINUS;
                            }

"*"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_MULT;
                            }

"/"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_DIV;
                            }

"%"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_MOD;
                            }

"<"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_LESS;
                            }

">"                         {
                                printf("Char symbol: `%s`\n", yytext);
                                return T_GREATER;
                            }

"&&"                        {
                                // 逻辑运算符，与
                                printf("And\n");
                                KEYWORD_TOKEN(T_AND);
                                return T_AND;
                            }

"||"                        {
                                // 逻辑运算符，或
                                printf("Or\n");
                                KEYWORD_TOKEN(T_OR);
                                return T_OR;
                            }

"=="                        {
                                // 关系运算符，等于
                                printf("Equal\n");
                                KEYWORD_TOKEN(T_EQ);
                                return T_EQ;
                            }

"!="                        {
                                // 关系运算符，不等于
                                printf("Not equal\n");
                                KEYWORD_TOKEN(T_NE);
                                return T_NE;
                            }

"<="                        {
                                // 关系运算符，小于等于
                                printf("Less equal\n");
                                KEYWORD_TOKEN(T_LE);
                                return T_LE;
                            }

">="                        {
                                // 关系运算符，大于等于
                                printf("Greater equal\n");
                                KEYWORD_TOKEN(T_GE);
                                return T_GE;
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
