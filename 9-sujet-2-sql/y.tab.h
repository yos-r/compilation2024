/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
#line 95 "file.y"

    int intValue;
    float floatValue;
    char *stringValue;

#line 133 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
