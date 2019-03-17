#ifndef AST_HPP
#define AST_HPP

#include "ast/ast_binop.hpp"
#include "ast/ast_declarator.hpp"
#include "ast/ast_function.hpp"
#include "ast/ast_jump.hpp"
#include "ast/ast_list.hpp"
#include "ast/ast_node.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_translation.hpp"
#include "ast/ast_variable.hpp"

extern NodePtr parseAST(std::string name);

#define LEX_DEBUG 0
#define PAR_DEBUG 0

#endif
