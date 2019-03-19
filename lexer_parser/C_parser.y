%code requires{
  #include "ast.hpp"
  #include <fstream>
  #include <string>
	#include <iostream>

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  extern NodePtr g_root;
  extern FILE* yyin;

  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  Node* node;
  double float_val;
  int32_t int_val;
  std::string* string;
}

%token T_IDENTIFIER T_STRINGLIT T_SIZEOF T_FLOATCONST T_INTCONST T_INC T_DEC T_LEFT_OP T_RIGHT_OP T_LE T_GE T_EQ T_NE T_ARROW T_AND T_OR T_MUL_ASSIGN T_DIV_ASSIGN T_MOD_ASSIGN T_ADD_ASSIGN T_ASSIGN T_OR_ASSIGN T_SUB_ASSIGN T_LEFT_ASSIGN T_RIGHT_ASSIGN T_AND_ASSIGN T_AND_L T_OR_L OR_ASSIGN T_TYPEDEF T_EXTERN T_STATIC T_AUTO T_REGISTER T_CHAR T_INT T_UNSIGNED T_VOID T_LONG T_SIGNED T_VOLATILE T_FLOAT T_DOUBLE T_STRUCT T_ENUM T_UNION T_ELLIPSIS T_CASE T_DEFAULT T_IF T_ELSE T_SWITCH T_WHILE T_DO T_FOR T_GOTO T_CONTINUE T_BREAK T_RETURN T_PLUS T_STAR T_DIV T_MOD T_CONST T_CHARCONST T_G T_L T_MINUS T_SHORT T_TILDE T_TYPE_NAME T_XOR T_XOR_ASSIGN T_EXCL T_SEMI T_LCB T_RCB T_COMA T_COL T_LB T_RB T_LSB T_RSB T_DOT T_QUEST

%type<node> primary_expression postfix_expression argument_expression_list unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression conditional_expression assignment_expression expression constant_expression declaration init_declarator_list init_declarator struct_or_union_specifier struct_or_union struct_declaration_list struct_declaration struct_declarator_list struct_declarator enum_specifier enumerator_list enumerator declarator direct_declarator pointer parameter_type_list parameter_list parameter_declaration identifier_list abstract_declarator direct_abstract_declarator initializer initializer_list statement labeled_statement compound_statement declaration_list statement_list expression_statement selection_statement iteration_statement jump_statement translation_unit external_declaration function_definition 
%type<string> T_IDENTIFIER T_SIZEOF T_INC T_DEC T_LEFT_OP T_RIGHT_OP T_LE T_GE T_EQ T_NE T_ARROW T_AND T_OR T_MUL_ASSIGN T_DIV_ASSIGN T_MOD_ASSIGN T_ADD_ASSIGN T_ASSIGN T_OR_ASSIGN T_SUB_ASSIGN T_LEFT_ASSIGN T_RIGHT_ASSIGN T_AND_ASSIGN T_AND_L T_OR_L T_XOR_ASSIGN OR_ASSIGN T_TYPEDEF T_EXTERN T_STATIC T_AUTO T_REGISTER T_CHAR T_INT T_UNSIGNED T_VOID T_LONG T_SIGNED T_VOLATILE T_FLOAT T_DOUBLE T_STRUCT T_ENUM T_UNION T_ELLIPSIS T_CASE T_DEFAULT T_IF T_ELSE T_SWITCH T_WHILE T_DO T_FOR T_GOTO T_CONTINUE T_BREAK T_RETURN T_PLUS T_STAR T_DIV T_MOD T_CONST T_STRINGLIT T_G T_L T_MINUS T_SHORT T_TILDE T_TYPE_NAME T_XOR T_EXCL T_SEMI T_LCB T_RCB T_COMA T_COL T_LB T_RB T_LSB T_RSB T_DOT T_QUEST
%type<string> unary_operator assignment_operator type_specifier specifier_qualifier_list type_qualifier type_qualifier_list type_name declaration_specifiers storage_class_specifier

%type<float_val> T_FLOATCONST
%type<int_val> T_INTCONST T_CHARCONST

//%right "then" T_ELSE



%start translation_unit

%%

primary_expression
	: T_IDENTIFIER {$$ = new Variable($1);}
	| T_INTCONST {$$ = new IntConst($1);}
  | T_FLOATCONST {$$ = new FloatConst($1);}
	| T_STRINGLIT {$$ = new String($1);}
	| T_LB expression T_RB {$$ = $2;}
	;


postfix_expression
	: primary_expression {$$ = $1;}
	| postfix_expression T_LSB expression T_RSB //{$$ = new Array($1, $3);}
	| postfix_expression T_LB T_RB {$$ = new FunctionCall($1, NULL);}
	| postfix_expression T_LB argument_expression_list T_RB {$$ = new FunctionCall($1, $3);}
	| postfix_expression T_DOT T_IDENTIFIER 
	| postfix_expression T_ARROW T_IDENTIFIER 
	| postfix_expression T_INC //{$$ = new PostFixExpression($1, $2)}
	| postfix_expression T_DEC //{$$ = new PostFixExpression($1, $2)}
	;

argument_expression_list
	: assignment_expression {$$ = new List(); $$->insert($1); $$->setType(ARG_EXP);}
	| argument_expression_list T_COMA assignment_expression {$1->insert($3); $$ = $1;}
	;

unary_expression
	: postfix_expression {$$ = $1;}
	| T_INC unary_expression //{$$ = new UnaryOperator($2, $1, NULL);}
	| T_DEC unary_expression //{$$ = new UnaryOperator($2, $1, NULL);}
	| unary_operator cast_expression //{ = new UnaryOperator} //TODO
	| T_SIZEOF unary_expression {$$ = new SizeOfOp($2);}
	| T_SIZEOF T_LB type_name T_RB {$$ = new SizeOfOp($3);}
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
	| T_LB type_name T_RB cast_expression {;}
	;

multiplicative_expression
	: cast_expression {$$ = $1;}
	| multiplicative_expression T_STAR cast_expression {$$ = new BinaryOperation($1, $2, $3);}
	| multiplicative_expression T_DIV cast_expression {$$ = new BinaryOperation($1, $2, $3);}
	| multiplicative_expression T_MOD cast_expression {$$ = new BinaryOperation($1, $2, $3);}
	;

additive_expression
	: multiplicative_expression {$$ = $1;}
	| additive_expression T_PLUS multiplicative_expression {$$ = new BinaryOperation($1, $2, $3);}
	| additive_expression T_MINUS multiplicative_expression {$$ = new BinaryOperation($1, $2, $3);}
	;

shift_expression
	: additive_expression {$$ = $1;}
	| shift_expression T_LEFT_OP additive_expression {$$ = new BinaryOperation($1, $2, $3);}
	| shift_expression T_RIGHT_OP additive_expression {$$ = new BinaryOperation($1, $2, $3);}
	;

relational_expression
	: shift_expression {$$ = $1;}
	| relational_expression T_L shift_expression {$$ = new BinaryOperation($1, $2, $3);}
	| relational_expression T_G shift_expression {$$ = new BinaryOperation($1, $2, $3);}
	| relational_expression T_LE shift_expression {$$ = new BinaryOperation($1, $2, $3);}
	| relational_expression T_GE shift_expression {$$ = new BinaryOperation($1, $2, $3);}
	;

equality_expression
	: relational_expression {$$ = $1;}
	| equality_expression T_EQ relational_expression {$$ = new BinaryOperation($1, $2, $3);}
	| equality_expression T_NE relational_expression {$$ = new BinaryOperation($1, $2, $3);}
	;

and_expression
	: equality_expression {$$ = $1;}
	| and_expression T_AND equality_expression {$$ = new BinaryOperation($1, $2, $3);}
	;

exclusive_or_expression
	: and_expression {$$ = $1;}
	| exclusive_or_expression T_XOR and_expression {$$ = new BinaryOperation($1, $2, $3);}
	;

inclusive_or_expression
	: exclusive_or_expression {$$ = $1;}
	| inclusive_or_expression T_OR exclusive_or_expression {$$ = new BinaryOperation($1, $2, $3);}
	;

logical_and_expression
	: inclusive_or_expression {$$ = $1;}
	| logical_and_expression T_AND_L inclusive_or_expression {$$ = new BinaryOperation($1, $2, $3);}
	;

logical_or_expression
	: logical_and_expression {$$ = $1;}
	| logical_or_expression T_OR_L logical_and_expression {$$ = new BinaryOperation($1, $2, $3);}
	;

conditional_expression
	: logical_or_expression {$$ = $1;}
	| logical_or_expression T_QUEST expression T_COL conditional_expression {;} //TODO
	;

assignment_expression
	: conditional_expression {$$ = $1;}
	| unary_expression assignment_operator assignment_expression {$$ = new BinaryOperation($1, $2, $3);}
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
	| expression T_COMA assignment_expression
	;

constant_expression
	: conditional_expression {$$ = $1;}
	;

declaration
	: declaration_specifiers T_SEMI {$$ = new Declaration($1, NULL);}
	| declaration_specifiers init_declarator_list T_SEMI {$$ = new Declaration($1, $2);}
	;

declaration_specifiers
	: storage_class_specifier {$$ = $1;}
	| storage_class_specifier declaration_specifiers {$$ = new std::string(*$1 + " " + *$2);}
	| type_specifier {$$ = $1;}
	| type_specifier declaration_specifiers {$$ = new std::string(*$1 + " " + *$2);}
	;

init_declarator_list
	: init_declarator {$$ = new List(); $$->insert($1); $$->setType(INITDEC);}
	| init_declarator_list T_COMA init_declarator {$1->insert($3); $$ = $1;}
	;

init_declarator
	: declarator {$$ = new InitDeclarator($1, NULL);}
	| declarator T_ASSIGN initializer {$$ = new InitDeclarator($1, $3);}
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
	| T_TYPE_NAME //{$$ = $1; /*maybe new typename*/}
	;

struct_or_union_specifier
	: struct_or_union T_IDENTIFIER T_LCB struct_declaration_list T_RCB
	| struct_or_union T_LCB struct_declaration_list T_RCB
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
	: specifier_qualifier_list struct_declarator_list T_SEMI
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list {$$ = new std::string(*$1 + " " + *$2);}
	| type_specifier {$$ = $1;}
	| type_qualifier specifier_qualifier_list {$$ = new std::string(*$1 + " " + *$2);}
	| type_qualifier {$$ = $1;}
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list T_COMA struct_declarator
	;

struct_declarator
	: declarator
	| T_COL constant_expression
	| declarator T_COL constant_expression
	;

enum_specifier
	: T_ENUM T_LCB enumerator_list T_RCB
	| T_ENUM T_IDENTIFIER T_LCB enumerator_list T_RCB
	| T_ENUM T_IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list T_COMA enumerator
	;

enumerator
	: T_IDENTIFIER
	| T_IDENTIFIER T_ASSIGN constant_expression
	;

type_qualifier
	: T_CONST {;}
	| T_VOLATILE {;}
	;

declarator
	: pointer direct_declarator
	| direct_declarator {$$ = $1;}
	;

direct_declarator
	: T_IDENTIFIER {$$ = new Variable($1);}
	| T_LB declarator T_RB {$$ = $2;}
	| direct_declarator T_LSB constant_expression T_RSB
	| direct_declarator T_LSB T_RSB
	| direct_declarator T_LB parameter_type_list T_RB {$$ = new DirectDeclarator($1, $3);}
	| direct_declarator T_LB identifier_list T_RB {$$ = new DirectDeclarator($1, $3);} //maybe something with gettypes to ensure that $1 is a string
	| direct_declarator T_LB T_RB {$$ = new DirectDeclarator($1, NULL);}
	;

pointer
	: T_STAR
	| T_STAR type_qualifier_list
	| T_STAR pointer
	| T_STAR type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier {;}
	| type_qualifier_list type_qualifier {;}
	;


parameter_type_list
	: parameter_list {$$ = $1;}
	;

parameter_list
	: parameter_declaration {$$ = new List(); $$->insert($1); $$->setType(PARAM);}
	| parameter_list T_COMA parameter_declaration {$1->insert($3); $$ = $1;}
	;

parameter_declaration
	: declaration_specifiers declarator {$$ = new ParamDeclaration($1, $2);}
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: T_IDENTIFIER {$$ = new IdentifierList(); $$->insert($1);}
	| identifier_list T_COMA T_IDENTIFIER {$1->insert($3); $$ = $1;}
	;

type_name
	: specifier_qualifier_list {$$ = $1;}
	| specifier_qualifier_list abstract_declarator {$$ = $1;}
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: T_LB abstract_declarator T_RB
	| T_LSB T_RSB
	| T_LSB constant_expression T_RSB
	| direct_abstract_declarator T_LSB T_RSB
	| direct_abstract_declarator T_LSB constant_expression T_RSB
	| T_LB T_RB
	| T_LB parameter_type_list T_RB
	| direct_abstract_declarator T_LB T_RB
	| direct_abstract_declarator T_LB parameter_type_list T_RB
	;

initializer
	: assignment_expression {$$ = $1;}
	| T_LCB initializer_list T_RCB {$$ = $2;}
	| T_LCB initializer_list T_COMA T_RCB {$$ = $2;}
	;

initializer_list
	: initializer {$$ = new List(); $$->insert($1); $$->setType(INIT);}
	| initializer_list T_COMA initializer {$1->insert($3); $$ = $1;}
	;

statement
	: labeled_statement {$$ = $1;}
	| compound_statement {$$ = $1;}
	| expression_statement {$$ = $1;}
	| selection_statement {$$ = $1;}
	| iteration_statement {$$ = $1;}
	| jump_statement {$$ = $1;}
	;

labeled_statement
	: T_IDENTIFIER T_COL statement
	| T_CASE constant_expression T_COL statement
	| T_DEFAULT T_COL statement
	;

compound_statement
	: T_LCB T_RCB {;}
	| T_LCB statement_list T_RCB {$$ = new Scope($2);}
	| T_LCB declaration_list T_RCB {$$ = new Scope($2);}
	| T_LCB declaration_list statement_list T_RCB {$$ = new Scope($2, $3);}
	;

declaration_list
	: declaration {$$ = new List(); $$->insert($1); $$->setType(DECL);}
	| declaration_list declaration {$1->insert($2); $$ = $1;}
	;

statement_list
	: statement {$$ = new List(); $$->insert($1); $$->setType(STAT);}
	| statement_list statement {$1->insert($2); $$ = $1;}
	;

expression_statement
	: T_SEMI {$$ = NULL;}
	| expression T_SEMI {$$ = $1;}
	;

selection_statement
	: T_IF T_LB expression T_RB statement  {$$ = new IfStatement($3, $5, NULL); /*%prec "then"*/}
	| T_IF T_LB expression T_RB statement T_ELSE statement {$$ = new IfStatement($3, $5, $7);}
	| T_SWITCH T_LB expression T_RB statement
	;

iteration_statement
	: T_WHILE T_LB expression T_RB statement
	| T_DO statement T_WHILE T_LB expression T_RB T_SEMI
	| T_FOR T_LB expression_statement expression_statement T_RB statement
	| T_FOR T_LB expression_statement expression_statement expression T_RB statement
	;

jump_statement
	: T_CONTINUE T_SEMI //{$$ = new Continue();}
	| T_BREAK T_SEMI //{$$ = new Break();}
	| T_RETURN T_SEMI {$$ = new Return(NULL);}
	| T_RETURN expression T_SEMI{$$ = new Return($2);}
	;

translation_unit
	: external_declaration {g_root->insert($1);}
	| translation_unit external_declaration{g_root->insert($2);}
	;

external_declaration
	: function_definition {$$ = $1;}
	| declaration {$$ = $1;}
	;

function_definition
	: declaration_specifiers declarator compound_statement {$$ = new Function($1, $2, $3); /* most important!*/}
	| declaration_specifiers declarator declaration_list compound_statement {$$ = new Function($1, $2, $4);}
	| declarator declaration_list compound_statement {}
	| declarator compound_statement {}
	;

%%

NodePtr g_root;
NodePtr parseAST(std::string name){
	g_root = new TranslationUnit();
	yyin = fopen(name.c_str(), "r");
		if(yyin) { 
			yyparse();
  		}
  fclose(yyin);
  return g_root;
}
