#include "ast/ast_variable.hpp"

Variable::Variable(std::string *_s) : name(*_s) { delete _s; }