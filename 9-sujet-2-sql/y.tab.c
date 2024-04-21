/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "file.y"

#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int yylex(void); 
int yyerror(char*s); 

int champs=0;
int colonnes=0;
int predicat=0;
#define MAX_STRINGS 100 
#define MAX_LENGTH 50  
#define MAX_KEYS 10    


char* strings[MAX_STRINGS];
char* types[MAX_STRINGS];

char* tables[MAX_LENGTH]; //table des tables
int num_strings = 0;
int num_types=0;
int num_champs=0;
int num_tables=0;
int num_ligne=1;
// enregistrement cle valeur pour stocker les tables et les nombs de champs
struct KeyValue {
    char key[100]; // Assuming maximum length of the key is 100 characters
    char champs[MAX_LENGTH][100]; // Assuming maximum length of each value is 100 characters
    char types[MAX_LENGTH][100];
    int num_values; // Number of values in the array
};
int cle=0; //nombre de clés/ enregistrements dans tablesChamps
struct KeyValue tablesChamps[MAX_KEYS];
// affichage du tableau des enregistrements
void displayArray(struct KeyValue array[], int size) {
    for (int i = 0; i < size; i++) {
        // printf("Struct %d:\n", i + 1);
        printf("Table: %s\n", array[i].key);
        printf("    Champs:\n");
        for (int j = 0; j < array[i].num_values; j++) {
            printf("        %s\n", array[i].champs[j]);
        }
        printf("    Types:\n");
        for (int j = 0; j < array[i].num_values; j++) {
            printf("        %s\n", array[i].types[j]);
        }
        printf("\n");
    }
}
// HELP FUNCTIONS: manipulation des tableaux et des chaines
int is_string_in_array(char* strings[],char* str,int num_strings) {
    for (int i = 0; i < num_strings; i++) {
        if (strcmp(strings[i], str) == 0) {
            return 1;
        }
    }
    return 0; 
}
int are_all_values_in_types(char* table, char types[][100], int types_size, char* strings[], int num_strings) {
    for (int i = 0; i < num_strings; i++) {
        int found = 0;
        for (int j = 0; j < types_size; j++) {
            if (strcmp(strings[i], types[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Erreur ligne %d: Le champ ' %s '  n'existe pas dans la table %s \n",num_ligne,strings[i],table);
            exit(EXIT_FAILURE);
            return 0; // Not all values found in types array
        }
    }
    return 1; // All values found in types array
}
void display_champs(struct KeyValue kv) {
    printf("value array for key '%s':\n", kv.key);
    for (int i = 0; i < kv.num_values; i++) {
        printf("%s\t", kv.champs[i]);
    }
}
void add_string(char* strings[], char* str,int num_strings,int choix ) {
    if (num_strings < MAX_STRINGS) {
        if (!is_string_in_array(strings,str,num_strings)) {
            strings[num_strings] = strdup(str);

        } else {
            switch (choix){
                  case 0: printf("Erreur: ligne %d : le champ '%s' est dupliqué \n", num_ligne,str); break;
                  case 1: printf("Erreur: ligne %d : la table '%s' existe déja \n", num_ligne,str);break;
                   }
            if (choix!=2) exit(EXIT_FAILURE); 
        }
    } else {
        printf("Erreur '%s'.\n", str);
    }
}
void add_string2(char* strings[], char* str,int num_strings ) {
    if (num_strings < MAX_STRINGS) {
        strings[num_strings] = strdup(str);}
}
void delete_string(char* strings[], char* str, int num_strings) {
    int i, j;
    for (i = 0; i < num_strings; i++) {
        if (strcmp(strings[i], str) == 0) {
            // Found the string to delete
            // Shift all elements after the deleted element one position to the left
            for (j = i; j < (num_strings - 1); j++) {
                strings[j] = strings[j + 1];
            }
            return; 
        }
    }
    // String not found
    printf("String '%s' not found in the array.\n", str);
}
int findKey(struct KeyValue array[], char *searchKey,int size){
    for (int i = 0; i < size; i++) {
        if (strcmp(array[i].key, searchKey) == 0) {
            return i; 
        }
    }
    return -1;
}
void display_strings(char* strings[], int num_strings) {
    printf("Strings in the array:\n");
    for (int i = 0; i < num_strings; i++) {
        printf("%s\n", strings[i]);
    }
}
void empty_array(char* strings[] ,int numstrings) {
    for (int i = 0; i < num_strings; i++) {
        free(strings[i]);
        strings[i] = NULL; // Optional: Set pointers to NULL for safety
    }
    num_strings = 0; 
}
int countLines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1; 
    }

    int lines = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);
    return lines;
}

#line 228 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    ID = 258,
    STRING = 259,
    PRIMARY_KEY = 260,
    FOREIGN_KEY = 261,
    REFERENCES = 262,
    FIN = 263,
    PAROUV = 264,
    PARFERM = 265,
    SELECT = 266,
    FROM = 267,
    WHERE = 268,
    COMP = 269,
    NB = 270,
    NUMERIC = 271,
    CREATE = 272,
    INSERT = 273,
    INTO = 274,
    TABLE = 275,
    INT = 276,
    VARCHAR = 277,
    VALUES = 278,
    NULLL = 279,
    POINTVIRGULE = 280,
    COMMENT = 281,
    UPDATE = 282,
    DELETE = 283,
    SET = 284,
    ALL = 285,
    DROP = 286,
    EGAL = 287,
    DIFF = 288,
    LOGIQUE = 289,
    NOT = 290
  };
#endif
/* Tokens.  */
#define ID 258
#define STRING 259
#define PRIMARY_KEY 260
#define FOREIGN_KEY 261
#define REFERENCES 262
#define FIN 263
#define PAROUV 264
#define PARFERM 265
#define SELECT 266
#define FROM 267
#define WHERE 268
#define COMP 269
#define NB 270
#define NUMERIC 271
#define CREATE 272
#define INSERT 273
#define INTO 274
#define TABLE 275
#define INT 276
#define VARCHAR 277
#define VALUES 278
#define NULLL 279
#define POINTVIRGULE 280
#define COMMENT 281
#define UPDATE 282
#define DELETE 283
#define SET 284
#define ALL 285
#define DROP 286
#define EGAL 287
#define DIFF 288
#define LOGIQUE 289
#define NOT 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 160 "file.y"

    int intValue;
    float floatValue;
    char *stringValue;

#line 356 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   139

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  56
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

#define YYUNDEFTOK  2
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    36,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   204,   204,   205,   206,   209,   214,   216,   220,   221,
     223,   226,   227,   228,   229,   230,   232,   234,   235,   237,
     240,   241,   243,   243,   244,   245,   246,   246,   248,   248,
     248,   250,   250,   250,   252,   253,   254,   255,   256,   257,
     258,   260,   262,   265,   268,   271,   272,   273,   274,   275,
     276,   278,   279,   280,   282,   282,   282
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRING", "PRIMARY_KEY",
  "FOREIGN_KEY", "REFERENCES", "FIN", "PAROUV", "PARFERM", "SELECT",
  "FROM", "WHERE", "COMP", "NB", "NUMERIC", "CREATE", "INSERT", "INTO",
  "TABLE", "INT", "VARCHAR", "VALUES", "NULLL", "POINTVIRGULE", "COMMENT",
  "UPDATE", "DELETE", "SET", "ALL", "DROP", "EGAL", "DIFF", "LOGIQUE",
  "NOT", "','", "$accept", "S", "CMD", "choix", "condition",
  "listecondition", "not", "op", "value", "listeinsertion",
  "listecreation", "type", "listeselect", "contrainte", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,    44
};
# endif

#define YYPACT_NINF (-60)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-55)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      39,    14,    21,    -5,   -60,    24,    12,    33,    54,    17,
     -60,   -60,   -60,    43,     4,    56,    59,    66,    45,    52,
      83,    84,    76,   -60,   -60,   -60,    85,    86,    87,    82,
      88,    89,    69,    92,    77,    81,   -60,   -60,   -60,    81,
     -60,   -60,    20,    20,    20,    90,    63,    64,     5,    65,
     -60,   -60,    27,    93,    -1,     0,    10,    15,    60,    60,
      60,    57,   -60,    70,    98,   -60,    94,   -60,     2,     3,
     102,   -60,    26,   -60,   -60,   -60,   -60,   -60,    11,   -60,
     -60,   -60,   -60,   -60,   -60,   -60,   -60,    65,    19,    91,
      95,    96,   -60,   -60,   -60,    97,    27,    99,   -60,    67,
     106,   -60,   -60,   -60,    60,    78,   -60,   103,   105,     3,
     112,   -60,   -60,   -60,   -60,    19,   -60,   101,   -60,   114,
     -60,   108,    60,   109,   111,   115,   -60,   -60,   118,   120,
     116,   119,   -60,   121,   117,   -60
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     3,     0,     0,     0,     0,     0,
       6,    51,    20,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     4,     2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    23,    17,    18,    16,    23,
      53,    52,     0,     0,     0,     0,     0,     0,     0,    27,
      19,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    26,    22,     0,    50,     0,    46,     0,     0,
       0,     9,     0,     8,     7,    38,    39,    37,     0,    32,
      31,    33,    13,    12,    14,    15,    11,    27,     0,     0,
       0,     0,    56,    55,    41,     0,     0,     0,    10,     0,
       0,    30,    28,    29,     0,     0,    48,     0,     0,     0,
       0,    40,    35,    36,    34,     0,    25,     0,    45,     0,
      42,     0,     0,     0,     0,     0,    24,    49,     0,     0,
       0,     0,    44,     0,     0,    43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -60,   -60,   -60,   -60,   100,   -60,    38,    16,   -59,   -60,
      41,    34,   -60,    23
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     8,     9,    13,    50,    63,    64,   104,    82,    78,
      54,    69,    14,    94
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      83,    84,    86,    90,    92,    27,    60,   -47,    93,    71,
      73,    91,   -47,   -54,    17,    10,   -21,    11,    24,    75,
      74,    98,    15,    52,    20,    18,    53,    19,    65,    96,
      76,    77,    97,   101,    21,    72,    72,    61,   -47,   -54,
      28,    16,    25,    66,    12,   116,    72,    99,    67,    68,
       1,   102,   103,    22,    23,    26,     2,     3,    85,    29,
      30,    79,    31,   126,    79,     4,     5,     6,   111,    32,
       7,   112,    80,    81,    33,    80,    81,    37,    47,    38,
      48,    34,   113,   114,    55,    56,    35,    36,    39,    40,
      41,    42,    45,    46,    49,    58,    59,    43,    44,    57,
      62,    88,    70,    89,    87,    95,   105,   108,   110,   115,
     106,   107,   119,   118,   117,   121,   123,   124,   125,   127,
     128,   130,   129,   131,   134,   100,   132,   135,   133,     0,
     109,   122,   120,     0,     0,     0,     0,     0,     0,    51
};

static const yytype_int8 yycheck[] =
{
      59,    60,    61,     1,     1,     1,     1,     5,     5,    10,
      10,     9,    10,    10,    19,     1,    12,     3,     1,     4,
      10,    10,     1,     3,    12,     1,     6,     3,     1,     3,
      15,    16,     6,    14,     1,    36,    36,    32,    36,    36,
      36,    20,    25,    16,    30,   104,    36,    36,    21,    22,
      11,    32,    33,    20,     0,    12,    17,    18,     1,     3,
       1,     4,     3,   122,     4,    26,    27,    28,     1,     3,
      31,     4,    15,    16,    29,    15,    16,     1,     1,     3,
       3,    29,    15,    16,    43,    44,     3,     3,     3,     3,
       3,     9,    23,     1,    13,    32,    32,     9,     9,     9,
      35,     3,     9,     9,    34,     3,    15,    10,     9,     3,
      15,    15,     7,    10,    36,     3,    15,     3,    10,    10,
       9,     3,     7,     3,     3,    87,    10,    10,     9,    -1,
      96,   115,   109,    -1,    -1,    -1,    -1,    -1,    -1,    39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    11,    17,    18,    26,    27,    28,    31,    38,    39,
       1,     3,    30,    40,    49,     1,    20,    19,     1,     3,
      12,     1,    20,     0,     1,    25,    12,     1,    36,     3,
       1,     3,     3,    29,    29,     3,     3,     1,     3,     3,
       3,     3,     9,     9,     9,    23,     1,     1,     3,    13,
      41,    41,     3,     6,    47,    47,    47,     9,    32,    32,
       1,    32,    35,    42,    43,     1,    16,    21,    22,    48,
       9,    10,    36,    10,    10,     4,    15,    16,    46,     4,
      15,    16,    45,    45,    45,     1,    45,    34,     3,     9,
       1,     9,     1,     5,    50,     3,     3,     6,    10,    36,
      43,    14,    32,    33,    44,    15,    15,    15,    10,    48,
       9,     1,     4,    15,    16,     3,    45,    36,    10,     7,
      50,     3,    44,    15,     3,    10,    45,    10,     9,     7,
       3,     3,    10,     9,     3,    10
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    38,    38,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39,    39,    39,    39,    39,    39,
      40,    40,    41,    41,    42,    42,    43,    43,    44,    44,
      44,    45,    45,    45,    46,    46,    46,    46,    46,    46,
      46,    47,    47,    47,    47,    48,    48,    48,    48,    48,
      48,    49,    49,    49,    50,    50,    50
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     2,     5,     2,     6,     6,     6,
       7,     6,     6,     6,     6,     6,     3,     3,     3,     4,
       1,     1,     2,     0,     6,     4,     1,     0,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     1,     1,     1,
       3,     3,     5,    11,     9,     4,     1,     1,     3,     6,
       1,     1,     3,     3,     0,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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
  case 3:
#line 205 "file.y"
          {printf("Ligne %d : Commentaire \n ",num_ligne);}
#line 1613 "y.tab.c"
    break;

  case 4:
#line 206 "file.y"
            { printf("Erreur Ligne %d : point virgule manquant \n",num_ligne); exit(EXIT_FAILURE);}
#line 1619 "y.tab.c"
    break;

  case 5:
#line 209 "file.y"
                               {if (is_string_in_array(tables,(yyvsp[-1].stringValue),num_tables)) {
    int key=findKey(tablesChamps,(yyvsp[-1].stringValue),cle);
        int result = are_all_values_in_types((yyvsp[-1].stringValue),tablesChamps[key].champs, tablesChamps[key].num_values, strings,num_strings);
 printf("Ligne %d : Sélection réussie depuis la table %s \n",num_ligne,(yyvsp[-1].stringValue));} 
        else { printf("Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,(yyvsp[-1].stringValue)); exit(EXIT_FAILURE); };}
#line 1629 "y.tab.c"
    break;

  case 6:
#line 214 "file.y"
               { printf("Erreur ligne %d: Identifiant manquant ou mal formé \n",num_ligne); exit(EXIT_FAILURE); }
#line 1635 "y.tab.c"
    break;

  case 7:
#line 216 "file.y"
                                                {add_string(tables,(yyvsp[-3].stringValue),num_tables,1); printf(" Ligne %d: Colonnes de la table %s = %d \n",num_ligne,(yyvsp[-3].stringValue),colonnes);num_tables++;
printf("Ligne %d : Création de la table %s réussie \n",num_ligne,(yyvsp[-3].stringValue));
strcpy(tablesChamps[cle].key, (yyvsp[-3].stringValue));tablesChamps[cle].num_values=num_strings;cle++;
}
#line 1644 "y.tab.c"
    break;

  case 8:
#line 220 "file.y"
                                                  {printf("Erreur Ligne %d : Identifiant manquant \n",num_ligne); exit(EXIT_FAILURE);}
#line 1650 "y.tab.c"
    break;

  case 9:
#line 221 "file.y"
                                               {printf("Erreur Ligne %d : mot-cle TABLE oublié \n",num_ligne); exit(EXIT_FAILURE);}
#line 1656 "y.tab.c"
    break;

  case 10:
#line 223 "file.y"
                                                      {if (is_string_in_array(tables,(yyvsp[-4].stringValue),num_tables)) {int clef= findKey(tablesChamps,(yyvsp[-4].stringValue),cle); /* chercher la cle*/if (num_champs==tablesChamps[clef].num_values) printf("Ligne %d : Insertion réussie dans la table %s \n",num_ligne,(yyvsp[-4].stringValue)); else {printf("Erreur Ligne %d : La table %s possede %d colonnes, vous avez fourni %d ",num_ligne,(yyvsp[-4].stringValue),tablesChamps[clef].num_values,num_champs); exit(EXIT_FAILURE);};} 
        else { printf(" Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,(yyvsp[-4].stringValue)); exit(EXIT_FAILURE); };}
#line 1663 "y.tab.c"
    break;

  case 11:
#line 226 "file.y"
                              {if (is_string_in_array(tables,(yyvsp[-4].stringValue),num_tables)) {printf("Ligne %d : Mise à jour de la table %s réussie \n",num_ligne,(yyvsp[-4].stringValue));} else {printf("Erreur Ligne %d : La table %s n'existe pas ",num_ligne,(yyvsp[-4].stringValue)); exit(EXIT_FAILURE);}}
#line 1669 "y.tab.c"
    break;

  case 12:
#line 227 "file.y"
                                  {printf("Erreur Ligne %d : Identifiant manquant ou mal formé ",num_ligne); exit(EXIT_FAILURE);}
#line 1675 "y.tab.c"
    break;

  case 13:
#line 228 "file.y"
                                     {printf("Erreur Ligne %d : Identifiant manquant ou mal formé ",num_ligne); exit(EXIT_FAILURE);}
#line 1681 "y.tab.c"
    break;

  case 14:
#line 229 "file.y"
                                {printf("Erreur Ligne %d : Opérateur incorrect, la mise à jour est effectuée avec = ",num_ligne); exit(EXIT_FAILURE);}
#line 1687 "y.tab.c"
    break;

  case 15:
#line 230 "file.y"
                              {printf("Erreur Ligne %d : ",num_ligne); exit(EXIT_FAILURE);}
#line 1693 "y.tab.c"
    break;

  case 16:
#line 232 "file.y"
                {if (is_string_in_array(tables,(yyvsp[0].stringValue),num_tables)) { delete_string(tables,(yyvsp[0].stringValue),num_tables); num_tables--;printf("Ligne %d : Suppression de la table %s réussie\n",num_ligne,(yyvsp[0].stringValue));} 
        else { printf(" Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,(yyvsp[0].stringValue)); exit(EXIT_FAILURE); };}
#line 1700 "y.tab.c"
    break;

  case 17:
#line 234 "file.y"
                {printf("Erreur Ligne %d : mot-cle TABLE oublié \n",num_ligne); exit(EXIT_FAILURE);}
#line 1706 "y.tab.c"
    break;

  case 18:
#line 235 "file.y"
                   {printf("Erreur Ligne %d : Identifiant manquant ou mal formé ",num_ligne); exit(EXIT_FAILURE);}
#line 1712 "y.tab.c"
    break;

  case 19:
#line 237 "file.y"
                           {if (is_string_in_array(tables,(yyvsp[-1].stringValue),num_tables)) { if ((yyvsp[0].intValue)==1) {printf("Ligne %d : La table %s est vidée \n",num_ligne,(yyvsp[-1].stringValue));}; printf("Ligne %d : Suppression de lignes réussie depuis la table %s \n",num_ligne,(yyvsp[-1].stringValue));} 
        else { printf(" Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,(yyvsp[-1].stringValue)); exit(EXIT_FAILURE); };}
#line 1719 "y.tab.c"
    break;

  case 20:
#line 240 "file.y"
           {printf(" Ligne %d: Tous les champs selectionnes\n",num_ligne);}
#line 1725 "y.tab.c"
    break;

  case 21:
#line 241 "file.y"
              {printf(" Ligne %d: Champs selectionnes = %d \n",num_ligne,champs);}
#line 1731 "y.tab.c"
    break;

  case 22:
#line 243 "file.y"
                                 {(yyval.intValue)=0; if (predicat>1) printf("Ligne %d: %d prédicats dans la clause \n",num_ligne,predicat);}
#line 1737 "y.tab.c"
    break;

  case 23:
#line 243 "file.y"
                                                                                                                                   {(yyval.intValue)=1;}
#line 1743 "y.tab.c"
    break;

  case 24:
#line 244 "file.y"
                                                       {predicat++;}
#line 1749 "y.tab.c"
    break;

  case 25:
#line 245 "file.y"
                  {predicat++;}
#line 1755 "y.tab.c"
    break;

  case 34:
#line 252 "file.y"
                                            {num_champs++;}
#line 1761 "y.tab.c"
    break;

  case 35:
#line 253 "file.y"
                            {num_champs++;}
#line 1767 "y.tab.c"
    break;

  case 36:
#line 254 "file.y"
                        {num_champs++;}
#line 1773 "y.tab.c"
    break;

  case 37:
#line 255 "file.y"
          {num_champs++;}
#line 1779 "y.tab.c"
    break;

  case 38:
#line 256 "file.y"
         {num_champs++;}
#line 1785 "y.tab.c"
    break;

  case 39:
#line 257 "file.y"
     {num_champs++;}
#line 1791 "y.tab.c"
    break;

  case 40:
#line 258 "file.y"
                           { printf("Erreur ligne %d: Erreur d'insertion \n",num_ligne); exit(EXIT_FAILURE); }
#line 1797 "y.tab.c"
    break;

  case 41:
#line 260 "file.y"
                                   {colonnes+=1;add_string(strings, (yyvsp[-2].stringValue), num_strings,0);strcpy(tablesChamps[cle].champs[num_strings], (yyvsp[-2].stringValue));num_strings++;
add_string2(types, (yyvsp[-1].stringValue), num_types);strcpy(tablesChamps[cle].types[num_types], (yyvsp[-1].stringValue));num_types++; }
#line 1804 "y.tab.c"
    break;

  case 42:
#line 262 "file.y"
                                       {printf("type: %s",(yyvsp[-1].stringValue));colonnes+=1;add_string(strings, (yyvsp[-2].stringValue), num_strings,0);strcpy(tablesChamps[cle].champs[num_strings], (yyvsp[-2].stringValue));num_strings++;
add_string2(types, (yyvsp[-1].stringValue), num_types);strcpy(tablesChamps[cle].types[num_types], (yyvsp[-1].stringValue));num_types++;
}
#line 1812 "y.tab.c"
    break;

  case 43:
#line 265 "file.y"
                                                                                   {if (!is_string_in_array(tables,(yyvsp[-3].stringValue),num_tables)) {printf("Erreur Ligne %d : table %s n'existe pas \n",num_ligne,(yyvsp[-3].stringValue)); exit(EXIT_FAILURE);} else { colonnes+=1;
add_string(strings, (yyvsp[-6].stringValue), num_strings,0);strcpy(tablesChamps[cle].champs[num_strings], (yyvsp[-6].stringValue)); num_strings++; 
add_string2(types, "FOREIGN", num_types);strcpy(tablesChamps[cle].types[num_types], "FOREIGN");num_types++; }}
#line 1820 "y.tab.c"
    break;

  case 44:
#line 268 "file.y"
                                                                {colonnes+=1;add_string(strings, (yyvsp[-6].stringValue), num_strings,0);num_strings++; 
add_string(types, "FOREIGN", num_types,2);num_types++;}
#line 1827 "y.tab.c"
    break;

  case 45:
#line 271 "file.y"
                                {if ((yyvsp[-1].intValue)>65535 ) {printf("Erreur ligne %d : taille de la chaine excède 65,535 ",num_ligne);exit(EXIT_FAILURE);} else {(yyval.stringValue)="VARCHAR";}}
#line 1833 "y.tab.c"
    break;

  case 46:
#line 272 "file.y"
      {(yyval.stringValue)="INT";}
#line 1839 "y.tab.c"
    break;

  case 47:
#line 273 "file.y"
           {printf("Erreur ligne %d : taille de la chaine non spécifiée ",num_ligne);exit(EXIT_FAILURE);}
#line 1845 "y.tab.c"
    break;

  case 48:
#line 274 "file.y"
                    {printf("Erreur ligne %d : parenthèse ouvrante oubliée ",num_ligne);exit(EXIT_FAILURE);}
#line 1851 "y.tab.c"
    break;

  case 49:
#line 275 "file.y"
                                   {(yyval.stringValue)="NUMERIC";}
#line 1857 "y.tab.c"
    break;

  case 50:
#line 276 "file.y"
        {printf("Erreur ligne %d : Type non reconnu \n ",num_ligne);}
#line 1863 "y.tab.c"
    break;

  case 51:
#line 278 "file.y"
                 {champs+=1; add_string(strings, (yyvsp[0].stringValue), num_strings,0); num_strings++;}
#line 1869 "y.tab.c"
    break;

  case 52:
#line 279 "file.y"
                   {champs+=1;add_string(strings, (yyvsp[0].stringValue), num_strings,0);num_strings++;}
#line 1875 "y.tab.c"
    break;

  case 53:
#line 280 "file.y"
                       { printf("Erreur ligne %d: Virgule manquante \n",num_ligne); exit(EXIT_FAILURE); }
#line 1881 "y.tab.c"
    break;

  case 56:
#line 282 "file.y"
                                     {printf("Erreur ligne %d : contrainte non valide ",num_ligne);exit(EXIT_FAILURE);}
#line 1887 "y.tab.c"
    break;


#line 1891 "y.tab.c"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
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
#line 283 "file.y"


#include "lex.yy.c" 
int yyerror(char *s){printf("erreur: %s \n",s);return 0;}
int main(int argc, char *argv[]){
    ++argv; --argc;
if ( argc > 0 ) yyin = fopen( argv[0], "r" );
else yyin = stdin;
int lines=countLines("input.txt");
for(int i=0;i<lines;i++) {
    yyparse();
    // réinitialisation des variables à chaque nouvelle commande
     champs=0; //detecteur du numero de champs selectionnes
     colonnes=0; // detecteur du numéro de champ a creer
     empty_array(strings,num_strings); //vider le tableau de detection des champs dupliqués
      empty_array(types,num_types);//vider le tableau de types des champs de la table
     num_strings=0;
     num_ligne++; //incrémentation du nombre de lignes
     predicat=0; // compteur des predicats
     num_types=0;
     num_champs=0;
     };
    
    /* display_strings(tables, num_tables);
    add_string(tables,"fsadf",1,0);
    delete_string(tables,"asd",2);  */
    display_strings(tables, num_tables);


// tableau d'enregistrement
    /* struct KeyValue myArray[MAX_KEYS];
     strcpy(myArray[0].key, "example_key_1");
    strcpy(myArray[0].champs[0], "value1_1");
    strcpy(myArray[0].champs[1], "value1_2");
    myArray[0].num_values = 2;

    // Set values for the second struct in the array
    strcpy(myArray[1].key, "example_key_2");
    strcpy(myArray[1].champs[0], "value2_1");
    myArray[1].num_values = 1; */
    displayArray(tablesChamps,cle);
return 0;}
