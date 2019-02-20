%code requires{
  #include "ast.hpp"

  #include <cassert>

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  extern const Node* g_root;
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Node* node;
  const Expression* expression;
  //double number;
  int32_t integer;
  std::string* string;
  std::string* string_lit;
}

%token <string> T_IDENTIFIER
%token <integer> T_INTCONST
%token <string_lit> T_STRINGLIT

%token T_PLUS T_MINUT T_MLT T_DIV T_MOD

%start root

%%

primary_expression
    : T_IDENTIFIER
    | constant
    | T_STRINGLIT
    | '(' expression ')'
    ;

constant
    : T_INTCONST
    ;

postfix_expression
    : primary_expression {$$ = $1;}
    //more
    ;

unary_expression
    : postfix_expression {$$ = $1;}
    //more
    ;

cast_expression
    : unary_expression {$$ = $1;}
    //| '(' type_name ')' cast_expression
    ;

multiplicative_expression
    : cast_expression {$$ = $1;}
    //| multiplicative_expression T_MLT cast_expression
    //| multiplicative_expression T_DIV cast_expression
    //| multiplicative_expression T_MOD cast_expression
    ;

additive_expression
    : multiplicative_expression  {$$ = $1;}
    //| additive_expression T_PLUS multiplicative_expression {$$ = new additiveExpression($1, *$2, $3);}
    //| additive_expression T_MINUS multiplicative_expression {$$ = new additiveExpression($1, *$2, $3);}
    ;

shift_expression
    : additive_expression {$$ = $1;}
    //| shift_expression T_LEFT_OP additive_expression
    //| shift_expression T_RIGHT_OP additive_expression
    ;

relational_expression
    : shift_expression {$$ = $1;}
    //more
    ;

equality_expression
    : relational_expression {$$ = $1;}
    ;

and_expression
    : equality_expression {$$ = $1;}
    //| and_expression T_BIT_AND equality_expression
    ;

xor_expression
    : and_expression {$$ = $1;}
    //| xor_expression T_BIT_XOR and_expression
    ;

or_expression
    : xor_expression {$$ = $1;}
    //| or_expression T_BIT_OR xor_expression
    ;

logical_and_expression
    : or_expression {$$ = $1;}
    | logical_and_expression T_AND or_expression
    ;

logical_or_expression
    : logical_and_expression {$$ = $1;}
    | logical_or_expression T_OR logical_and_expression
    ;

conditional_expression
    : logical_or_expression {$$ = $1;}
    //| logical_or_expression '?' expression ':' conditional_expression
    ;

assignment_expression
    : conditional_expression {$$ = $1;}
    unary_expression assignment_operator assignment_expression {$$ = new assignmentExpression($1, *$2, $3)}
    ;

assignment_operator
    : T_EQUALS
    //more
    ;

expression
    : assignment_expression {$$ = $1;}
    //| expression ',' assignment_expression
    ;

constant_expression
    : conditional_expression
    ;

statement
    /* : labeled_statement
    | compound_statement
    | expression_statement
    | selection_statement
    | itteration_statement
    | jump_statement */
    : expression_statement {$$ = $1}
    ;

expression_statement
    : T_SEMICOLON {$$ = new expressionStatement(NULL);}
    | expression T_SEMICOLON {$$ = new expressionStatement($1);}
    ;


%%

const Node* g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST(){
    g_root=0;
    yyparse();
    return g_root;
}
