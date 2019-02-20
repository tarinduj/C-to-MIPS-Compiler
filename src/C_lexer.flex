%option noyywrap
%option yylineno

%{


%}

D [0-9]
N [a-zA-Z_]
intSuffix [([uU][lL]?)|([lL][uU]?)]

%%


/* "auto"      {return T_AUTO;}
"break"     {return T_BREAK;}
"case"      {return T_CASE;}
"char"      {return T_CHAR;}
"const"     {return T_CONST;}
"continue"  {return T_CONTINIUE;}
"default"   {return T_DEFAULT;}
"do"        {return T_DO;}
"double"    {return T_DOUBLE;}
"else"      {return T_ELSE;}
"enum"      {return T_ENUM;}
"extern"    {return T_EXTERN;}
"float"     {return T_FLOAT;}
"for"       {return T_FOR;}
"goto"      {return T_GOTO;}
"if"        {return T_IF;} */
"int"       {return makeToken(T_INT);}
/* "long"      {return T_LONG;}
"register"  {return T_REGISTER;} */
"return"    {return makeToken(T_RETURN);}
/* "short"     {return T_SHORT;}
"signed"    {return T_SIGNED;}
"sizeof"    {return T_SIZEOF;}
"static"    {return T_STATIC;}
"struct"    {return T_STRUCT;}
"typedef"   {return T_TYPEDEF;}
"switch"    {return T_SWITCH;}
"union"     {return T_UNION;}
"unsigned"  {return T_UNSIGNED;} */
"void"      {return makeToken(T_VOID);}
/* "volatile"  {return T_VOLITAILE;}
"while"     {return T_WHILE;} */

"//".*              { /* DO NOTHING */ }
"/*"[^*]*|[*]*"*/"  { /* DO NOTHING */ }
[ \t\v\n\f]         { /* DO NOTHING */ }

{D}+{intSuffix}?                        {return makeIntToken(T_INTCONST); /*dec*/}
[0][0-7]*{intSuffix}?                   {return makeIntToken(T_INTCONST); /*octal*/}
(0x|0X)[0-9a-fA-F]+{intSuffix}?         {return makeIntToken(T_INTCONST); /*hex*/}

{L}({L}|{D})* {return T_IDENTIFIER /*check type of variable it refers to!*/}

"="         {return makeToken(T_EQUALS);}
";"         {return makeToken(T_SEMICOLON);}
"("         {return '(';}
")"         {return ')';}
"+"         {return makeToken(T_PLUS);}
"-"         {return makeToken(T_MINUS);}
"%"         {return makeToken(T_MOD);}
"/"         {return makeToken(T_DIV);}
"*"         {return makeToken(T_MLT);}



. {yyerror(yytext);}

%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
    fprintf (stderr, "Flex Error on line: %s\n", s); /* s is the text that wasn't matched */
    exit(1);
}

makeToken(int T){
    yylval.string = new std::string(yytext);
    return T;
}

makeIntToken(int T){
    yylval.integer = strtod(yytext, 0);
    return T;
}
