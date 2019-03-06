%option noyywrap
%option yylineno

%{
//#include "../include/ast.hpp"
#include "C_parser.tab.hpp"
#include <string>
extern FILE *yyin;


extern "C" int fileno(FILE *stream);

// int makeToken (int T);
// int makeIntToken (int T);
// int makeFloatToken (int T);
void yyerror (char const *s);
int makeToken (int T);
int makeIntToken(int T);
int makeDoubleToken(int T);
%}

D [0-9]
L [a-zA-Z_]
 //intSuffix [([uU][lL])?|[lL][uU]?]
intSuffix [uUlL][uUlL]?

%%


"auto"      {return T_AUTO;}
"break"     {return T_BREAK;}
"case"      {return T_CASE;}
"char"      {return T_CHAR;}
"const"     {return T_CONST;}
"continue"  {return T_CONTINUE;}
"default"   {return T_DEFAULT;}
"do"        {return T_DO;}
"double"    {return T_DOUBLE;}
"else"      {return T_ELSE;}
"enum"      {return T_ENUM;}
"extern"    {return T_EXTERN;}
"float"     {return T_FLOAT;}
"for"       {return T_FOR;}
"goto"      {return T_GOTO;}
"if"        {return T_IF;}
(int)       {return makeToken(T_INT);}
"long"      {return T_LONG;}
"register"  {return T_REGISTER;}
(return)    {return makeToken(T_RETURN);}
"short"     {return T_SHORT;}
"signed"    {return T_SIGNED;}
"sizeof"    {return T_SIZEOF;}
"static"    {return T_STATIC;}
"struct"    {return T_STRUCT;}
"typedef"   {return T_TYPEDEF;}
"switch"    {return T_SWITCH;}
"union"     {return T_UNION;}
"unsigned"  {return T_UNSIGNED;}
(void)     {return makeToken(T_VOID);}
"volatile"  {return T_VOLATILE;}
"while"     {return T_WHILE;}
(\/).*              { ; }
(\/\*)[^*]*|[*]*(\*\/)  { ; }
[ \t\v\n\f]         { ; }
{D}+{intSuffix}?                        {return makeIntToken(T_INTCONST);}

{L}({L}|{D})* {return makeToken(T_IDENTIFIER); /*check type of variable it refers to!*/}
(\=)         {return makeToken(T_EQ);}
(\;)         {return ';';}
(\+)         {return makeToken(T_PLUS);}
(\-)         {return makeToken(T_MINUS);}
(\%)         {return makeToken(T_MOD);}
(\/)         {return makeToken(T_DIV);}
(\*)         {return makeToken(T_STAR);}
(\))         {return ')';}
(\()         {return '(';}
(.) {yyerror(yytext);}
%%
void yyerror (char const* s){
    fprintf (stderr, "Flex Error on line: %s\n", s); /* s is the text that wasn't matched */
    exit(1);}
int makeToken (int T){
    yylval.string = new std::string(yytext);
    return T;
}
int makeIntToken (int T){
    yylval.int_val = std::stoi(yytext, 0);
    return T;
}
int makeFloatToken (int T){
    yylval.float_val = std::stod(yytext, 0);
    return T;
}
