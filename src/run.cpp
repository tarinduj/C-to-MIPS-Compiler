#include "run.hpp"
#include "ast.hpp"
#include "clara.hpp"
#include "fmt/format.h"
#include "verbosity.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "logger_macros.hpp"


int scopeCounter = 0;
std::vector<std::string> globalVarNames;


int run(int argc, char const *argv[]) {
  bool compile = false;
  bool translate = false;
  bool help = false;
  std::string output_file;
  std::string input_file;

  auto cli =
      clara::Help(help) |
      clara::Opt(compile)["-c"]["--compile"]("compile from C98 to MIPS") |
      clara::Opt(translate)["-t"]["--translate"](
          "translate from C89 to Python") |
      clara::Opt(output_file, "output")["-o"]("place the output into <file>") |
      clara::Arg(input_file, "input")("Input file").required();

  cli.parse(clara::Args(argc, argv));

  if (help) {
    std::cout << cli;
  } else if (compile) {
    MSG << fmt::format("I am gonna compile from {} to {}\n", input_file, output_file);
  } else if (translate) {
    MSG << fmt::format("I am gonna translate from {} to {}\n", input_file, output_file);
    std::ofstream target_file(output_file);
    NodePtr ast = parseAST(input_file);
    ast->pyPrint(target_file);
    addEnding(target_file);
  }

  MSG << "Finished\n";
  return 0;
}

void addEnding(std::ostream &os) {
  os << "# Invoke main as the starting point\n";
  os << "if __name__ == \"__main__\":\n";
  os << "\timport sys\n";
  os << "\tret=main()\n";
  os << "\tprint(\"temporary exit code:\")\n\tprint(ret)\n"; // temporarty line
  os << "\tsys.exit(ret)\n";
};
