#include "c_compiler.hpp"
#include "ast.hpp"
#include "run.hpp"
#include <iostream>
#include <fstream>
#include <string>

int scopeCounter = 0;
std::vector<std::string> globalVarNames;

int main(int argc, char const *argv[]) {
  if(std::string(argv[1]) == "--translate"){
    std::string input_name(argv[2]);
    std::string target_name(argv[4]);
    std::ofstream target_file(target_name);
    NodePtr ast = parseAST(input_name);
    ast->pyPrint(target_file);
    addEnding(target_file);
  }
  else if(std::string(argv[1]) == "--compile"){
  }
  else{
    NodePtr ast = parseAST(std::string(argv[1]));
    ast->pyPrint(std::cout);
  }

  return 0;
}

