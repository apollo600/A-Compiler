/* A Bison parser, made by GNU Bison 3.8.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_IDENT = 258,                 /* T_IDENT  */
    T_NUMBER = 259,                /* T_NUMBER  */
    T_AND = 260,                   /* T_AND  */
    T_OR = 261,                    /* T_OR  */
    T_EQ = 262,                    /* T_EQ  */
    T_NE = 263,                    /* T_NE  */
    T_LE = 264,                    /* T_LE  */
    T_GE = 265,                    /* T_GE  */
    T_LESS = 266,                  /* T_LESS  */
    T_GREATER = 267,               /* T_GREATER  */
    T_VOID = 268,                  /* T_VOID  */
    T_INT = 269,                   /* T_INT  */
    T_IF = 270,                    /* T_IF  */
    T_ELSE = 271,                  /* T_ELSE  */
    T_WHILE = 272,                 /* T_WHILE  */
    T_BREAK = 273,                 /* T_BREAK  */
    T_CONTINUE = 274,              /* T_CONTINUE  */
    T_RETURN = 275,                /* T_RETURN  */
    T_CONST = 276,                 /* T_CONST  */
    T_ASSIGN = 277,                /* T_ASSIGN  */
    T_SEMI = 278,                  /* T_SEMI  */
    T_COMMA = 279,                 /* T_COMMA  */
    T_LBRACE = 280,                /* T_LBRACE  */
    T_RBRACE = 281,                /* T_RBRACE  */
    T_LBRACKET = 282,              /* T_LBRACKET  */
    T_RBRACKET = 283,              /* T_RBRACKET  */
    T_LCURLY = 284,                /* T_LCURLY  */
    T_RCURLY = 285,                /* T_RCURLY  */
    T_NOT = 286,                   /* T_NOT  */
    T_ADD = 287,                   /* T_ADD  */
    T_MINUS = 288,                 /* T_MINUS  */
    T_MULT = 289,                  /* T_MULT  */
    T_DIV = 290,                   /* T_DIV  */
    T_MOD = 291                    /* T_MOD  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 13 "parser.ypp"

    std::string *string;
    int token;
    int value;
    char op;
    // ------------------
    IdentNode *ident_node;
    LValNode *l_val_node;
    PrimaryExpNode *primary_exp_node;
    IntNode *int_node;
    FuncRParamsNode *func_r_params_node;
    UnaryExpNode *unary_exp_node;
    MulExpNode *mul_exp_node;
    AddExpNode *add_exp_node;
    ConstExpNode *const_exp_node;
    RelExpNode *rel_exp_node;
    EqExpNode *eq_exp_node;
    LAndExpNode *l_and_exp_node;
    LOrExpNode *l_or_exp_node;

#line 121 "parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */
