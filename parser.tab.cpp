/* A Bison parser, made by GNU Bison 3.8.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30800

/* Bison version string.  */
#define YYBISON_VERSION "3.8"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.ypp"

#include "node.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

extern int yylex();
void yyerror(const char *s) { std::printf("Error: %s\n", s);std::exit(1); }

AddExpNode* root_node;

#line 83 "parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_IDENT = 3,                    /* T_IDENT  */
  YYSYMBOL_T_NUMBER = 4,                   /* T_NUMBER  */
  YYSYMBOL_T_AND = 5,                      /* T_AND  */
  YYSYMBOL_T_OR = 6,                       /* T_OR  */
  YYSYMBOL_T_EQ = 7,                       /* T_EQ  */
  YYSYMBOL_T_NE = 8,                       /* T_NE  */
  YYSYMBOL_T_LE = 9,                       /* T_LE  */
  YYSYMBOL_T_GE = 10,                      /* T_GE  */
  YYSYMBOL_T_LESS = 11,                    /* T_LESS  */
  YYSYMBOL_T_GREATER = 12,                 /* T_GREATER  */
  YYSYMBOL_T_VOID = 13,                    /* T_VOID  */
  YYSYMBOL_T_INT = 14,                     /* T_INT  */
  YYSYMBOL_T_IF = 15,                      /* T_IF  */
  YYSYMBOL_T_ELSE = 16,                    /* T_ELSE  */
  YYSYMBOL_T_WHILE = 17,                   /* T_WHILE  */
  YYSYMBOL_T_BREAK = 18,                   /* T_BREAK  */
  YYSYMBOL_T_CONTINUE = 19,                /* T_CONTINUE  */
  YYSYMBOL_T_RETURN = 20,                  /* T_RETURN  */
  YYSYMBOL_T_CONST = 21,                   /* T_CONST  */
  YYSYMBOL_T_ASSIGN = 22,                  /* T_ASSIGN  */
  YYSYMBOL_T_SEMI = 23,                    /* T_SEMI  */
  YYSYMBOL_T_COMMA = 24,                   /* T_COMMA  */
  YYSYMBOL_T_LBRACE = 25,                  /* T_LBRACE  */
  YYSYMBOL_T_RBRACE = 26,                  /* T_RBRACE  */
  YYSYMBOL_T_LBRACKET = 27,                /* T_LBRACKET  */
  YYSYMBOL_T_RBRACKET = 28,                /* T_RBRACKET  */
  YYSYMBOL_T_LCURLY = 29,                  /* T_LCURLY  */
  YYSYMBOL_T_RCURLY = 30,                  /* T_RCURLY  */
  YYSYMBOL_T_NOT = 31,                     /* T_NOT  */
  YYSYMBOL_T_ADD = 32,                     /* T_ADD  */
  YYSYMBOL_T_MINUS = 33,                   /* T_MINUS  */
  YYSYMBOL_T_MULT = 34,                    /* T_MULT  */
  YYSYMBOL_T_DIV = 35,                     /* T_DIV  */
  YYSYMBOL_T_MOD = 36,                     /* T_MOD  */
  YYSYMBOL_37_ = 37,                       /* '('  */
  YYSYMBOL_38_ = 38,                       /* ')'  */
  YYSYMBOL_39_ = 39,                       /* ','  */
  YYSYMBOL_40_ = 40,                       /* '['  */
  YYSYMBOL_41_ = 41,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_CompRoot = 43,                  /* CompRoot  */
  YYSYMBOL_CompUnit = 44,                  /* CompUnit  */
  YYSYMBOL_Decl = 45,                      /* Decl  */
  YYSYMBOL_ConstDecl = 46,                 /* ConstDecl  */
  YYSYMBOL_ConstDefList = 47,              /* ConstDefList  */
  YYSYMBOL_BType = 48,                     /* BType  */
  YYSYMBOL_ConstDef = 49,                  /* ConstDef  */
  YYSYMBOL_ConstIndex = 50,                /* ConstIndex  */
  YYSYMBOL_ConstInitVal = 51,              /* ConstInitVal  */
  YYSYMBOL_ConstInitValList = 52,          /* ConstInitValList  */
  YYSYMBOL_VarDecl = 53,                   /* VarDecl  */
  YYSYMBOL_VarDefList = 54,                /* VarDefList  */
  YYSYMBOL_VarDef = 55,                    /* VarDef  */
  YYSYMBOL_ConstExpList = 56,              /* ConstExpList  */
  YYSYMBOL_InitVal = 57,                   /* InitVal  */
  YYSYMBOL_InitValList = 58,               /* InitValList  */
  YYSYMBOL_FuncDef = 59,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 60,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 61,                /* FuncFParam  */
  YYSYMBOL_Indexs = 62,                    /* Indexs  */
  YYSYMBOL_VarName = 63,                   /* VarName  */
  YYSYMBOL_BlockItemList = 64,             /* BlockItemList  */
  YYSYMBOL_BlockItem = 65,                 /* BlockItem  */
  YYSYMBOL_Block = 66,                     /* Block  */
  YYSYMBOL_Stmt = 67,                      /* Stmt  */
  YYSYMBOL_Exp = 68,                       /* Exp  */
  YYSYMBOL_ConstExp = 69,                  /* ConstExp  */
  YYSYMBOL_Cond = 70,                      /* Cond  */
  YYSYMBOL_LOrExp = 71,                    /* LOrExp  */
  YYSYMBOL_LAndExp = 72,                   /* LAndExp  */
  YYSYMBOL_EqExp = 73,                     /* EqExp  */
  YYSYMBOL_RelExp = 74,                    /* RelExp  */
  YYSYMBOL_RelOp = 75,                     /* RelOp  */
  YYSYMBOL_EqOp = 76,                      /* EqOp  */
  YYSYMBOL_AddExp = 77,                    /* AddExp  */
  YYSYMBOL_AddOp = 78,                     /* AddOp  */
  YYSYMBOL_MulExp = 79,                    /* MulExp  */
  YYSYMBOL_MulOp = 80,                     /* MulOp  */
  YYSYMBOL_UnaryExp = 81,                  /* UnaryExp  */
  YYSYMBOL_FuncRParams = 82,               /* FuncRParams  */
  YYSYMBOL_UnaryOp = 83,                   /* UnaryOp  */
  YYSYMBOL_PrimaryExp = 84,                /* PrimaryExp  */
  YYSYMBOL_LVal = 85,                      /* LVal  */
  YYSYMBOL_Ident = 86,                     /* Ident  */
  YYSYMBOL_Number = 87                     /* Number  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   223

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  179

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      37,    38,     2,     2,    39,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    66,    66,    67,    70,    71,    74,    75,    78,    81,
      82,    85,    88,    89,    92,    93,    96,    97,    98,   101,
     102,   105,   108,   109,   112,   113,   116,   117,   120,   121,
     122,   125,   126,   129,   130,   131,   132,   135,   136,   139,
     140,   143,   144,   147,   151,   152,   155,   156,   159,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     174,   177,   180,   183,   184,   190,   191,   197,   198,   205,
     206,   213,   214,   215,   216,   219,   220,   223,   224,   230,
     231,   234,   235,   241,   242,   243,   246,   247,   251,   255,
     261,   262,   265,   266,   267,   270,   271,   272,   275,   276,
     279,   282
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_IDENT", "T_NUMBER",
  "T_AND", "T_OR", "T_EQ", "T_NE", "T_LE", "T_GE", "T_LESS", "T_GREATER",
  "T_VOID", "T_INT", "T_IF", "T_ELSE", "T_WHILE", "T_BREAK", "T_CONTINUE",
  "T_RETURN", "T_CONST", "T_ASSIGN", "T_SEMI", "T_COMMA", "T_LBRACE",
  "T_RBRACE", "T_LBRACKET", "T_RBRACKET", "T_LCURLY", "T_RCURLY", "T_NOT",
  "T_ADD", "T_MINUS", "T_MULT", "T_DIV", "T_MOD", "'('", "')'", "','",
  "'['", "']'", "$accept", "CompRoot", "CompUnit", "Decl", "ConstDecl",
  "ConstDefList", "BType", "ConstDef", "ConstIndex", "ConstInitVal",
  "ConstInitValList", "VarDecl", "VarDefList", "VarDef", "ConstExpList",
  "InitVal", "InitValList", "FuncDef", "FuncFParams", "FuncFParam",
  "Indexs", "VarName", "BlockItemList", "BlockItem", "Block", "Stmt",
  "Exp", "ConstExp", "Cond", "LOrExp", "LAndExp", "EqExp", "RelExp",
  "RelOp", "EqOp", "AddExp", "AddOp", "MulExp", "MulOp", "UnaryExp",
  "FuncRParams", "UnaryOp", "PrimaryExp", "LVal", "Ident", "Number", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-117)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      45,    52,  -117,    29,    15,  -117,  -117,  -117,    52,  -117,
    -117,    82,  -117,    95,    52,  -117,  -117,    59,  -117,    38,
      -4,    13,   167,  -117,    75,  -117,    52,   165,    77,    71,
      52,    -8,  -117,    85,    71,    87,  -117,    52,   143,   165,
      81,  -117,    38,  -117,  -117,  -117,  -117,   165,    94,   161,
     126,  -117,   165,  -117,    99,    88,  -117,   152,   165,  -117,
    -117,  -117,    29,    71,   117,  -117,    71,  -117,   120,  -117,
    -117,   142,   143,   165,    89,   161,  -117,  -117,  -117,   165,
    -117,  -117,  -117,   165,  -117,   165,    31,   134,  -117,  -117,
     145,    57,  -117,  -117,  -117,  -117,  -117,  -117,    61,  -117,
    -117,   149,  -117,   126,  -117,   113,  -117,  -117,   -15,  -117,
    -117,    68,  -117,   110,   154,   159,   172,   155,  -117,  -117,
    -117,    52,  -117,  -117,  -117,   178,    10,   176,   143,  -117,
    -117,  -117,  -117,   165,   152,  -117,   165,   165,  -117,  -117,
    -117,   181,  -117,   165,   165,  -117,  -117,  -117,   179,   200,
     202,   192,   107,   161,   182,  -117,   186,   183,   111,   165,
     165,  -117,  -117,   165,  -117,  -117,  -117,  -117,   165,   111,
    -117,  -117,   111,   202,   192,   107,   161,  -117,  -117
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    11,     0,     0,     2,     4,     6,     0,     7,
       5,     0,   100,     0,     0,     1,     3,     0,    22,    43,
       0,     0,     0,     9,     0,    21,     0,     0,    24,     0,
       0,     0,    37,    39,     0,     0,     8,     0,     0,     0,
       0,    23,     0,   101,    94,    92,    93,     0,     0,    61,
      77,    81,     0,    86,    96,    98,    97,     0,     0,    44,
      33,    43,     0,     0,     0,    35,     0,    10,     0,    12,
      16,     0,     0,     0,     0,    60,    26,    79,    80,     0,
      83,    84,    85,     0,    89,     0,     0,     0,    25,    28,
       0,     0,    38,    34,    41,    36,    17,    19,     0,    14,
      13,     0,    95,    78,    82,     0,    87,    90,     0,    29,
      31,     0,    27,     0,     0,     0,     0,     0,    50,    48,
      46,     0,    45,    52,    47,     0,    96,    40,     0,    18,
      15,    99,    88,     0,     0,    30,     0,     0,    56,    57,
      58,     0,    51,     0,     0,    20,    91,    32,     0,    62,
      63,    65,    67,    69,     0,    59,     0,     0,     0,     0,
       0,    75,    76,     0,    73,    74,    71,    72,     0,     0,
      49,    42,    53,    64,    66,    68,    70,    55,    54
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -117,  -117,   206,   121,  -117,  -117,     2,   177,  -117,   -55,
    -117,  -117,  -117,   187,  -117,   -83,  -117,  -117,   194,   156,
    -117,    40,  -117,  -117,    -9,  -116,   -38,    -6,    79,  -117,
      58,    60,    56,  -117,  -117,   -27,  -117,   144,  -117,   -45,
    -117,  -117,  -117,   -88,     0,  -117
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     4,     5,     6,     7,    22,    30,    23,    40,    69,
      98,     9,    17,    18,    28,    88,   111,    10,    31,    32,
     127,    33,    91,   122,   123,   124,   125,    70,   148,   149,
     150,   151,   152,   168,   163,    75,    79,    50,    83,    51,
     108,    52,    53,    54,    55,    56
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      49,    13,     8,   126,   110,    14,     8,    84,    19,    74,
       2,    49,    49,    97,    24,    15,    62,   100,    63,    89,
      60,    48,    29,   132,   133,    65,    42,     2,     1,     2,
      61,    49,   143,    71,    12,    43,     3,    24,   104,    34,
      11,    49,   172,     2,    11,    49,    49,   105,   107,    89,
      85,   147,    90,   177,    93,    12,   178,    95,     1,     2,
      12,    43,    44,    45,    46,    27,     3,   101,    47,   106,
     126,     2,   113,   145,   114,   115,   116,   117,     3,   141,
     118,   126,    25,    26,   126,   128,    59,   119,    44,    45,
      46,   129,   134,   121,    47,   146,    89,    38,   135,    57,
      59,    49,    39,    72,    58,   156,   157,    20,    73,   153,
     153,    62,    64,    66,    12,    43,   164,   165,   166,   167,
      21,    42,    76,    12,    43,    86,   113,   102,   114,   115,
     116,   117,   153,   153,   118,   136,   153,    12,    43,    85,
      59,   176,    44,    45,    46,    94,    12,    43,    47,    68,
      96,    44,    45,    46,   131,    12,    43,    47,    12,    43,
      80,    81,    82,    87,   109,    44,    45,    46,    12,    43,
      99,    47,    68,   112,    44,    45,    46,   130,   140,   137,
      47,    87,   138,    44,    45,    46,    44,    45,    46,    47,
      36,    37,    47,    77,    78,   139,    44,    45,    46,   161,
     162,   142,    47,   144,   155,   158,   159,   160,   169,   170,
      16,   171,   120,    41,    67,    35,   154,   173,    92,   175,
     174,     0,     0,   103
};

static const yytype_int16 yycheck[] =
{
      27,     1,     0,    91,    87,     3,     4,    52,     8,    47,
      14,    38,    39,    68,    14,     0,    24,    72,    26,    57,
      29,    27,    26,    38,    39,    34,    26,    14,    13,    14,
      30,    58,    22,    39,     3,     4,    21,    37,    83,    26,
       0,    68,   158,    14,     4,    72,    73,    85,    86,    87,
      40,   134,    58,   169,    63,     3,   172,    66,    13,    14,
       3,     4,    31,    32,    33,    27,    21,    73,    37,    38,
     158,    14,    15,   128,    17,    18,    19,    20,    21,   117,
      23,   169,    23,    24,   172,    24,    29,    30,    31,    32,
      33,    30,    24,    91,    37,   133,   134,    22,    30,    22,
      29,   128,    27,    22,    27,   143,   144,    25,    27,   136,
     137,    24,    27,    26,     3,     4,     9,    10,    11,    12,
      25,   121,    28,     3,     4,    37,    15,    38,    17,    18,
      19,    20,   159,   160,    23,    25,   163,     3,     4,    40,
      29,   168,    31,    32,    33,    28,     3,     4,    37,    29,
      30,    31,    32,    33,    41,     3,     4,    37,     3,     4,
      34,    35,    36,    29,    30,    31,    32,    33,     3,     4,
      28,    37,    29,    28,    31,    32,    33,    28,    23,    25,
      37,    29,    23,    31,    32,    33,    31,    32,    33,    37,
      23,    24,    37,    32,    33,    23,    31,    32,    33,     7,
       8,    23,    37,    27,    23,    26,     6,     5,    26,    23,
       4,    28,    91,    26,    37,    21,   137,   159,    62,   163,
     160,    -1,    -1,    79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    13,    14,    21,    43,    44,    45,    46,    48,    53,
      59,    63,     3,    86,    48,     0,    44,    54,    55,    86,
      25,    25,    47,    49,    86,    23,    24,    27,    56,    26,
      48,    60,    61,    63,    26,    60,    23,    24,    22,    27,
      50,    55,    86,     4,    31,    32,    33,    37,    69,    77,
      79,    81,    83,    84,    85,    86,    87,    22,    27,    29,
      66,    86,    24,    26,    27,    66,    26,    49,    29,    51,
      69,    69,    22,    27,    68,    77,    28,    32,    33,    78,
      34,    35,    36,    80,    81,    40,    37,    29,    57,    68,
      69,    64,    61,    66,    28,    66,    30,    51,    52,    28,
      51,    69,    38,    79,    81,    68,    38,    68,    82,    30,
      57,    58,    28,    15,    17,    18,    19,    20,    23,    30,
      45,    48,    65,    66,    67,    68,    85,    62,    24,    30,
      28,    41,    38,    39,    24,    30,    25,    25,    23,    23,
      23,    68,    23,    22,    27,    51,    68,    57,    70,    71,
      72,    73,    74,    77,    70,    23,    68,    68,    26,     6,
       5,     7,     8,    76,     9,    10,    11,    12,    75,    26,
      23,    28,    67,    72,    73,    74,    77,    67,    67
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    43,    44,    44,    45,    45,    46,    47,
      47,    48,    49,    49,    50,    50,    51,    51,    51,    52,
      52,    53,    54,    54,    55,    55,    56,    56,    57,    57,
      57,    58,    58,    59,    59,    59,    59,    60,    60,    61,
      61,    62,    62,    63,    64,    64,    65,    65,    66,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      68,    69,    70,    71,    71,    72,    72,    73,    73,    74,
      74,    75,    75,    75,    75,    76,    76,    77,    77,    78,
      78,    79,    79,    80,    80,    80,    81,    81,    81,    81,
      82,    82,    83,    83,    83,    84,    84,    84,    85,    85,
      86,    87
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     4,     1,
       3,     1,     3,     4,     3,     4,     1,     2,     3,     1,
       3,     3,     1,     3,     2,     4,     3,     4,     1,     2,
       3,     1,     3,     4,     5,     5,     6,     1,     3,     1,
       4,     0,     4,     2,     0,     2,     1,     1,     3,     4,
       1,     2,     1,     5,     6,     5,     2,     2,     2,     3,
       1,     1,     1,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     1,     3,     4,     2,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     4,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 60: /* Exp: AddExp  */
#line 174 "parser.ypp"
                       { root_node = (yyvsp[0].add_exp_node); }
#line 1292 "parser.tab.cpp"
    break;

  case 61: /* ConstExp: AddExp  */
#line 177 "parser.ypp"
                       { (yyval.const_exp_node) = new ConstExpNode((yyvsp[0].add_exp_node)); }
#line 1298 "parser.tab.cpp"
    break;

  case 62: /* Cond: LOrExp  */
#line 180 "parser.ypp"
                       { (yyval.l_or_exp_node) = (yyvsp[0].l_or_exp_node); }
#line 1304 "parser.tab.cpp"
    break;

  case 63: /* LOrExp: LAndExp  */
#line 183 "parser.ypp"
                        { (yyval.l_or_exp_node) = new LOrExpNode((yyvsp[0].l_and_exp_node)); }
#line 1310 "parser.tab.cpp"
    break;

  case 64: /* LOrExp: LOrExp T_OR LAndExp  */
#line 184 "parser.ypp"
                                      { 
                        LOrExp* l_or_exp = new LOrExp((yyvsp[-2].l_or_exp_node), (yyvsp[0].l_and_exp_node));
                        (yyval.l_or_exp_node) = new LOrExpNode(l_or_exp);
                }
#line 1319 "parser.tab.cpp"
    break;

  case 65: /* LAndExp: EqExp  */
#line 190 "parser.ypp"
                      { (yyval.l_and_exp_node) = new LAndExpNode((yyvsp[0].eq_exp_node)); }
#line 1325 "parser.tab.cpp"
    break;

  case 66: /* LAndExp: LAndExp T_AND EqExp  */
#line 191 "parser.ypp"
                                      { 
                        LAndExp* l_and_exp = new LAndExp((yyvsp[-2].l_and_exp_node), (yyvsp[0].eq_exp_node)); 
                        (yyval.l_and_exp_node) = new LAndExpNode(l_and_exp);
                }
#line 1334 "parser.tab.cpp"
    break;

  case 67: /* EqExp: RelExp  */
#line 197 "parser.ypp"
                       { (yyval.eq_exp_node) = new EqExpNode((yyvsp[0].rel_exp_node));}
#line 1340 "parser.tab.cpp"
    break;

  case 68: /* EqExp: EqExp EqOp RelExp  */
#line 198 "parser.ypp"
                                    { 
                        EqExp* eq_exp = new EqExp((yyvsp[-2].eq_exp_node), *(yyvsp[-1].string), (yyvsp[0].rel_exp_node));
                        delete (yyvsp[-1].string);
                        (yyval.eq_exp_node) = new EqExpNode(eq_exp);
                }
#line 1350 "parser.tab.cpp"
    break;

  case 69: /* RelExp: AddExp  */
#line 205 "parser.ypp"
                       { (yyval.rel_exp_node) = new RelExpNode((yyvsp[0].add_exp_node)); }
#line 1356 "parser.tab.cpp"
    break;

  case 70: /* RelExp: RelExp RelOp AddExp  */
#line 206 "parser.ypp"
                                      { 
                        RelExp* rel_exp = new RelExp((yyvsp[-2].rel_exp_node), *(yyvsp[-1].string), (yyvsp[0].add_exp_node)); 
                        delete (yyvsp[-1].string); 
                        (yyval.rel_exp_node) = new RelExpNode(rel_exp);
                }
#line 1366 "parser.tab.cpp"
    break;

  case 71: /* RelOp: T_LESS  */
#line 213 "parser.ypp"
                       { *(yyval.string) = "<"; }
#line 1372 "parser.tab.cpp"
    break;

  case 72: /* RelOp: T_GREATER  */
#line 214 "parser.ypp"
                            { *(yyval.string) = ">"; }
#line 1378 "parser.tab.cpp"
    break;

  case 73: /* RelOp: T_LE  */
#line 215 "parser.ypp"
                       { *(yyval.string) = "<="; }
#line 1384 "parser.tab.cpp"
    break;

  case 74: /* RelOp: T_GE  */
#line 216 "parser.ypp"
                       { *(yyval.string) = ">="; }
#line 1390 "parser.tab.cpp"
    break;

  case 75: /* EqOp: T_EQ  */
#line 219 "parser.ypp"
                     { *(yyval.string) = "=="; }
#line 1396 "parser.tab.cpp"
    break;

  case 76: /* EqOp: T_NE  */
#line 220 "parser.ypp"
                       { *(yyval.string) = "!="; }
#line 1402 "parser.tab.cpp"
    break;

  case 77: /* AddExp: MulExp  */
#line 223 "parser.ypp"
                       { (yyval.add_exp_node) = new AddExpNode((yyvsp[0].mul_exp_node)); }
#line 1408 "parser.tab.cpp"
    break;

  case 78: /* AddExp: AddExp AddOp MulExp  */
#line 224 "parser.ypp"
                                      {
                        AddExp* add_exp = new AddExp((yyvsp[-2].add_exp_node), (yyvsp[-1].op), (yyvsp[0].mul_exp_node));
                        (yyval.add_exp_node) = new AddExpNode(add_exp);
                }
#line 1417 "parser.tab.cpp"
    break;

  case 79: /* AddOp: T_ADD  */
#line 230 "parser.ypp"
                      { (yyval.op) = '+'; std::cout << "> AddOp `+`" << std::endl; }
#line 1423 "parser.tab.cpp"
    break;

  case 80: /* AddOp: T_MINUS  */
#line 231 "parser.ypp"
                          { (yyval.op) = '-'; }
#line 1429 "parser.tab.cpp"
    break;

  case 81: /* MulExp: UnaryExp  */
#line 234 "parser.ypp"
                         { (yyval.mul_exp_node) = new MulExpNode((yyvsp[0].unary_exp_node)); }
#line 1435 "parser.tab.cpp"
    break;

  case 82: /* MulExp: MulExp MulOp UnaryExp  */
#line 235 "parser.ypp"
                                        { 
                        MulExp* mul_exp = new MulExp((yyvsp[-2].mul_exp_node), (yyvsp[-1].op), (yyvsp[0].unary_exp_node));
                        (yyval.mul_exp_node) = new MulExpNode(mul_exp);
                }
#line 1444 "parser.tab.cpp"
    break;

  case 83: /* MulOp: T_MULT  */
#line 241 "parser.ypp"
                       { (yyval.op) = '*'; }
#line 1450 "parser.tab.cpp"
    break;

  case 84: /* MulOp: T_DIV  */
#line 242 "parser.ypp"
                        { (yyval.op) = '/'; }
#line 1456 "parser.tab.cpp"
    break;

  case 85: /* MulOp: T_MOD  */
#line 243 "parser.ypp"
                        { (yyval.op) = '%'; }
#line 1462 "parser.tab.cpp"
    break;

  case 86: /* UnaryExp: PrimaryExp  */
#line 246 "parser.ypp"
                           { (yyval.unary_exp_node) = new UnaryExpNode((yyvsp[0].primary_exp_node)); }
#line 1468 "parser.tab.cpp"
    break;

  case 87: /* UnaryExp: Ident '(' ')'  */
#line 247 "parser.ypp"
                                {
                        FuncCall *func_call = new FuncCall((yyvsp[-2].ident_node));
                        (yyval.unary_exp_node) = new UnaryExpNode(func_call);
                }
#line 1477 "parser.tab.cpp"
    break;

  case 88: /* UnaryExp: Ident '(' FuncRParams ')'  */
#line 251 "parser.ypp"
                                            {
                        FuncCall *func_call = new FuncCall((yyvsp[-3].ident_node), (yyvsp[-1].func_r_params_node));
                        (yyval.unary_exp_node) = new UnaryExpNode(func_call);
                }
#line 1486 "parser.tab.cpp"
    break;

  case 89: /* UnaryExp: UnaryOp UnaryExp  */
#line 255 "parser.ypp"
                                   {
                        UnaryOpExp* unary_op_exp = new UnaryOpExp((yyvsp[-1].op), (yyvsp[0].unary_exp_node));
                        (yyval.unary_exp_node) = new UnaryExpNode(unary_op_exp);
                }
#line 1495 "parser.tab.cpp"
    break;

  case 90: /* FuncRParams: Exp  */
#line 261 "parser.ypp"
                    { (yyval.func_r_params_node) = new FuncRParamsNode((yyvsp[0].add_exp_node)); }
#line 1501 "parser.tab.cpp"
    break;

  case 91: /* FuncRParams: FuncRParams ',' Exp  */
#line 262 "parser.ypp"
                                      { (yyval.func_r_params_node) = new FuncRParamsNode(*(yyvsp[-2].func_r_params_node), (yyvsp[0].add_exp_node)); delete (yyvsp[-2].func_r_params_node); }
#line 1507 "parser.tab.cpp"
    break;

  case 92: /* UnaryOp: T_ADD  */
#line 265 "parser.ypp"
                      { (yyval.op) = '+'; }
#line 1513 "parser.tab.cpp"
    break;

  case 93: /* UnaryOp: T_MINUS  */
#line 266 "parser.ypp"
                          { (yyval.op) = '-'; }
#line 1519 "parser.tab.cpp"
    break;

  case 94: /* UnaryOp: T_NOT  */
#line 267 "parser.ypp"
                        { (yyval.op) = '!'; }
#line 1525 "parser.tab.cpp"
    break;

  case 95: /* PrimaryExp: '(' Exp ')'  */
#line 270 "parser.ypp"
                            { (yyval.primary_exp_node) = new PrimaryExpNode((yyvsp[-1].add_exp_node)); }
#line 1531 "parser.tab.cpp"
    break;

  case 96: /* PrimaryExp: LVal  */
#line 271 "parser.ypp"
                       { (yyval.primary_exp_node) = new PrimaryExpNode((yyvsp[0].l_val_node)); }
#line 1537 "parser.tab.cpp"
    break;

  case 97: /* PrimaryExp: Number  */
#line 272 "parser.ypp"
                         { (yyval.primary_exp_node) = new PrimaryExpNode((yyvsp[0].int_node)); }
#line 1543 "parser.tab.cpp"
    break;

  case 98: /* LVal: Ident  */
#line 275 "parser.ypp"
                      { (yyval.l_val_node) = new LValNode((yyvsp[0].ident_node)); }
#line 1549 "parser.tab.cpp"
    break;

  case 99: /* LVal: LVal '[' Exp ']'  */
#line 276 "parser.ypp"
                                   { (yyval.l_val_node) = new LValNode(*(yyvsp[-3].l_val_node), (yyvsp[-1].add_exp_node)); delete (yyvsp[-3].l_val_node); }
#line 1555 "parser.tab.cpp"
    break;

  case 100: /* Ident: T_IDENT  */
#line 279 "parser.ypp"
                        { (yyval.ident_node) = new IdentNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1561 "parser.tab.cpp"
    break;

  case 101: /* Number: T_NUMBER  */
#line 282 "parser.ypp"
                         { (yyval.int_node) = new IntNode((yyvsp[0].value)); }
#line 1567 "parser.tab.cpp"
    break;


#line 1571 "parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 285 "parser.ypp"

