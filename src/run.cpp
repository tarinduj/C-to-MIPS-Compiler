#include "run.hpp"
#include "ast.hpp"
#include "clara.hpp"
#include "context.hpp"
#include "fmt/format.h"
#include "logger_macros.hpp"
#include "verbosity.hpp"
#include <fstream>
#include <iostream>
#include <string>

Context * global_context;

int run(int argc, char const *argv[]) {
  bool compile = false;
  bool translate = false;
  bool help = false;
  std::string output_file;
  std::string input_file;


  auto cli =
      clara::Help(help) |
      clara::Opt(compile)["-c"]["-S"]["--compile"]("compile from C98 to MIPS") |
      clara::Opt(translate)["-t"]["--translate"](
          "translate from C89 to Python") |
      clara::Opt(output_file, "output")["-o"]("place the output into <file>") |
      clara::Arg(input_file, "input")("Input file").required();

  cli.parse(clara::Args(argc, argv));

  std::ofstream target_file(output_file);
  global_context = new Context(&target_file);

  if (help) {
    std::cout << cli;
  } else if (compile) {
    NodePtr ast = parseAST(input_file);
    MSG << fmt::format("I am gonna compile from {} to {}\n", input_file,
                       output_file);
    ast->mipsPrint();

  } else if (translate) {
    MSG << fmt::format("I am gonna translate from {} to {}\n", input_file,
                       output_file);
    NodePtr ast = parseAST(input_file);
    ast->pyPrint(target_file);
    addEnding(target_file);
    // testing purposes
    if (verbosity_config == V_HIGH) {
      globalVarNames.clear();
      ast->pyPrint(std::cerr);
    }
  }

  MSG << "Finished\n";
  target_file.close();
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
