/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "syntax.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "syntax.tab.h"
#include "syntax.h"
struct syntax_node *root;
struct syntax_node *create_nonterminal_node(int node_type, int argc, ...);
/* use this to let main function know:
 * whether there is no error
 * or we have done some error recovery and 
 * successfully built a syntax tree
 */
int is_successful = 1;

#line 82 "syntax.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    ID = 260,
    TYPE = 261,
    STRUCT = 262,
    RETURN = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    PLUS = 267,
    MINUS = 268,
    STAR = 269,
    DIV = 270,
    AND = 271,
    OR = 272,
    NOT = 273,
    DOT = 274,
    SEMI = 275,
    COMMA = 276,
    ASSIGNOP = 277,
    RELOP = 278,
    LP = 279,
    RP = 280,
    LB = 281,
    RB = 282,
    LC = 283,
    RC = 284,
    NONTREMINAL = 285,
    UNARY_MINUS = 286,
    LOWER_THAN_ELSE = 287
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 21 "syntax.y" /* yacc.c:355  */

    int int_value;
    float float_value;
    char *string_value;
    struct syntax_node *node_value;

#line 162 "syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 193 "syntax.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   383

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    57,    57,    63,    66,    71,    74,    77,    82,    86,
      92,    95,   102,   105,   110,   113,   118,   123,   126,   131,
     138,   141,   144,   151,   154,   159,   164,   167,   172,   179,
     182,   189,   192,   197,   200,   203,   206,   227,   230,   235,
     238,   243,   246,   255,   258,   263,   266,   273,   276,   281,
     284,   291,   294,   297,   300,   303,   306,   309,   312,   315,
     318,   323,   326,   329,   332,   337,   340,   343,   348,   351,
     354,   357,   362,   365
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "TYPE", "STRUCT",
  "RETURN", "IF", "ELSE", "WHILE", "PLUS", "MINUS", "STAR", "DIV", "AND",
  "OR", "NOT", "DOT", "SEMI", "COMMA", "ASSIGNOP", "RELOP", "LP", "RP",
  "LB", "RB", "LC", "RC", "NONTREMINAL", "UNARY_MINUS", "LOWER_THAN_ELSE",
  "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287
};
# endif

#define YYPACT_NINF -63

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-63)))

#define YYTABLE_NINF -44

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      78,   -18,   -63,    14,    37,   -63,    78,     4,   -63,   -63,
      19,    22,   -63,   -63,   -63,    42,   -63,    54,    55,     3,
      51,     7,   -63,    81,    59,   -63,    35,   -63,    -8,    81,
      69,    64,    58,   -63,    81,    75,    84,   -63,   -63,    79,
      80,    25,    86,   -63,   -63,    -6,    88,    97,   -63,   100,
     -63,   -63,    98,   -63,    96,   -63,   -63,   -63,   102,   -63,
     -63,    99,   195,   106,   107,   195,   195,   140,   -63,   104,
      86,   224,   195,   -63,    81,   -63,   -63,   124,   239,   156,
     172,    30,    30,   113,   254,   -63,   -63,   195,   195,   195,
     195,   195,   195,   135,   -63,   195,   195,   188,   314,   -63,
     122,   -63,   269,   125,   -63,   126,   284,   127,   299,   -63,
     -63,   120,   120,    30,    30,   344,   329,   -63,   314,   153,
     128,   208,   -63,   195,   -63,   108,   108,   108,   108,   -63,
     -63,   -63,   144,   146,   -63,   -63,   108,   108,   -63,   -63
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    12,    17,     0,     2,     0,     0,    13,     7,
      19,     0,    16,     1,     4,    20,     6,     0,    10,     0,
       0,     0,     5,     0,     0,     9,     0,     8,     0,     0,
       0,     0,     0,    25,     0,     0,    27,    20,    11,     0,
       0,     0,     0,    46,    15,    49,     0,    47,    14,     0,
      44,    24,    28,    23,     0,    22,    21,    30,     0,    70,
      71,    69,     0,     0,     0,     0,     0,     0,    34,     0,
       0,     0,     0,    45,     0,    26,    36,     0,     0,     0,
       0,    61,    62,     0,     0,    29,    32,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,    50,    48,
       0,    65,    73,     0,    35,     0,     0,     0,     0,    60,
      59,    55,    56,    57,    58,    52,    53,    68,    51,    54,
       0,     0,    64,     0,    63,     0,     0,     0,     0,    67,
      66,    72,    38,    37,    42,    41,     0,     0,    40,    39
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -63,   -63,   157,   -63,   139,     1,   -63,   -63,   -63,   -23,
     -63,   116,   -63,   152,   111,   246,    70,   -63,   109,   -63,
     -62,    61
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    17,    29,     8,    11,    12,    18,
      19,    35,    36,    68,    69,    70,    30,    31,    46,    47,
      71,   103
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      78,     7,     9,    81,    82,    84,    45,     7,    32,    15,
      98,    52,    43,     2,     3,   102,    72,   106,   108,    10,
      24,    44,    34,    25,    16,   111,   112,   113,   114,   115,
     116,    26,    33,   118,   119,   121,    41,    13,   -43,   -43,
     -43,     2,     3,   -43,   -43,    43,   -43,   -18,   -43,    93,
      20,    45,    28,   -43,    57,    34,    97,     2,     3,   -43,
      39,   102,    40,   -43,   -43,    49,    21,   -43,   -43,   -43,
       2,     3,   -43,   -43,    22,   -43,    23,   -43,    -3,     1,
     -43,    24,   -43,    51,     2,     3,    37,    58,   -43,    59,
      60,    61,   -43,   -43,    62,    63,    42,    64,    48,    65,
      53,    50,     2,     3,    66,    54,    55,    56,    73,    58,
      67,    59,    60,    61,    26,   -31,    62,    63,    74,    64,
      43,    65,    76,    77,    24,   100,    66,    59,    60,    61,
      79,    80,    67,    85,    89,    90,    26,    65,   109,    93,
     117,    83,    66,    59,    60,    61,    97,   122,    67,   101,
     124,   125,   127,    65,   136,   129,   137,   105,    66,    59,
      60,    61,    38,    14,    67,    87,    88,    89,    90,    65,
      75,    27,    93,   107,    66,    59,    60,    61,     0,    97,
      67,    86,     0,    99,   131,    65,     0,     0,     0,   120,
      66,    59,    60,    61,     0,     0,    67,     0,    59,    60,
      61,    65,     0,     0,     0,     0,    66,     0,    65,     0,
       0,     0,    67,    66,     0,     0,     0,     0,     0,    67,
      87,    88,    89,    90,    91,    92,     0,    93,     0,     0,
      95,    96,     0,     0,    97,   130,    87,    88,    89,    90,
      91,    92,     0,    93,    94,     0,    95,    96,     0,     0,
      97,    87,    88,    89,    90,    91,    92,     0,    93,   104,
       0,    95,    96,     0,     0,    97,    87,    88,    89,    90,
      91,    92,     0,    93,     0,     0,    95,    96,     0,   110,
      97,    87,    88,    89,    90,    91,    92,     0,    93,     0,
     123,    95,    96,     0,     0,    97,    87,    88,    89,    90,
      91,    92,     0,    93,     0,     0,    95,    96,     0,   126,
      97,    87,    88,    89,    90,    91,    92,     0,    93,     0,
       0,    95,    96,     0,   128,    97,    87,    88,    89,    90,
      91,    92,     0,    93,     0,     0,    95,    96,     0,     0,
      97,    87,    88,    89,    90,    91,     0,     0,    93,     0,
       0,     0,    96,     0,     0,    97,    87,    88,    89,    90,
       0,     0,     0,    93,     0,     0,     0,    96,     0,     0,
      97,   132,   133,   134,   135,     0,     0,     0,     0,     0,
       0,     0,   138,   139
};

static const yytype_int16 yycheck[] =
{
      62,     0,    20,    65,    66,    67,    29,     6,     1,     5,
      72,    34,    20,     6,     7,    77,    22,    79,    80,     5,
      26,    29,    21,    20,    20,    87,    88,    89,    90,    91,
      92,    28,    25,    95,    96,    97,     1,     0,     3,     4,
       5,     6,     7,     8,     9,    20,    11,    28,    13,    19,
      28,    74,     1,    18,    29,    54,    26,     6,     7,    24,
       1,   123,     3,    28,    29,     1,    24,     3,     4,     5,
       6,     7,     8,     9,    20,    11,    21,    13,     0,     1,
      29,    26,    18,    25,     6,     7,     5,     1,    24,     3,
       4,     5,    28,    29,     8,     9,    26,    11,    29,    13,
      25,    31,     6,     7,    18,    21,    27,    27,    20,     1,
      24,     3,     4,     5,    28,    29,     8,     9,    21,    11,
      20,    13,    20,    24,    26,     1,    18,     3,     4,     5,
      24,    24,    24,    29,    14,    15,    28,    13,    25,    19,
       5,     1,    18,     3,     4,     5,    26,    25,    24,    25,
      25,    25,    25,    13,    10,    27,    10,     1,    18,     3,
       4,     5,    23,     6,    24,    12,    13,    14,    15,    13,
      54,    19,    19,     1,    18,     3,     4,     5,    -1,    26,
      24,    70,    -1,    74,   123,    13,    -1,    -1,    -1,     1,
      18,     3,     4,     5,    -1,    -1,    24,    -1,     3,     4,
       5,    13,    -1,    -1,    -1,    -1,    18,    -1,    13,    -1,
      -1,    -1,    24,    18,    -1,    -1,    -1,    -1,    -1,    24,
      12,    13,    14,    15,    16,    17,    -1,    19,    -1,    -1,
      22,    23,    -1,    -1,    26,    27,    12,    13,    14,    15,
      16,    17,    -1,    19,    20,    -1,    22,    23,    -1,    -1,
      26,    12,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    22,    23,    -1,    -1,    26,    12,    13,    14,    15,
      16,    17,    -1,    19,    -1,    -1,    22,    23,    -1,    25,
      26,    12,    13,    14,    15,    16,    17,    -1,    19,    -1,
      21,    22,    23,    -1,    -1,    26,    12,    13,    14,    15,
      16,    17,    -1,    19,    -1,    -1,    22,    23,    -1,    25,
      26,    12,    13,    14,    15,    16,    17,    -1,    19,    -1,
      -1,    22,    23,    -1,    25,    26,    12,    13,    14,    15,
      16,    17,    -1,    19,    -1,    -1,    22,    23,    -1,    -1,
      26,    12,    13,    14,    15,    16,    -1,    -1,    19,    -1,
      -1,    -1,    23,    -1,    -1,    26,    12,    13,    14,    15,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    23,    -1,    -1,
      26,   125,   126,   127,   128,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   136,   137
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,     7,    34,    35,    36,    38,    39,    20,
       5,    40,    41,     0,    35,     5,    20,    37,    42,    43,
      28,    24,    20,    21,    26,    20,    28,    46,     1,    38,
      49,    50,     1,    25,    38,    44,    45,     5,    37,     1,
       3,     1,    49,    20,    29,    42,    51,    52,    29,     1,
      49,    25,    42,    25,    21,    27,    27,    29,     1,     3,
       4,     5,     8,     9,    11,    13,    18,    24,    46,    47,
      48,    53,    22,    20,    21,    44,    20,    24,    53,    24,
      24,    53,    53,     1,    53,    29,    47,    12,    13,    14,
      15,    16,    17,    19,    20,    22,    23,    26,    53,    51,
       1,    25,    53,    54,    20,     1,    53,     1,    53,    25,
      25,    53,    53,    53,    53,    53,    53,     5,    53,    53,
       1,    53,    25,    21,    25,    25,    25,    25,    25,    27,
      27,    54,    48,    48,    48,    48,    10,    10,    48,    48
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    36,    36,    36,
      37,    37,    38,    38,    39,    39,    39,    40,    40,    41,
      42,    42,    42,    43,    43,    43,    44,    44,    45,    46,
      46,    47,    47,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    54,    54
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     2,     3,     3,
       1,     3,     1,     1,     5,     5,     2,     0,     1,     1,
       1,     4,     4,     4,     4,     3,     3,     1,     2,     4,
       3,     0,     2,     2,     1,     3,     2,     5,     5,     7,
       7,     5,     5,     0,     2,     3,     2,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     4,     3,     4,     4,     3,     1,
       1,     1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 57 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Program, 1, (yyvsp[0].node_value));
    root = (yyval.node_value);
}
#line 1508 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 63 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(ExtDefList, 0);
}
#line 1516 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 66 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(ExtDefList, 2, (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1524 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 71 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(ExtDef, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1532 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 74 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(ExtDef, 2, (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1540 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 77 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_nonterminal_node(ExtDef, 0);
}
#line 1550 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 82 "syntax.y" /* yacc.c:1646  */
    {
    // function definition
    (yyval.node_value) = create_nonterminal_node(ExtDef, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1559 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 86 "syntax.y" /* yacc.c:1646  */
    {
    // function declaration
    (yyval.node_value) = create_nonterminal_node(ExtDef, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1568 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 92 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(ExtDecList, 1, (yyvsp[0].node_value));
}
#line 1576 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 95 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(ExtDecList, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1584 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 102 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Specifier, 1, (yyvsp[0].node_value));
}
#line 1592 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 105 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Specifier, 1, (yyvsp[0].node_value));
}
#line 1600 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 110 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(StructSpecifier, 5, (yyvsp[-4].node_value), (yyvsp[-3].node_value), (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1608 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 113 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_nonterminal_node(StructSpecifier, 0);
}
#line 1618 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 118 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(StructSpecifier, 2, (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1626 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 123 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(OptTag, 0);
}
#line 1634 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 126 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(OptTag, 1, (yyvsp[0].node_value));
}
#line 1642 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 131 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Tag, 1, (yyvsp[0].node_value));
}
#line 1650 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 138 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(VarDec, 1, (yyvsp[0].node_value));
}
#line 1658 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 141 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(VarDec, 4, (yyvsp[-3].node_value), (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1666 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 144 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_nonterminal_node(VarDec, 0);
}
#line 1676 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 151 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(FunDec, 4, (yyvsp[-3].node_value), (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1684 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 154 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_nonterminal_node(FunDec, 0);
}
#line 1694 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 159 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(FunDec, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1702 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 164 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(VarList, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1710 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 167 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(VarList, 1, (yyvsp[0].node_value));
}
#line 1718 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 172 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(ParamDec, 2, (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1726 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 179 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(CompSt, 4, (yyvsp[-3].node_value), (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1734 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 182 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_nonterminal_node(CompSt, 0);
}
#line 1744 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 189 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(StmtList, 0);
}
#line 1752 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 192 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(StmtList, 2, (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1760 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 197 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Stmt, 2, (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1768 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 200 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Stmt, 1, (yyvsp[0].node_value));
}
#line 1776 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 203 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Stmt, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1784 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 206 "syntax.y" /* yacc.c:1646  */
    {
    /* according to this bison manual page
     * link : https://www.gnu.org/software/bison/manual/html_node/Error-Recovery.html#Error-Recovery
     * To prevent an outpouring of error messages, 
     * the parser will output no error message for another syntax 
     * error that happens shortly after the first; 
     * only after three consecutive input tokens have been successfully 
     * shifted will error messages resume. 
     *
     * But our compiler lab requires that for every syntax error line
     * we should output an syntax error message
     * So we use yyerrok to let bison return to its normal mode
     * so that consecutive errors will not be supressed
     */
    yyerrok;
    is_successful = 0;
    /* remember to create an empty production rule node for it
     * or its parent will encounter an segment fault when call create_nonterminal_node
     */
    (yyval.node_value) = create_nonterminal_node(Stmt, 0);
}
#line 1810 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 227 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Stmt, 5, (yyvsp[-4].node_value), (yyvsp[-3].node_value), (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1818 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 230 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_nonterminal_node(Stmt, 0);
}
#line 1828 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 235 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Stmt, 7, (yyvsp[-6].node_value), (yyvsp[-5].node_value), (yyvsp[-4].node_value), (yyvsp[-3].node_value), (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1836 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 238 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_nonterminal_node(Stmt, 0);
}
#line 1846 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 243 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Stmt, 5, (yyvsp[-4].node_value), (yyvsp[-3].node_value), (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1854 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 246 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_nonterminal_node(Stmt, 0);
}
#line 1864 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 255 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(DefList, 0);
}
#line 1872 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 258 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(DefList, 2, (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1880 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 263 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Def, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1888 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 266 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_nonterminal_node(Def, 0);
}
#line 1898 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 273 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(DecList, 1, (yyvsp[0].node_value));
}
#line 1906 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 276 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(DecList, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1914 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 281 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Dec, 1, (yyvsp[0].node_value));
}
#line 1922 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 284 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Dec, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1930 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 291 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1938 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 294 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1946 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 297 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1954 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 300 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1962 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 303 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1970 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 306 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1978 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 309 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1986 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 312 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1994 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 315 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 2002 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 318 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_nonterminal_node(Exp, 0);
}
#line 2012 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 323 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 2, (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 2020 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 326 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 2, (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 2028 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 329 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 4, (yyvsp[-3].node_value), (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 2036 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 332 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_nonterminal_node(Exp, 0);
}
#line 2046 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 337 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 2054 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 340 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 4, (yyvsp[-3].node_value), (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 2062 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 343 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_nonterminal_node(Exp, 0);
}
#line 2072 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 348 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 2080 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 351 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 1, (yyvsp[0].node_value));
}
#line 2088 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 354 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 1, (yyvsp[0].node_value));
}
#line 2096 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 357 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Exp, 1, (yyvsp[0].node_value));
}
#line 2104 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 362 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Args, 3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 2112 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 365 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_nonterminal_node(Args, 1, (yyvsp[0].node_value));
}
#line 2120 "syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2124 "syntax.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 369 "syntax.y" /* yacc.c:1906  */


#include "lex.yy.c"

extern char *yytext;

/* do not print to stderr
 * or my testscript won't work
 */
void yyerror(char *s) {
    printf("Error type B at Line %d: %s.\n", 
        yylloc.first_line, s);
}

struct syntax_node *create_nonterminal_node(int node_type, int argc, ...) {
    struct syntax_node *head = NULL, *curr = NULL, *next = NULL;
    va_list args;

    va_start(args, argc);          
    for(int i = 0; i < argc; i++ ) {
        next = va_arg(args, struct syntax_node *); 
        /* first one */
        if(!head) {
            head = curr = next;
            curr->prev = NULL;
        }
        else {
            curr->next = next;
            next->prev = curr;
            curr = next;
        }
        curr->next = NULL;
    }
    va_end(args);

    struct syntax_node *ret = Calloc(1, sizeof(struct syntax_node));
    ret->node_type = node_type;
    ret->prev = ret->next = NULL;
    ret->child = head;
    ret->is_empty = 1;
    if(argc > 0) {
        ret->is_empty = 0;
        ret->line_no = head->line_no;
    }
    return ret;
}

/* be careful of the order here */
char *syntax_node_name_table[] = {
    "INT", "FLOAT", "ID", "TYPE",
    "STRUCT", "RETURN", "IF", "ELSE", "WHILE",
    "PLUS", "MINUS", "STAR", "DIV",
    "AND", "OR", "NOT",
    "DOT", "SEMI", "COMMA", "ASSIGNOP", "RELOP",
    "LP", "RP", "LB", "RB", "LC", "RC",
    "Program", "ExtDefList", "ExtDef", "Specifier", "ExtDecList",
    "FunDec", "CompSt", "VarDec", "StructSpecifier", "Tag", "OptTag", "VarList",
    "ParamDec", "StmtList", "Stmt", "Exp", "DefList", "Def", "Dec", "DecList", "Args"
};

char *get_syntax_node_name(int node_type) {
    assert(node_type >= INT && node_type <= Args);
    return syntax_node_name_table[node_type - INT];
}

int is_terminal(int node_type) {
    return node_type >= INT && node_type <= RC;
}

void print_syntax_node(struct syntax_node * node) {
    int node_type = node->node_type;
    printf("%s", get_syntax_node_name(node_type));
    if(!is_terminal(node_type))
        printf(" (%d)", node->line_no);
    if(node_type == ID || node_type == TYPE)
        printf(": %s", node->value.string_value);
    if(node_type == INT)
        printf(": %d", node->value.int_value);
    if(node_type == FLOAT)
        printf(": %f", node->value.float_value);
}

void delete_syntax_node(struct syntax_node * node) {
    int node_type = node->node_type;
    if(node_type == ID || node_type == TYPE 
        || node_type == RELOP)
        Free(node->value.string_value);
    Free(node);
}

void print_syntax_tree(struct syntax_node *root, int indent_level) {
    /* we do not print invalid node and empty production rule node */
    if(!root || root->is_empty)
        return;
    /* each indentation level == 2 space */
    for(int i = 0; i < indent_level; i++)
        printf("  ");
    print_syntax_node(root);
    printf("\n");
    struct syntax_node *p = root->child;
    while(p) {
        print_syntax_tree(p, indent_level + 1);
        p = p->next;
    }
}

void delete_syntax_tree(struct syntax_node *root) {
    struct syntax_node *p = root->child;
    delete_syntax_node(root);
    while(p) {
        delete_syntax_node(p);
        p = p->next;
    }
}
