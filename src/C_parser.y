%code requires{
  #include "../include/ast.hpp"
  #include <fstream>

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  extern Node* g_root;
	extern FILE* yyin;

  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Node* node;
  double float_val;
  int32_t int_val;
  std::string* string;
}

%token T_IDENTIFIER T_STRINGLIT T_SIZEOF T_FLOATCONST T_INTCONST T_INC T_DEC T_LEFT_OP T_RIGHT_OP T_LE T_GE T_EQ T_NE T_ARROW T_AND T_OR T_MUL_ASSIGN T_DIV_ASSIGN T_MOD_ASSIGN T_ADD_ASSIGN T_ASSIGN T_OR_ASSIGN T_SUB_ASSIGN T_LEFT_ASSIGN T_RIGHT_ASSIGN T_AND_ASSIGN T_AND_L T_OR_L T_DOT XOR_ASSIGN OR_ASSIGN T_TYPEDEF T_EXTERN T_STATIC T_AUTO T_REGISTER T_CHAR T_INT T_UNSIGNED T_VOID T_LONG T_SIGNED T_VOLATILE T_FLOAT T_DOUBLE T_STRUCT T_ENUM T_UNION T_ELLIPSIS T_CASE T_DEFAULT T_IF T_ELSE T_SWITCH T_WHILE T_DO T_FOR T_GOTO T_CONTINUE T_BREAK T_RETURN T_PLUS T_STAR T_DIV T_MOD T_CONST T_CHARCONST T_G T_L T_MINUS T_SHORT T_TILDE T_TYPE_NAME T_XOR T_XOR_ASSIGN T_EXCL

%type<node> program primary_expression postfix_expression argument_expression_list unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression conditional_expression assignment_expression expression constant_expression declaration declaration_specifiers init_declarator_list init_declarator storage_class_specifier struct_or_union_specifier struct_or_union struct_declaration_list struct_declaration struct_declarator_list struct_declarator enum_specifier enumerator_list enumerator declarator direct_declarator pointer parameter_type_list parameter_list parameter_declaration identifier_list abstract_declarator direct_abstract_declarator initializer initializer_list statement labeled_statement compound_statement declaration_list statement_list expression_statement selection_statement iteration_statement jump_statement translation_unit external_declaration function_definition 
%type<string> T_IDENTIFIER T_SIZEOF T_INC T_DEC T_LEFT_OP T_RIGHT_OP T_LE T_GE T_EQ T_NE T_ARROW T_AND T_OR T_MUL_ASSIGN T_DIV_ASSIGN T_MOD_ASSIGN T_ADD_ASSIGN T_ASSIGN T_OR_ASSIGN T_SUB_ASSIGN T_LEFT_ASSIGN T_RIGHT_ASSIGN T_AND_ASSIGN T_AND_L T_OR_L T_DOT XOR_ASSIGN OR_ASSIGN T_TYPEDEF T_EXTERN T_STATIC T_AUTO T_REGISTER T_CHAR T_INT T_UNSIGNED T_VOID T_LONG T_SIGNED T_VOLATILE T_FLOAT T_DOUBLE T_STRUCT T_ENUM T_UNION T_ELLIPSIS T_CASE T_DEFAULT T_IF T_ELSE T_SWITCH T_WHILE T_DO T_FOR T_GOTO T_CONTINUE T_BREAK T_RETURN T_PLUS T_STAR T_DIV T_MOD T_CONST T_STRINGLIT T_G T_L T_MINUS T_SHORT T_TILDE T_TYPE_NAME T_XOR T_XOR_ASSIGN T_EXCL
%type<string> unary_operator assignment_operator type_specifier specifier_qualifier_list type_qualifier type_qualifier_list type_name

%type<float_val> T_FLOATCONST
%type<int_val> T_INTCONST T_CHARCONST

%right "then" T_ELSE



%start program
%%

program
    : translation_unit {g_root = $1}

primary_expression
	: T_IDENTIFIER {$$ = new Variable(*$1);}
	| T_INTCONST {$$ = new IntConst($1);}
  | T_FLOATCONST {$$ = new FloatConst($1);}
  | T_CHARCONST {$$ = new CharConst($1;}
	| T_STRINGLIT {$$ = new String(*$1);}
	| '(' expression ')' {$$ = $2;}
	;


postfix_expression
	: primary_expression {$$ = $1;}
	| postfix_expression '[' expression ']' {$$ = new Array($1, $3);}
	| postfix_expression '(' ')' {$$ = new FunctionCall(Null);}
	| postfix_expression '(' argument_expression_list ')' {$$ = new FunctionCall($3);}
	| postfix_expression T_DOT T_IDENTIFIER {$$ = new BinaryOperation($1, *$2, $3);}
	| postfix_expression T_ARROW T_IDENTIFIER {$$ = new BinaryOperation($1, *$2, $3);}
	| postfix_expression T_INC {$$ = new BinaryOperation($1, *$2, Null);}
	| postfix_expression T_DEC {$$ = new BinaryOperation($1, *$2, Null);}
	;

argument_expression_list
	: assignment_expression {$$ = $1;}
	| argument_expression_list ',' assignment_expression {;}
	;

unary_expression
	: postfix_expression {$$ = $1}
	| T_INC unary_expression {$$ = new BinaryOperation($2, *$1, Null);}
	| T_DEC unary_expression {$$ = new BinaryOperation($2, *$1, Null);}
	| unary_operator cast_expression {;/*needs to be done*/}
	| T_SIZEOF unary_expression
	| T_SIZEOF '(' type_name ')'
	;

unary_operator
	: T_AND {$$ = $1;}
	| T_STAR {$$ = $1;}
	| T_PLUS {$$ = $1;}
	| T_MINUS {$$ = $1;}
	| T_TILDE {$$ = $1;}
	| T_EXCL {$$ = $1;}
	;

cast_expression
	: unary_expression {$$ = $1;}
	| '(' type_name ')' cast_expression {$$ = new Cast($2, $4);}
	;

multiplicative_expression
	: cast_expression {$$ = $1;}
	| multiplicative_expression T_STAR cast_expression {$$ = new BinaryOperation($1, *$2, $3);}
	| multiplicative_expression T_DIV cast_expression {$$ = new BinaryOperation($1, *$2, $3);}
	| multiplicative_expression T_MOD cast_expression {$$ = new BinaryOperation($1, *$2, $3);}
	;

additive_expression
	: multiplicative_expression {$$ = $1;}
	| additive_expression T_PLUS multiplicative_expression {$$ = new BinaryOperation($1, *$2, $3);}
	| additive_expression T_MINUS multiplicative_expression {$$ = new BinaryOperation($1, *$2, $3);}
	;

shift_expression
	: additive_expression {$$ = $1;}
	| shift_expression T_LEFT_OP additive_expression {$$ = new BinaryOperation($1, *$2, $3);}
	| shift_expression T_RIGHT_OP additive_expression {$$ = new BinaryOperation($1, *$2, $3);}
	;

relational_expression
	: shift_expression {$$ = $1;}
	| relational_expression T_L shift_expression {$$ = new BinaryOperation($1, *$2, $3);}
	| relational_expression T_G shift_expression {$$ = new BinaryOperation($1, *$2, $3);}
	| relational_expression T_LE shift_expression {$$ = new BinaryOperation($1, *$2, $3);}
	| relational_expression T_GE shift_expression {$$ = new BinaryOperation($1, *$2, $3);}
	;

equality_expression
	: relational_expression {$$ = $1;}
	| equality_expression T_EQ relational_expression {$$ = new BinaryOperation($1, *$2, $3);}
	| equality_expression T_NE relational_expression {$$ = new BinaryOperation($1, *$2, $3);}
	;

and_expression
	: equality_expression {$$ = $1;}
	| and_expression T_AND equality_expression {$$ = new BinaryOperation($1, *$2, $3);}
	;

exclusive_or_expression
	: and_expression {$$ = $1;}
	| exclusive_or_expression T_XOR and_expression {$$ = new BinaryOperation($1, *$2, $3);}
	;

inclusive_or_expression
	: exclusive_or_expression {$$ = $1;}
	| inclusive_or_expression T_OR exclusive_or_expression {$$ = new BinaryOperation($1, *$2, $3);}
	;

logical_and_expression
	: inclusive_or_expression {$$ = $1;}
	| logical_and_expression T_AND_L inclusive_or_expression {$$ = new BinaryOperation($1, *$2, $3);}
	;

logical_or_expression
	: logical_and_expression {$$ = $1;}
	| logical_or_expression T_OR_L logical_and_expression {$$ = new BinaryOperation($1, *$2, $3);}
	;

conditional_expression
	: logical_or_expression {$$ = $1;}
	| logical_or_expression '?' expression ':' conditional_expression {;}
	;

assignment_expression
	: conditional_expression {$$ = $1;}
	| unary_expression assignment_operator assignment_expression {$$ = new BinaryOperation($1, *$2, $3);}
	;

assignment_operator
	: T_ASSIGN {$$ = $1;}
	| T_MUL_ASSIGN {$$ = $1;}
	| T_DIV_ASSIGN {$$ = $1;}
	| T_MOD_ASSIGN {$$ = $1;}
	| T_ADD_ASSIGN {$$ = $1;}
	| T_SUB_ASSIGN {$$ = $1;}
	| T_LEFT_ASSIGN {$$ = $1;}
	| T_RIGHT_ASSIGN {$$ = $1;}
	| T_AND_ASSIGN {$$ = $1;}
	| T_XOR_ASSIGN {$$ = $1;}
	| T_OR_ASSIGN {$$ = $1;}
	;

expression
	: assignment_expression {$$ = $1;}
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression {$$ = $1}
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator T_ASSIGN initializer
	;

storage_class_specifier
	: T_TYPEDEF {$$ = $1;}
	| T_EXTERN {$$ = $1;}
	| T_STATIC {$$ = $1;}
	| T_AUTO {$$ = $1;}
	| T_REGISTER {$$ = $1;}
	;

type_specifier
	: T_VOID {$$ = $1;}
	| T_CHAR {$$ = $1;}
	| T_SHORT {$$ = $1;}
	| T_INT {$$ = $1;}
	| T_LONG {$$ = $1;}
	| T_FLOAT {$$ = $1;}
	| T_DOUBLE {$$ = $1;}
	| T_SIGNED {$$ = $1;}
	| T_UNSIGNED {$$ = $1;}
	| struct_or_union_specifier
	| enum_specifier
	| T_TYPE_NAME {$$ = $1; /*maybe new typename*/}
	;

struct_or_union_specifier
	: struct_or_union T_IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union T_IDENTIFIER
	;

struct_or_union
	: T_STRUCT
	| T_UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: T_ENUM '{' enumerator_list '}'
	| T_ENUM T_IDENTIFIER '{' enumerator_list '}'
	| T_ENUM T_IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: T_IDENTIFIER
	| T_IDENTIFIER T_ASSIGN constant_expression
	;

type_qualifier
	: T_CONST
	| T_VOLATILE
	;

declarator
	: pointer direct_declarator
	| direct_declarator
	;

direct_declarator
	: T_IDENTIFIER
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
	;

pointer
	: T_STAR
	| T_STAR type_qualifier_list
	| T_STAR pointer
	| T_STAR type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


parameter_type_list
	: parameter_list
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: T_IDENTIFIER
	| identifier_list ',' T_IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement {$$ = new Statement($1); /*maybe*/}
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: T_IDENTIFIER ':' statement
	| T_CASE constant_expression ':' statement
	| T_DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: T_IF '(' expression ')' statement %prec "then" 
	| T_IF '(' expression ')' statement T_ELSE statement
	| T_SWITCH '(' expression ')' statement
	;

iteration_statement
	: T_WHILE '(' expression ')' statement
	| T_DO statement T_WHILE '(' expression ')' ';'
	| T_FOR '(' expression_statement expression_statement ')' statement
	| T_FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: T_CONTINUE ';' {$$ = new Continue();}
	| T_BREAK ';' {$$ = new Break();}
	| T_RETURN ';' {$$ = new Return(Null);}
	| T_RETURN expression ';'{$$ = new Return($2);}
	;

translation_unit
	: external_declaration {$$->add($1);}
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement {$$ = new function();}
	| declaration_specifiers declarator compound_statement {$$ = new function(); /* most important!*/}
	| declarator declaration_list compound_statement {$$ = new function();}
	| declarator compound_statement {$$ = new function();}
	;

%%

Node* g_root;
Node *parseAST(char* name){
  g_root = Null;
	yyin = fopen(name, "r");
	  if(yyin) { 
	  yyparse();
  }
  fclose(yyin);
  return g_root;
}
