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
    FIN = 261,
    PAROUV = 262,
    PARFERM = 263,
    SELECT = 264,
    FROM = 265,
    WHERE = 266,
    COMP = 267,
    NB = 268,
    NUMERIC = 269,
    CREATE = 270,
    INSERT = 271,
    INTO = 272,
    TABLE = 273,
    TYPE = 274,
    VALUES = 275,
    NULLL = 276,
    POINTVIRGULE = 277,
    COMMENT = 278,
    UPDATE = 279,
    DELETE = 280
  };
#endif
/* Tokens.  */
#define ID 258
#define STRING 259
#define PRIMARY_KEY 260
#define FIN 261
#define PAROUV 262
#define PARFERM 263
#define SELECT 264
#define FROM 265
#define WHERE 266
#define COMP 267
#define NB 268
#define NUMERIC 269
#define CREATE 270
#define INSERT 271
#define INTO 272
#define TABLE 273
#define TYPE 274
#define VALUES 275
#define NULLL 276
#define POINTVIRGULE 277
#define COMMENT 278
#define UPDATE 279
#define DELETE 280

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 74 "file.y"

    int intValue;
    float floatValue;
    char *stringValue;

#line 113 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
