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
struct syntax_node *create_node(int node_type, int is_empty);
struct syntax_node *connect_node(int argc, ...);
/* use this to let main function know:
 * whether there is no error
 * or we have done some error recovery and 
 * successfully built a syntax tree
 */
int is_successful = 1;

#line 83 "syntax.tab.c" /* yacc.c:339  */

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
# define YYDEBUG 0
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
#line 22 "syntax.y" /* yacc.c:355  */

    int int_value;
    float float_value;
    char *string_value;
    struct syntax_node *node_value;

#line 163 "syntax.tab.c" /* yacc.c:355  */
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

#line 194 "syntax.tab.c" /* yacc.c:358  */

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
#define YYLAST   358

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  137

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
       0,    58,    58,    65,    68,    74,    79,    84,    89,    95,
      99,   108,   114,   120,   127,   132,   139,   142,   150,   160,
     166,   174,   181,   189,   194,   204,   209,   215,   223,   231,
     234,   240,   245,   249,   255,   276,   283,   288,   296,   301,
     308,   317,   320,   326,   331,   338,   342,   349,   353,   362,
     367,   372,   377,   383,   388,   393,   398,   403,   409,   414,
     419,   424,   432,   437,   445,   451,   456,   463,   469,   475,
     483,   488
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

#define YYPACT_NINF -60

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-60)))

#define YYTABLE_NINF -42

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      75,   -18,   -60,    26,    58,   -60,    75,     4,   -60,   -60,
      23,    43,   -60,   -60,   -60,    54,   -60,    60,    33,    55,
       7,    31,   -60,    88,    38,    39,   -60,    -8,    88,    66,
      39,    72,   -60,    88,    73,    78,   -60,   -60,    79,    81,
      85,    61,   -60,   -60,    51,    93,    94,   -60,   -60,   -60,
      96,   -60,    13,   -60,   -60,   105,   -60,   -60,   102,   170,
     103,   106,   170,   170,   115,   -60,   100,    61,   199,   170,
     -60,    88,   -60,   -60,    99,   214,   131,   147,    -3,    -3,
     112,   229,   -60,   -60,   170,   170,   170,   170,   170,   170,
     126,   -60,   170,   170,   163,   289,   -60,   113,   -60,   244,
     120,   -60,   121,   259,   132,   274,   -60,   -60,    95,    95,
      -3,    -3,   319,   304,   -60,   289,   128,   129,   183,   -60,
     170,   -60,    83,    83,    83,    83,   -60,   -60,   -60,   143,
     148,   -60,   -60,    83,    83,   -60,   -60
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    11,    16,     0,     2,     0,     0,    12,     7,
      18,     0,    15,     1,     4,    19,     6,     0,     9,     0,
       0,     0,     5,     0,     0,     0,     8,     0,     0,     0,
       0,     0,    24,     0,     0,    26,    19,    10,     0,     0,
       0,     0,    44,    14,    47,     0,    45,    13,    42,    23,
      27,    22,     0,    21,    20,     0,    68,    69,    67,     0,
       0,     0,     0,     0,     0,    32,     0,     0,     0,     0,
      43,     0,    25,    34,     0,     0,     0,     0,    59,    60,
       0,     0,    28,    30,     0,     0,     0,     0,     0,     0,
       0,    31,     0,     0,     0,    48,    46,     0,    63,    71,
       0,    33,     0,     0,     0,     0,    58,    57,    53,    54,
      55,    56,    50,    51,    66,    49,    52,     0,     0,    62,
       0,    61,     0,     0,     0,     0,    65,    64,    70,    36,
      35,    40,    39,     0,     0,    38,    37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -60,   -60,   153,   -60,   138,     1,   -60,   -60,   -60,   -22,
     -60,   110,   -60,   144,   111,   224,    30,   -60,    98,   -60,
     -59,    50
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    17,    28,     8,    11,    12,    18,
      19,    34,    35,    65,    66,    67,    29,    30,    45,    46,
      68,   100
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      75,     7,     9,    78,    79,    81,    44,     7,    27,    15,
      95,    50,    42,     2,     3,    99,    90,   103,   105,     2,
       3,    43,    33,    94,    16,   108,   109,   110,   111,   112,
     113,    10,    31,   115,   116,   118,   -41,     2,     3,    38,
      40,    39,   -41,   -41,   -41,     2,     3,   -41,   -41,    44,
     -41,   -17,   -41,    33,    23,    41,    32,   -41,    13,    24,
      48,    99,    55,   -41,    56,    57,    58,   -41,   -41,    59,
      60,    20,    61,    69,    62,    -3,     1,    24,    21,    63,
      22,     2,     3,    25,    55,    64,    56,    57,    58,    25,
     -29,    59,    60,    36,    61,    47,    62,    49,    51,    52,
      97,    63,    56,    57,    58,    42,    53,    64,    54,    86,
      87,    25,    62,    70,    90,    71,    80,    63,    56,    57,
      58,    94,    24,    64,    98,    73,    74,    76,    62,    82,
      77,   114,   102,    63,    56,    57,    58,   106,   119,    64,
      84,    85,    86,    87,    62,   121,   122,    90,   104,    63,
      56,    57,    58,   133,    94,    64,   126,   124,   134,    14,
      62,    37,    72,    26,   117,    63,    56,    57,    58,    96,
     128,    64,     0,    56,    57,    58,    62,     0,    83,     0,
       0,    63,     0,    62,     0,     0,     0,    64,    63,     0,
       0,     0,     0,     0,    64,    84,    85,    86,    87,    88,
      89,     0,    90,     0,     0,    92,    93,     0,     0,    94,
     127,    84,    85,    86,    87,    88,    89,     0,    90,    91,
       0,    92,    93,     0,     0,    94,    84,    85,    86,    87,
      88,    89,     0,    90,   101,     0,    92,    93,     0,     0,
      94,    84,    85,    86,    87,    88,    89,     0,    90,     0,
       0,    92,    93,     0,   107,    94,    84,    85,    86,    87,
      88,    89,     0,    90,     0,   120,    92,    93,     0,     0,
      94,    84,    85,    86,    87,    88,    89,     0,    90,     0,
       0,    92,    93,     0,   123,    94,    84,    85,    86,    87,
      88,    89,     0,    90,     0,     0,    92,    93,     0,   125,
      94,    84,    85,    86,    87,    88,    89,     0,    90,     0,
       0,    92,    93,     0,     0,    94,    84,    85,    86,    87,
      88,     0,     0,    90,     0,     0,     0,    93,     0,     0,
      94,    84,    85,    86,    87,     0,     0,     0,    90,     0,
       0,     0,    93,     0,     0,    94,   129,   130,   131,   132,
       0,     0,     0,     0,     0,     0,     0,   135,   136
};

static const yytype_int16 yycheck[] =
{
      59,     0,    20,    62,    63,    64,    28,     6,     1,     5,
      69,    33,    20,     6,     7,    74,    19,    76,    77,     6,
       7,    29,    21,    26,    20,    84,    85,    86,    87,    88,
      89,     5,     1,    92,    93,    94,    29,     6,     7,     1,
       1,     3,     3,     4,     5,     6,     7,     8,     9,    71,
      11,    28,    13,    52,    21,    25,    25,    18,     0,    26,
      30,   120,     1,    24,     3,     4,     5,    28,    29,     8,
       9,    28,    11,    22,    13,     0,     1,    26,    24,    18,
      20,     6,     7,    28,     1,    24,     3,     4,     5,    28,
      29,     8,     9,     5,    11,    29,    13,    25,    25,    21,
       1,    18,     3,     4,     5,    20,    27,    24,    27,    14,
      15,    28,    13,    20,    19,    21,     1,    18,     3,     4,
       5,    26,    26,    24,    25,    20,    24,    24,    13,    29,
      24,     5,     1,    18,     3,     4,     5,    25,    25,    24,
      12,    13,    14,    15,    13,    25,    25,    19,     1,    18,
       3,     4,     5,    10,    26,    24,    27,    25,    10,     6,
      13,    23,    52,    19,     1,    18,     3,     4,     5,    71,
     120,    24,    -1,     3,     4,     5,    13,    -1,    67,    -1,
      -1,    18,    -1,    13,    -1,    -1,    -1,    24,    18,    -1,
      -1,    -1,    -1,    -1,    24,    12,    13,    14,    15,    16,
      17,    -1,    19,    -1,    -1,    22,    23,    -1,    -1,    26,
      27,    12,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    22,    23,    -1,    -1,    26,    12,    13,    14,    15,
      16,    17,    -1,    19,    20,    -1,    22,    23,    -1,    -1,
      26,    12,    13,    14,    15,    16,    17,    -1,    19,    -1,
      -1,    22,    23,    -1,    25,    26,    12,    13,    14,    15,
      16,    17,    -1,    19,    -1,    21,    22,    23,    -1,    -1,
      26,    12,    13,    14,    15,    16,    17,    -1,    19,    -1,
      -1,    22,    23,    -1,    25,    26,    12,    13,    14,    15,
      16,    17,    -1,    19,    -1,    -1,    22,    23,    -1,    25,
      26,    12,    13,    14,    15,    16,    17,    -1,    19,    -1,
      -1,    22,    23,    -1,    -1,    26,    12,    13,    14,    15,
      16,    -1,    -1,    19,    -1,    -1,    -1,    23,    -1,    -1,
      26,    12,    13,    14,    15,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    23,    -1,    -1,    26,   122,   123,   124,   125,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   133,   134
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,     7,    34,    35,    36,    38,    39,    20,
       5,    40,    41,     0,    35,     5,    20,    37,    42,    43,
      28,    24,    20,    21,    26,    28,    46,     1,    38,    49,
      50,     1,    25,    38,    44,    45,     5,    37,     1,     3,
       1,    49,    20,    29,    42,    51,    52,    29,    49,    25,
      42,    25,    21,    27,    27,     1,     3,     4,     5,     8,
       9,    11,    13,    18,    24,    46,    47,    48,    53,    22,
      20,    21,    44,    20,    24,    53,    24,    24,    53,    53,
       1,    53,    29,    47,    12,    13,    14,    15,    16,    17,
      19,    20,    22,    23,    26,    53,    51,     1,    25,    53,
      54,    20,     1,    53,     1,    53,    25,    25,    53,    53,
      53,    53,    53,    53,     5,    53,    53,     1,    53,    25,
      21,    25,    25,    25,    25,    25,    27,    27,    54,    48,
      48,    48,    48,    10,    10,    48,    48
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    36,    36,    37,
      37,    38,    38,    39,    39,    39,    40,    40,    41,    42,
      42,    42,    43,    43,    43,    44,    44,    45,    46,    47,
      47,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    49,    49,    50,    50,    51,    51,    52,    52,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    54
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     2,     3,     1,
       3,     1,     1,     5,     5,     2,     0,     1,     1,     1,
       4,     4,     4,     4,     3,     3,     1,     2,     4,     0,
       2,     2,     1,     3,     2,     5,     5,     7,     7,     5,
       5,     0,     2,     3,     2,     1,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     4,     4,     3,     4,     4,     3,     1,     1,     1,
       3,     1
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
#line 58 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(Program, 0);
    (yyval.node_value)->child = connect_node(1, (yyvsp[0].node_value));
    root = (yyval.node_value);
}
#line 1504 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 65 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(ExtDefList, 1);
}
#line 1512 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 68 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(ExtDefList, 0);
    (yyval.node_value)->child = connect_node(2, (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1521 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 74 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *semi = create_node(SEMI, 0);
    (yyval.node_value) = create_node(ExtDef, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), semi);
}
#line 1531 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 79 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *semi = create_node(SEMI, 0);
    (yyval.node_value) = create_node(ExtDef, 0);
    (yyval.node_value)->child = connect_node(2, (yyvsp[-1].node_value), semi);
}
#line 1541 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 84 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_node(ExtDef, 1);
}
#line 1551 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 89 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(ExtDef, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1560 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 95 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(ExtDecList, 0);
    (yyval.node_value)->child = connect_node(1, (yyvsp[0].node_value));
}
#line 1569 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 99 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *comma = create_node(COMMA, 0);
    (yyval.node_value) = create_node(ExtDecList, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), comma, (yyvsp[0].node_value));
}
#line 1579 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 108 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *type = create_node(TYPE, 0);
    type->value.string_value = (yyvsp[0].string_value);
    (yyval.node_value) = create_node(Specifier, 0);
    (yyval.node_value)->child = connect_node(1, type);
}
#line 1590 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 114 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(Specifier, 0);
    (yyval.node_value)->child = connect_node(1, (yyvsp[0].node_value));
}
#line 1599 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 120 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *structure = create_node(STRUCT, 0);
    struct syntax_node *lc = create_node(LC, 0);
    struct syntax_node *rc = create_node(RC, 0);
    (yyval.node_value) = create_node(StructSpecifier, 0);
    (yyval.node_value)->child = connect_node(5, structure, (yyvsp[-3].node_value), lc, (yyvsp[-1].node_value), rc);
}
#line 1611 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 127 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_node(StructSpecifier, 1);
}
#line 1621 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 132 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *structure = create_node(STRUCT, 0);
    (yyval.node_value) = create_node(StructSpecifier, 0);
    (yyval.node_value)->child = connect_node(2, structure, (yyvsp[0].node_value));
}
#line 1631 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 139 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(OptTag, 1);
}
#line 1639 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 142 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = (yyvsp[0].string_value);
    (yyval.node_value) = create_node(OptTag, 0);
    (yyval.node_value)->child = connect_node(1, id);
}
#line 1650 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 150 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = (yyvsp[0].string_value);
    (yyval.node_value) = create_node(Tag, 0);
    (yyval.node_value)->child = connect_node(1, id);
}
#line 1661 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 160 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = (yyvsp[0].string_value);
    (yyval.node_value) = create_node(VarDec, 0);
    (yyval.node_value)->child = connect_node(1, id);
}
#line 1672 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 166 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *lb = create_node(LB, 0);
    struct syntax_node *integer = create_node(INT, 0);
    integer->value.int_value = (yyvsp[-1].int_value);
    struct syntax_node *rb = create_node(RB, 0);
    (yyval.node_value) = create_node(VarDec, 0);
    (yyval.node_value)->child = connect_node(4, (yyvsp[-3].node_value), lb, integer, rb);
}
#line 1685 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 174 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_node(VarDec, 1);
}
#line 1695 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 181 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = (yyvsp[-3].string_value);
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    (yyval.node_value) = create_node(FunDec, 0);
    (yyval.node_value)->child = connect_node(4, id, lp, (yyvsp[-1].node_value), rp);
}
#line 1708 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 189 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_node(FunDec, 1);
}
#line 1718 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 194 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = (yyvsp[-2].string_value);
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    (yyval.node_value) = create_node(FunDec, 0);
    (yyval.node_value)->child = connect_node(3, id, lp, rp);
}
#line 1731 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 204 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *comma = create_node(COMMA, 0);
    (yyval.node_value) = create_node(VarList, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), comma, (yyvsp[0].node_value));
}
#line 1741 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 209 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(VarList, 0);
    (yyval.node_value)->child = connect_node(1, (yyvsp[0].node_value));
}
#line 1750 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 215 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(ParamDec, 0);
    (yyval.node_value)->child = connect_node(2, (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1759 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 223 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *lc = create_node(LC, 0);
    struct syntax_node *rc = create_node(RC, 0);
    (yyval.node_value) = create_node(CompSt, 0);
    (yyval.node_value)->child = connect_node(4, lc, (yyvsp[-2].node_value), (yyvsp[-1].node_value), rc);
}
#line 1770 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 231 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(StmtList, 1);
}
#line 1778 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 234 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(StmtList, 0);
    (yyval.node_value)->child = connect_node(2, (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1787 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 240 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *semi = create_node(SEMI, 0);
    (yyval.node_value) = create_node(Stmt, 0);
    (yyval.node_value)->child = connect_node(2, (yyvsp[-1].node_value), semi);
}
#line 1797 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 245 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(Stmt, 0);
    (yyval.node_value)->child = connect_node(1, (yyvsp[0].node_value));
}
#line 1806 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 249 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *return_token = create_node(RETURN, 0);
    struct syntax_node *semi = create_node(SEMI, 0);
    (yyval.node_value) = create_node(Stmt, 0);
    (yyval.node_value)->child = connect_node(3, return_token, (yyvsp[-1].node_value), semi);
}
#line 1817 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 255 "syntax.y" /* yacc.c:1646  */
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
     * or its parent will encounter an segment fault when call connect_node
     */
    (yyval.node_value) = create_node(Stmt, 1);
}
#line 1843 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 276 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *if_token = create_node(IF, 0);
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    (yyval.node_value) = create_node(Stmt, 0);
    (yyval.node_value)->child = connect_node(5, if_token, lp, (yyvsp[-2].node_value), rp, (yyvsp[0].node_value));
}
#line 1855 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 283 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_node(Stmt, 1);
}
#line 1865 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 288 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *if_token = create_node(IF, 0);
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    struct syntax_node *else_token = create_node(ELSE, 0);
    (yyval.node_value) = create_node(Stmt, 0);
    (yyval.node_value)->child = connect_node(7, if_token, lp, (yyvsp[-4].node_value), rp, (yyvsp[-2].node_value), else_token, (yyvsp[0].node_value));
}
#line 1878 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 296 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_node(Stmt, 1);
}
#line 1888 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 301 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *while_token = create_node(WHILE, 0);
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    (yyval.node_value) = create_node(Stmt, 0);
    (yyval.node_value)->child = connect_node(5, while_token, lp, (yyvsp[-2].node_value), rp, (yyvsp[0].node_value));
}
#line 1900 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 308 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_node(Stmt, 1);
}
#line 1910 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 317 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(DefList, 1);
}
#line 1918 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 320 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(DefList, 0);
    (yyval.node_value)->child = connect_node(2, (yyvsp[-1].node_value), (yyvsp[0].node_value));
}
#line 1927 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 326 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *semi = create_node(SEMI, 0);
    (yyval.node_value) = create_node(Def, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), (yyvsp[-1].node_value), semi);
}
#line 1937 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 331 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_node(Def, 1);
}
#line 1947 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 338 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(DecList, 0);
    (yyval.node_value)->child = connect_node(1, (yyvsp[0].node_value));
}
#line 1956 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 342 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *comma = create_node(COMMA, 0);
    (yyval.node_value) = create_node(DecList, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), comma, (yyvsp[0].node_value));
}
#line 1966 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 349 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(Dec, 0);
    (yyval.node_value)->child = connect_node(1, (yyvsp[0].node_value));
}
#line 1975 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 353 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *assignop = create_node(ASSIGNOP, 0);
    (yyval.node_value) = create_node(Dec, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), assignop, (yyvsp[0].node_value));
}
#line 1985 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 362 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *assignop = create_node(ASSIGNOP, 0);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), assignop, (yyvsp[0].node_value));
}
#line 1995 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 367 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *and = create_node(AND, 0);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), and, (yyvsp[0].node_value));
}
#line 2005 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 372 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *or = create_node(OR, 0);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), or, (yyvsp[0].node_value));
}
#line 2015 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 377 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *relop = create_node(RELOP, 0);
    relop->value.string_value = (yyvsp[-1].string_value);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), relop, (yyvsp[0].node_value));
}
#line 2026 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 383 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *plus = create_node(PLUS, 0);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), plus, (yyvsp[0].node_value));
}
#line 2036 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 388 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *minus = create_node(MINUS, 0);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), minus, (yyvsp[0].node_value));
}
#line 2046 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 393 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *star = create_node(STAR, 0);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), star, (yyvsp[0].node_value));
}
#line 2056 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 398 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *div = create_node(DIV, 0);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), div, (yyvsp[0].node_value));
}
#line 2066 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 403 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(3, lp, (yyvsp[-1].node_value), rp);
}
#line 2077 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 409 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_node(Exp, 1);
}
#line 2087 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 414 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *minus = create_node(MINUS, 0);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(2, minus, (yyvsp[0].node_value));
}
#line 2097 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 419 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *not = create_node(NOT, 0);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(2, not, (yyvsp[0].node_value));
}
#line 2107 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 424 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = (yyvsp[-3].string_value);
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(4, id, lp, (yyvsp[-1].node_value), rp);
}
#line 2120 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 432 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_node(Exp, 1);
}
#line 2130 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 437 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = (yyvsp[-2].string_value);
    struct syntax_node *lp = create_node(LP, 0);
    struct syntax_node *rp = create_node(RP, 0);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(3, id, lp, rp);
}
#line 2143 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 445 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *lb = create_node(LB, 0);
    struct syntax_node *rb = create_node(RB, 0);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(4, (yyvsp[-3].node_value), lb, (yyvsp[-1].node_value), rb);
}
#line 2154 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 451 "syntax.y" /* yacc.c:1646  */
    {
    yyerrok;
    is_successful = 0;
    (yyval.node_value) = create_node(Exp, 1);
}
#line 2164 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 456 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *dot = create_node(DOT, 0);
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = (yyvsp[0].string_value);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), dot, id);
}
#line 2176 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 463 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *id = create_node(ID, 0);
    id->value.string_value = (yyvsp[0].string_value);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(1, id);
}
#line 2187 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 469 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *integer = create_node(INT, 0);
    integer->value.int_value = (yyvsp[0].int_value);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(1, integer);
}
#line 2198 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 475 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *float_number = create_node(FLOAT, 0);
    float_number->value.float_value = (yyvsp[0].float_value);
    (yyval.node_value) = create_node(Exp, 0);
    (yyval.node_value)->child = connect_node(1, float_number);
}
#line 2209 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 483 "syntax.y" /* yacc.c:1646  */
    {
    struct syntax_node *comma = create_node(COMMA, 0);
    (yyval.node_value) = create_node(Args, 0);
    (yyval.node_value)->child = connect_node(3, (yyvsp[-2].node_value), comma, (yyvsp[0].node_value));
}
#line 2219 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 488 "syntax.y" /* yacc.c:1646  */
    {
    (yyval.node_value) = create_node(Args, 0);
    (yyval.node_value)->child = connect_node(1, (yyvsp[0].node_value));
}
#line 2228 "syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2232 "syntax.tab.c" /* yacc.c:1646  */
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
#line 493 "syntax.y" /* yacc.c:1906  */


#include "lex.yy.c"

extern char *yytext;

/* do not print to stderr
 * or my testscript won't work
 */
void yyerror(char *s) {
    printf("Error type B at Line %d: %s.\n", 
        yylloc.first_line, s);
}

struct syntax_node *create_node(int node_type, int is_empty) {
    struct syntax_node *ret = Calloc(1, sizeof(struct syntax_node));
    ret->node_type = node_type;
    ret->is_empty = is_empty;
    ret->prev = ret->next = ret->child = NULL;
    return ret;
}

struct syntax_node *connect_node(int argc, ...) {
    struct syntax_node *ret = NULL, *curr = NULL, *next = NULL;
    va_list args;

    va_start(args, argc);           
    for(int i = 0; i < argc; i++ ) {
        next = va_arg(args, struct syntax_node *); 
        /* first one */
        if(!ret) {
            ret = curr = next;
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

void print_syntax_node(struct syntax_node * node) {
    int node_type = node->node_type;
    printf("%s", get_syntax_node_name(node_type));
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
