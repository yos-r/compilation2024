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
// HELP FUNCTIONS: manipulation des tableaux et des chaines
int is_string_in_array(char* strings[],char* str,int num_strings) {
    for (int i = 0; i < num_strings; i++) {
        if (strcmp(strings[i], str) == 0) {
            return 1;
        }
    }
    return 0; 
}
void displayArray(struct KeyValue array[], int size) {
    for (int i = 0; i < size; i++) {
         if (is_string_in_array(tables,array[i].key,num_tables)){

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
int check_field_array(struct KeyValue array[], char *table,char* field,int size){
    for (int i = 0; i < size; i++) {
        if (strcmp(array[i].key, table) == 0) {
            // table trouv'ee, recchercher dans les champs
             for (int j = 0; j < array[i].num_values; j++){
                if (strcmp(array[i].champs[j],field)==0) {
                    return 1;
                }
             }
        }
    }
    printf("Erreur ligne %d: Le champ ' %s '  n'existe pas dans la table %s \n",num_ligne,field,table);
    exit(EXIT_FAILURE); 
    return -1;
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

#line 247 "y.tab.c"

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
    NUMERICTYPE = 273,
    INSERT = 274,
    INTO = 275,
    TABLE = 276,
    INT = 277,
    VARCHAR = 278,
    VALUES = 279,
    NULLL = 280,
    POINTVIRGULE = 281,
    COMMENT = 282,
    UPDATE = 283,
    DELETE = 284,
    SET = 285,
    ALL = 286,
    DROP = 287,
    EGAL = 288,
    DIFF = 289,
    LOGIQUE = 290,
    NOT = 291,
    DESCRIBE = 292
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
#define NUMERICTYPE 273
#define INSERT 274
#define INTO 275
#define TABLE 276
#define INT 277
#define VARCHAR 278
#define VALUES 279
#define NULLL 280
#define POINTVIRGULE 281
#define COMMENT 282
#define UPDATE 283
#define DELETE 284
#define SET 285
#define ALL 286
#define DROP 287
#define EGAL 288
#define DIFF 289
#define LOGIQUE 290
#define NOT 291
#define DESCRIBE 292

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 179 "file.y"

    int intValue;
    float floatValue;
    char *stringValue;

#line 379 "y.tab.c"

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
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   140

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  135

#define YYUNDEFTOK  2
#define YYMAXUTOK   292


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
       2,     2,     2,     2,    38,     2,     2,     2,     2,     2,
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
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   226,   226,   227,   228,   230,   232,   238,   240,   244,
     245,   247,   250,   251,   252,   253,   254,   256,   258,   259,
     261,   267,   268,   270,   270,   271,   272,   273,   273,   275,
     275,   275,   277,   277,   277,   279,   280,   281,   282,   283,
     284,   285,   287,   289,   292,   297,   303,   304,   305,   306,
     307,   308,   310,   311,   312,   314,   314,   314
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRING", "PRIMARY_KEY",
  "FOREIGN_KEY", "REFERENCES", "FIN", "PAROUV", "PARFERM", "SELECT",
  "FROM", "WHERE", "COMP", "NB", "NUMERIC", "CREATE", "NUMERICTYPE",
  "INSERT", "INTO", "TABLE", "INT", "VARCHAR", "VALUES", "NULLL",
  "POINTVIRGULE", "COMMENT", "UPDATE", "DELETE", "SET", "ALL", "DROP",
  "EGAL", "DIFF", "LOGIQUE", "NOT", "DESCRIBE", "','", "$accept", "S",
  "CMD", "choix", "condition", "listecondition", "not", "op", "value",
  "listeinsertion", "listecreation", "type", "listeselect", "contrainte", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,    44
};
# endif

#define YYPACT_NINF (-61)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-56)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      33,    16,    22,    -5,   -61,    25,    17,    30,   -61,    39,
       9,   -61,   -61,   -61,    43,     4,    56,    29,    74,    38,
      57,    83,    85,    53,   -61,   -61,   -61,    86,    87,    88,
      84,    89,    90,    68,    93,    71,    82,   -61,   -61,   -61,
      82,   -61,   -61,    19,    19,    19,    91,    64,    70,     5,
      60,   -61,   -61,    35,    92,    -1,     8,    10,    67,    69,
      69,    69,    63,   -61,    72,    99,   -61,    95,   -61,     2,
       3,   102,   -61,    21,   -61,   -61,   -61,   -61,   -61,    11,
     -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,    60,     0,
      94,    96,    97,   -61,   -61,   -61,    98,    35,   101,   -61,
      65,   103,   -61,   -61,   -61,    69,   104,   -61,   105,   106,
       3,   113,   -61,   -61,   -61,   -61,     0,   -61,   -61,   -61,
     114,   -61,   108,    69,   110,   115,   -61,   117,   118,   116,
     119,   -61,   120,   121,   -61
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     3,     0,     0,     0,     5,     0,
       0,     7,    52,    21,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     4,     2,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    24,    18,    19,    17,
      24,    54,    53,     0,     0,     0,     0,     0,     0,     0,
      28,    20,     6,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    27,    23,     0,    51,     0,    47,     0,
       0,     0,    10,     0,     9,     8,    39,    40,    38,     0,
      33,    32,    34,    14,    13,    15,    16,    12,    28,     0,
       0,     0,     0,    57,    56,    42,     0,     0,     0,    11,
       0,     0,    31,    29,    30,     0,     0,    50,     0,     0,
       0,     0,    41,    36,    37,    35,     0,    26,    48,    46,
       0,    43,     0,     0,     0,     0,    25,     0,     0,     0,
       0,    45,     0,     0,    44
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -61,   -61,   -61,   -61,   100,   -61,    36,    13,   -60,   -61,
      31,    28,   -61,    20
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     9,    10,    14,    51,    64,    65,   105,    83,    79,
      55,    70,    15,    95
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,    85,    87,    91,    93,    28,    61,   -49,    94,    72,
      25,    92,   -49,   -55,   102,    18,   -22,    11,    74,    12,
      75,    99,    53,    16,    97,    54,    19,    98,    20,    21,
      31,    22,    32,   103,   104,    26,    66,    73,    62,    24,
     -49,   -55,    29,    17,     1,   117,    73,    13,    73,   100,
       2,    23,     3,    67,    38,    27,    39,    68,    69,    30,
       4,     5,     6,   126,    86,     7,   112,    80,    34,   113,
       8,    76,    48,    80,    49,    56,    57,    33,    81,    82,
     114,   115,    77,    78,    81,    82,    36,    35,    37,    40,
      41,    42,    46,    43,    47,    50,    63,    59,    44,    45,
      58,    71,    89,    60,    90,    96,   116,    88,   109,   106,
     111,   107,   108,   120,   118,   119,   122,   124,   125,   127,
     129,   130,   128,   133,   101,   110,   131,     0,   132,   123,
     121,   134,     0,     0,     0,     0,     0,     0,     0,     0,
      52
};

static const yytype_int8 yycheck[] =
{
      60,    61,    62,     1,     1,     1,     1,     5,     5,    10,
       1,     9,    10,    10,    14,    20,    12,     1,    10,     3,
      10,    10,     3,     1,     3,     6,     1,     6,     3,    12,
       1,     1,     3,    33,    34,    26,     1,    38,    33,     0,
      38,    38,    38,    21,    11,   105,    38,    31,    38,    38,
      17,    21,    19,    18,     1,    12,     3,    22,    23,     3,
      27,    28,    29,   123,     1,    32,     1,     4,    30,     4,
      37,     4,     1,     4,     3,    44,    45,     3,    15,    16,
      15,    16,    15,    16,    15,    16,     3,    30,     3,     3,
       3,     3,    24,     9,     1,    13,    36,    33,     9,     9,
       9,     9,     3,    33,     9,     3,     3,    35,    10,    15,
       9,    15,    15,     7,    10,    10,     3,     3,    10,     9,
       3,     3,     7,     3,    88,    97,    10,    -1,     9,   116,
     110,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      40
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    11,    17,    19,    27,    28,    29,    32,    37,    40,
      41,     1,     3,    31,    42,    51,     1,    21,    20,     1,
       3,    12,     1,    21,     0,     1,    26,    12,     1,    38,
       3,     1,     3,     3,    30,    30,     3,     3,     1,     3,
       3,     3,     3,     9,     9,     9,    24,     1,     1,     3,
      13,    43,    43,     3,     6,    49,    49,    49,     9,    33,
      33,     1,    33,    36,    44,    45,     1,    18,    22,    23,
      50,     9,    10,    38,    10,    10,     4,    15,    16,    48,
       4,    15,    16,    47,    47,    47,     1,    47,    35,     3,
       9,     1,     9,     1,     5,    52,     3,     3,     6,    10,
      38,    45,    14,    33,    34,    46,    15,    15,    15,    10,
      50,     9,     1,     4,    15,    16,     3,    47,    10,    10,
       7,    52,     3,    46,     3,    10,    47,     9,     7,     3,
       3,    10,     9,     3,    10
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    40,    40,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    42,    42,    43,    43,    44,    44,    45,    45,    46,
      46,    46,    47,    47,    47,    48,    48,    48,    48,    48,
      48,    48,    49,    49,    49,    49,    50,    50,    50,    50,
      50,    50,    51,    51,    51,    52,    52,    52
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     2,     1,     5,     2,     6,     6,
       6,     7,     6,     6,     6,     6,     6,     3,     3,     3,
       4,     1,     1,     2,     0,     6,     4,     1,     0,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     1,
       1,     3,     3,     5,    11,     9,     4,     1,     4,     1,
       3,     1,     1,     3,     3,     0,     1,     1
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
#line 227 "file.y"
          {printf("Ligne %d : Commentaire \n ",num_ligne);}
#line 1638 "y.tab.c"
    break;

  case 4:
#line 228 "file.y"
            { printf("Erreur Ligne %d : point virgule manquant \n",num_ligne); exit(EXIT_FAILURE);}
#line 1644 "y.tab.c"
    break;

  case 5:
#line 230 "file.y"
         {printf("Ligne %d : Description de la base de donnees \n",num_ligne); displayArray(tablesChamps,cle);}
#line 1650 "y.tab.c"
    break;

  case 6:
#line 232 "file.y"
                               {if (is_string_in_array(tables,(yyvsp[-1].stringValue),num_tables)) {
    int key=findKey(tablesChamps,(yyvsp[-1].stringValue),cle);
        int result = are_all_values_in_types((yyvsp[-1].stringValue),tablesChamps[key].champs, tablesChamps[key].num_values, strings,num_strings);
        if ((yyvsp[-3].intValue)==0){printf("Ligne %d : %d Champs selectionnes \n ",num_ligne,tablesChamps[key].num_values);}
 printf("Ligne %d : Sélection réussie depuis la table %s \n",num_ligne,(yyvsp[-1].stringValue));} 
        else { printf("Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,(yyvsp[-1].stringValue)); exit(EXIT_FAILURE); };}
#line 1661 "y.tab.c"
    break;

  case 7:
#line 238 "file.y"
               { printf("Erreur ligne %d: Identifiant manquant ou mal formé \n",num_ligne); exit(EXIT_FAILURE); }
#line 1667 "y.tab.c"
    break;

  case 8:
#line 240 "file.y"
                                                {add_string(tables,(yyvsp[-3].stringValue),num_tables,1); printf(" Ligne %d: Colonnes de la table %s = %d \n",num_ligne,(yyvsp[-3].stringValue),colonnes);num_tables++;
printf("Ligne %d : Création de la table %s réussie \n",num_ligne,(yyvsp[-3].stringValue));
strcpy(tablesChamps[cle].key, (yyvsp[-3].stringValue));tablesChamps[cle].num_values=num_strings;cle++;
}
#line 1676 "y.tab.c"
    break;

  case 9:
#line 244 "file.y"
                                                  {printf("Erreur Ligne %d : Identifiant manquant \n",num_ligne); exit(EXIT_FAILURE);}
#line 1682 "y.tab.c"
    break;

  case 10:
#line 245 "file.y"
                                               {printf("Erreur Ligne %d : mot-cle TABLE oublié \n",num_ligne); exit(EXIT_FAILURE);}
#line 1688 "y.tab.c"
    break;

  case 11:
#line 247 "file.y"
                                                      {if (is_string_in_array(tables,(yyvsp[-4].stringValue),num_tables)) {int clef= findKey(tablesChamps,(yyvsp[-4].stringValue),cle); /* chercher la cle*/if (num_champs==tablesChamps[clef].num_values) printf("Ligne %d : Insertion réussie dans la table %s \n",num_ligne,(yyvsp[-4].stringValue)); else {printf("Erreur Ligne %d : La table %s possede %d colonnes, vous avez fourni %d ",num_ligne,(yyvsp[-4].stringValue),tablesChamps[clef].num_values,num_champs); exit(EXIT_FAILURE);};} 
        else { printf(" Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,(yyvsp[-4].stringValue)); exit(EXIT_FAILURE); };}
#line 1695 "y.tab.c"
    break;

  case 12:
#line 250 "file.y"
                              {if (is_string_in_array(tables,(yyvsp[-4].stringValue),num_tables)) {int a= check_field_array(tablesChamps,(yyvsp[-4].stringValue),(yyvsp[-2].stringValue),cle);printf("Ligne %d : Mise à jour de la table %s réussie \n",num_ligne,(yyvsp[-4].stringValue));} else {printf("Erreur Ligne %d : La table %s n'existe pas ",num_ligne,(yyvsp[-4].stringValue)); exit(EXIT_FAILURE);}}
#line 1701 "y.tab.c"
    break;

  case 13:
#line 251 "file.y"
                                  {printf("Erreur Ligne %d : Identifiant manquant ou mal formé ",num_ligne); exit(EXIT_FAILURE);}
#line 1707 "y.tab.c"
    break;

  case 14:
#line 252 "file.y"
                                     {printf("Erreur Ligne %d : Identifiant manquant ou mal formé ",num_ligne); exit(EXIT_FAILURE);}
#line 1713 "y.tab.c"
    break;

  case 15:
#line 253 "file.y"
                                {printf("Erreur Ligne %d : Opérateur incorrect, la mise à jour est effectuée avec = ",num_ligne); exit(EXIT_FAILURE);}
#line 1719 "y.tab.c"
    break;

  case 16:
#line 254 "file.y"
                              {printf("Erreur Ligne %d : ",num_ligne); exit(EXIT_FAILURE);}
#line 1725 "y.tab.c"
    break;

  case 17:
#line 256 "file.y"
                {if (is_string_in_array(tables,(yyvsp[0].stringValue),num_tables)) { delete_string(tables,(yyvsp[0].stringValue),num_tables); num_tables--;printf("Ligne %d : Suppression de la table %s réussie\n",num_ligne,(yyvsp[0].stringValue));} 
        else { printf(" Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,(yyvsp[0].stringValue)); exit(EXIT_FAILURE); };}
#line 1732 "y.tab.c"
    break;

  case 18:
#line 258 "file.y"
                {printf("Erreur Ligne %d : mot-cle TABLE oublié \n",num_ligne); exit(EXIT_FAILURE);}
#line 1738 "y.tab.c"
    break;

  case 19:
#line 259 "file.y"
                   {printf("Erreur Ligne %d : Identifiant manquant ou mal formé ",num_ligne); exit(EXIT_FAILURE);}
#line 1744 "y.tab.c"
    break;

  case 20:
#line 261 "file.y"
                           {if (is_string_in_array(tables,(yyvsp[-1].stringValue),num_tables)) {
    int key=findKey(tablesChamps,(yyvsp[-1].stringValue),cle);
        int result = are_all_values_in_types((yyvsp[-1].stringValue),tablesChamps[key].champs, tablesChamps[key].num_values, strings,num_strings);
     if ((yyvsp[0].intValue)==1) {printf("Ligne %d : La table %s est vidée \n",num_ligne,(yyvsp[-1].stringValue));}; printf("Ligne %d : Suppression de lignes réussie depuis la table %s \n",num_ligne,(yyvsp[-1].stringValue));} 
        else { printf(" Erreur ligne %d: Pas de table %s dans la base de données \n",num_ligne,(yyvsp[-1].stringValue)); exit(EXIT_FAILURE); };}
#line 1754 "y.tab.c"
    break;

  case 21:
#line 267 "file.y"
           {(yyval.intValue)=0; }
#line 1760 "y.tab.c"
    break;

  case 22:
#line 268 "file.y"
              {(yyval.intValue)=1;printf(" Ligne %d: Champs selectionnes = %d \n",num_ligne,champs);}
#line 1766 "y.tab.c"
    break;

  case 23:
#line 270 "file.y"
                                 {(yyval.intValue)=0; if (predicat>1) printf("Ligne %d: %d prédicats dans la clause \n",num_ligne,predicat);}
#line 1772 "y.tab.c"
    break;

  case 24:
#line 270 "file.y"
                                                                                                                                   {(yyval.intValue)=1;}
#line 1778 "y.tab.c"
    break;

  case 25:
#line 271 "file.y"
                                                       {predicat++;add_string2(strings, (yyvsp[-2].stringValue), num_strings); num_strings++;}
#line 1784 "y.tab.c"
    break;

  case 26:
#line 272 "file.y"
                  {predicat++; add_string2(strings, (yyvsp[-2].stringValue), num_strings); num_strings++;}
#line 1790 "y.tab.c"
    break;

  case 35:
#line 279 "file.y"
                                            {num_champs++;}
#line 1796 "y.tab.c"
    break;

  case 36:
#line 280 "file.y"
                            {num_champs++;}
#line 1802 "y.tab.c"
    break;

  case 37:
#line 281 "file.y"
                        {num_champs++;}
#line 1808 "y.tab.c"
    break;

  case 38:
#line 282 "file.y"
          {num_champs++;}
#line 1814 "y.tab.c"
    break;

  case 39:
#line 283 "file.y"
         {num_champs++;}
#line 1820 "y.tab.c"
    break;

  case 40:
#line 284 "file.y"
     {num_champs++;}
#line 1826 "y.tab.c"
    break;

  case 41:
#line 285 "file.y"
                           { printf("Erreur ligne %d: Erreur d'insertion \n",num_ligne); exit(EXIT_FAILURE); }
#line 1832 "y.tab.c"
    break;

  case 42:
#line 287 "file.y"
                                   {colonnes+=1;add_string(strings, (yyvsp[-2].stringValue), num_strings,0);strcpy(tablesChamps[cle].champs[num_strings], (yyvsp[-2].stringValue));num_strings++;
add_string2(types, (yyvsp[-1].stringValue), num_types);strcpy(tablesChamps[cle].types[num_types], (yyvsp[-1].stringValue));num_types++; }
#line 1839 "y.tab.c"
    break;

  case 43:
#line 289 "file.y"
                                       {colonnes+=1;add_string(strings, (yyvsp[-2].stringValue), num_strings,0);strcpy(tablesChamps[cle].champs[num_strings], (yyvsp[-2].stringValue));num_strings++;
add_string2(types, (yyvsp[-1].stringValue), num_types);strcpy(tablesChamps[cle].types[num_types], (yyvsp[-1].stringValue));num_types++;
}
#line 1847 "y.tab.c"
    break;

  case 44:
#line 292 "file.y"
                                                                                   {if (!is_string_in_array(tables,(yyvsp[-3].stringValue),num_tables)) {printf("Erreur Ligne %d : table %s n'existe pas \n",num_ligne,(yyvsp[-3].stringValue)); exit(EXIT_FAILURE);} else { 
int i= check_field_array(tablesChamps,(yyvsp[-3].stringValue),(yyvsp[-1].stringValue),cle);
colonnes+=1;
add_string(strings, (yyvsp[-6].stringValue), num_strings,0);strcpy(tablesChamps[cle].champs[num_strings], (yyvsp[-6].stringValue)); num_strings++; 
add_string2(types, "FOREIGN", num_types);strcpy(tablesChamps[cle].types[num_types], "FOREIGN");num_types++; }}
#line 1857 "y.tab.c"
    break;

  case 45:
#line 297 "file.y"
                                                                {if (!is_string_in_array(tables,(yyvsp[-3].stringValue),num_tables)) {printf("Erreur Ligne %d : table %s n'existe pas \n",num_ligne,(yyvsp[-3].stringValue)); exit(EXIT_FAILURE);};
colonnes+=1;
int i= check_field_array(tablesChamps,(yyvsp[-3].stringValue),(yyvsp[-1].stringValue),cle);
add_string(strings, (yyvsp[-6].stringValue), num_strings,0);num_strings++; 
add_string(types, "FOREIGN", num_types,2);num_types++;}
#line 1867 "y.tab.c"
    break;

  case 46:
#line 303 "file.y"
                                {if ((yyvsp[-1].intValue)>65535 ) {printf("Erreur ligne %d : taille de la chaine excède 65,535 ",num_ligne);exit(EXIT_FAILURE);} else {(yyval.stringValue)="VARCHAR";}}
#line 1873 "y.tab.c"
    break;

  case 47:
#line 304 "file.y"
      {(yyval.stringValue)="INT";}
#line 1879 "y.tab.c"
    break;

  case 48:
#line 305 "file.y"
                                 {(yyval.stringValue)="NUMERIC";}
#line 1885 "y.tab.c"
    break;

  case 49:
#line 306 "file.y"
           {printf("Erreur ligne %d : taille de la chaine non spécifiée ",num_ligne);exit(EXIT_FAILURE);}
#line 1891 "y.tab.c"
    break;

  case 50:
#line 307 "file.y"
                    {printf("Erreur ligne %d : parenthèse ouvrante oubliée ",num_ligne);exit(EXIT_FAILURE);}
#line 1897 "y.tab.c"
    break;

  case 51:
#line 308 "file.y"
        {printf("Erreur ligne %d : Type non reconnu \n ",num_ligne);}
#line 1903 "y.tab.c"
    break;

  case 52:
#line 310 "file.y"
                 {champs+=1; add_string(strings, (yyvsp[0].stringValue), num_strings,0); num_strings++;}
#line 1909 "y.tab.c"
    break;

  case 53:
#line 311 "file.y"
                   {champs+=1;add_string(strings, (yyvsp[0].stringValue), num_strings,0);num_strings++;}
#line 1915 "y.tab.c"
    break;

  case 54:
#line 312 "file.y"
                       { printf("Erreur ligne %d: Virgule manquante \n",num_ligne); exit(EXIT_FAILURE); }
#line 1921 "y.tab.c"
    break;

  case 57:
#line 314 "file.y"
                                     {printf("Erreur ligne %d : contrainte non valide ",num_ligne);exit(EXIT_FAILURE);}
#line 1927 "y.tab.c"
    break;


#line 1931 "y.tab.c"

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
#line 315 "file.y"


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

return 0;}
