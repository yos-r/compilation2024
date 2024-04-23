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
#line 198 "file.y"

    int intValue;
    float floatValue;
    char *stringValue;

#line 137 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
