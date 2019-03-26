%option noyywrap
%option yylineno

%{
#include "C_parser.tab.hpp"
#include <string>
#include <iostream>
#include <sstream>
extern FILE *yyin;

extern "C" int fileno(FILE *stream);

void yyerror (char const *s);
int makeToken (int T);
int makeIntToken(int T);
int makeIntTokenHex (int T);
int makeIntTokenOct (int T);
int makeFloatToken(int T);
void printToken();
%}

D			[0-9]
O           [0-7]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%%

0[xX]{H}+{IS}?		{return makeIntTokenHex(T_INTCONST);}
0{O}+{IS}?		    {return makeIntTokenOct(T_INTCONST);}
{D}+{IS}?		    {return makeIntToken(T_INTCONST);}
{D}+{E}{FS}?		{return makeIntToken(T_INTCONST);}

{D}*"."{D}+({E})?{FS}?	{return makeFloatToken(T_FLOATCONST);}
{D}+"."{D}*({E})?{FS}?	{return makeFloatToken(T_FLOATCONST);}

"auto"      {return makeToken(T_AUTO);}
"break"     {return makeToken(T_BREAK);}
"case"      {return makeToken(T_CASE);}
"char"      {return makeToken(T_CHAR);}
"const"     {return makeToken(T_CONST);}
"continue"  {return makeToken(T_CONTINUE);}
"default"   {return makeToken(T_DEFAULT);}
"do"        {return makeToken(T_DO);}
"double"    {return makeToken(T_DOUBLE);}
"else"      {return makeToken(T_ELSE);}
"enum"      {return makeToken(T_ENUM);}
"extern"    {return makeToken(T_EXTERN);}
"float"     {return makeToken(T_FLOAT);}
"for"       {return makeToken(T_FOR);}
"goto"      {return makeToken(T_GOTO);}
"if"        {return makeToken(T_IF);}
"int"       {return makeToken(T_INT);}
"long"      {return makeToken(T_LONG);}
"register"  {return makeToken(T_REGISTER);}
"return"    {return makeToken(T_RETURN);}
"short"     {return makeToken(T_SHORT);}
"signed"    {return makeToken(T_SIGNED);}
"sizeof"    {return makeToken(T_SIZEOF);}
"static"    {return makeToken(T_STATIC);}
"struct"    {return makeToken(T_STRUCT);}
"typedef"   {return makeToken(T_TYPEDEF);}
"switch"    {return makeToken(T_SWITCH);}
"union"     {return makeToken(T_UNION);}
"unsigned"  {return makeToken(T_UNSIGNED);}
"void"      {return makeToken(T_VOID);}
"volatile"  {return makeToken(T_VOLATILE);}
"while"     {return makeToken(T_WHILE);}

"..."			{return makeToken(T_ELLIPSIS);}
">>="			{return makeToken(T_RIGHT_ASSIGN);}
"<<="			{return makeToken(T_LEFT_ASSIGN);}
"+="			{return makeToken(T_ADD_ASSIGN);}
"-="			{return makeToken(T_SUB_ASSIGN);}
"*="			{return makeToken(T_MUL_ASSIGN);}
"/="			{return makeToken(T_DIV_ASSIGN);}
"%="			{return makeToken(T_MOD_ASSIGN);}
"&="			{return makeToken(T_AND_ASSIGN);}
"^="			{return makeToken(T_XOR_ASSIGN);}
"|="			{return makeToken(T_OR_ASSIGN);}
">>"			{return makeToken(T_RIGHT_OP);}
"<<"			{return makeToken(T_LEFT_OP);}
"++"			{return makeToken(T_INC);}
"--"			{return makeToken(T_DEC);}
"->"			{return makeToken(T_ARROW);}
"&&"			{return makeToken(T_AND);}
"||"			{return makeToken(T_OR);}
"<="			{return makeToken(T_LE);}
">="			{return makeToken(T_GE);}
"=="			{return makeToken(T_EQ);}
"!="			{return makeToken(T_NE);}
"="			    {return makeToken(T_ASSIGN);}
"&"			    {return makeToken(T_AND_L);}
"|"			    {return makeToken(T_OR_L);}
"!"			    {return makeToken(T_EXCL);}
"~"			    {return makeToken(T_TILDE);}
"-"			    {return makeToken(T_MINUS);}
"+"			    {return makeToken(T_PLUS);}
"*"			    {return makeToken(T_STAR);}
"/"			    {return makeToken(T_DIV);}
"%"			    {return makeToken(T_MOD);}
"<"			    {return makeToken(T_L);}
">"			    {return makeToken(T_G);}
"^"			    {return makeToken(T_XOR);}
";"			    {return makeToken(T_SEMI);}
("{"|"<%")		{return makeToken(T_LCB);}
("}"|"%>")		{return makeToken(T_RCB);}
","			    {return makeToken(T_COMA);}
":"			    {return makeToken(T_COL);}
"("			    {return makeToken(T_LB);}
")"			    {return makeToken(T_RB);}
("["|"<:")		{return makeToken(T_LSB);}
("]"|":>")		{return makeToken(T_RSB);}
"."			    {return makeToken(T_DOT);}
"?"			    {return makeToken(T_QUEST);}
{L}({L}|{D})*   {return makeToken(T_IDENTIFIER); /*or return T_TYPE_NAME depending on whether it was added as typename*/}

L?\"(\\.|[^\\"])*\"	{return makeToken(T_STRINGLIT);}
(\/\/).*                {;}
(\/\*)[^*]*|[*]*(\*\/)  {;}
[ \t\v\n\f]             {;}
. {yyerror(yytext);}
%%
void yyerror (char const* s){
    fprintf (stderr, "Flex Error on line: %i\n", yylineno); /* s is the text that wasn't matched */
    exit(1);}
int makeToken (int T){
    yylval.string = new std::string(yytext);
    printToken();
    return T;
}
int makeIntToken (int T){
    yylval.int_val = std::stoi(yytext, 0);
    printToken();
    return T;
}
int makeIntTokenHex (int T){
    std::stringstream ss;
    ss << std::hex << yytext;
    unsigned int x;
    ss >> x;
    yylval.int_val = (int) x;
    printToken();
    return T;
}
int makeIntTokenOct (int T){
    std::stringstream ss;
    ss << std::oct << yytext;
    unsigned int x;
    ss >> x;
    yylval.int_val = (int) x;
    printToken();
    return T;
}
int makeFloatToken (int T){
    yylval.float_val = std::stod(yytext, 0);
    printToken();
    return T;
}
void printToken(){
    if(LEX_DEBUG){
        std::cerr<<yytext<<"\t";
    }
}
