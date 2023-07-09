%{
#include <string>
#include <cstdlib>
#include "node.h"
#include "parser.tab.hpp"

#define STRING_TOKEN        yylval.string = new std::string(yytext, yyleng)
#define INT_TOKEN(value)    yylval.value = value
#define KEYWORD_TOKEN(t)    yylval.token = t

int lineno = 1;

bool DEBUG = false;
%}

%option noyywrap

/* COMMENT 状态，表示一个多行注释 */
%x COMMENT

%%

"void"                      {
                                // void 类型
                                if (DEBUG)
                                    printf(">> Void\n");
                                KEYWORD_TOKEN(T_VOID);
                                return T_VOID;
                            }

"int"                       {
                                // int 类型
                                if (DEBUG)
                                    printf(">> Int\n");
                                KEYWORD_TOKEN(T_INT);
                                return T_INT;
                            }

"if"                        {
                                // 关键字，if
                                if (DEBUG)
                                    printf(">> If\n");
                                KEYWORD_TOKEN(T_IF);
                                return T_IF;
                            }

"else"                      {
                                // 关键字，else
                                if (DEBUG)
                                    printf(">> Else\n");
                                KEYWORD_TOKEN(T_ELSE);
                                return T_ELSE;
                            }

"while"                     {
                                // 关键字，while
                                if (DEBUG)
                                    printf(">> While\n");
                                KEYWORD_TOKEN(T_WHILE);
                                return T_WHILE;
                            }

"break"                     {
                                // 关键字，break
                                if (DEBUG)
                                    printf(">> Break\n");
                                KEYWORD_TOKEN(T_BREAK);
                                return T_BREAK;
                            }

"const"                     {
                                // 关键字，const
                                if (DEBUG)
                                    printf(">> Const\n");
                                KEYWORD_TOKEN(T_CONST);
                                return T_CONST;
                            }

"continue"                  {
                                // 关键字，continue
                                if (DEBUG)
                                    printf(">> Continue\n");
                                KEYWORD_TOKEN(T_CONTINUE);
                                return T_CONTINUE;
                            }

"return"                    {
                                // 关键字，return
                                if (DEBUG)
                                    printf(">> Return\n");
                                KEYWORD_TOKEN(T_RETURN);
                                return T_RETURN;
                            }

[_a-zA-Z][0-9a-zA-Z]*       {
                                // 标识符
                                if (DEBUG)
                                    printf(">> Ident: `%s`\n", yytext);
                                STRING_TOKEN;
                                return T_IDENT;
                            }

0[0-7]*                     {
                                // 数字常量，八进制
                                if (DEBUG)
                                    printf(">> Digit oct: `%s`\n", yytext);
                                int a = strtol(yytext, NULL, 8);
                                // INT_TOKEN(a);
                                yylval.value = a;
                                return T_NUMBER;
                            }

[0-9]+                      {
                                // 数字常量，十进制
                                if (DEBUG)
                                    printf(">> Digit dec: `%s`\n", yytext);
                                int a = strtol(yytext, NULL, 10);
                                // INT_TOKEN(a);
                                yylval.value = a;
                                return T_NUMBER;
                            }

("0x"|"0X")[0-9a-fA-F]+     {
                                // 数字常量，十六进制
                                if (DEBUG)
                                    printf(">> Digit hex: `%s`\n", yytext);
                                int a = strtol(yytext, NULL, 16);
                                // INT_TOKEN(a);
                                yylval.value = a;
                                return T_NUMBER;
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
                                if (DEBUG)
                                    printf(">> Char symbol: `%s`\n", yytext);
                                return yytext[0];
                            }

"&&"                        {
                                // 逻辑运算符，与
                                if (DEBUG)
                                    printf(">> And\n");
                                KEYWORD_TOKEN(T_AND);
                                return T_AND;
                            }

"||"                        {
                                // 逻辑运算符，或
                                if (DEBUG)
                                    printf(">> Or\n");
                                KEYWORD_TOKEN(T_OR);
                                return T_OR;
                            }

"=="                        {
                                // 关系运算符，等于
                                if (DEBUG)
                                    printf(">> Equal\n");
                                KEYWORD_TOKEN(T_EQ);
                                return T_EQ;
                            }

"!="                        {
                                // 关系运算符，不等于
                                if (DEBUG)
                                    printf(">> Not equal\n");
                                KEYWORD_TOKEN(T_NE);
                                return T_NE;
                            }

"<="                        {
                                // 关系运算符，小于等于
                                if (DEBUG)
                                    printf(">> Less equal\n");
                                KEYWORD_TOKEN(T_LE);
                                return T_LE;
                            }

">="                        {
                                // 关系运算符，大于等于
                                if (DEBUG)
                                    printf(">> Greater equal\n");
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
                                printf(">> -- SRC ERROR: Line %d: Unterminated comment\n", lineno);
                                // return YYerror;
                            }

"//".*\n                    {
                                lineno++;
                                ; // 忽略行注释
                            }

\n                          {
                                if (DEBUG)
                                    ECHO;
                                lineno++;
                            }

[ \t]                       {
                                // 空白符
                                // printf(">> -- IGNORED: space\n");
                            }

<<EOF>>                     { yyterminate(); }

.                           {
                                // 自检查
                                printf(">> -- SCANNER ERROR: Line %d: `%s` not recognized\n", lineno, yytext);
                            }
