#include "compiler.hpp"
#include "ast.hpp"
#include "run.hpp"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
  std::string name(argv[1]);
  NodePtr ast = parseAST(name);
  std::cout << std::endl;
  return 0;
}