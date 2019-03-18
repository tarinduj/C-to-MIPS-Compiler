#include "run.hpp"
#include "ast.hpp"
#include "clara.hpp"
#include "fmt/format.h"
#include "loguru.hpp"
#include "verbosity.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace fmt::literals;

int scopeCounter = 0;
std::vector<std::string> globalVarNames;

int run(int argc, char const *argv[]) {
  bool compile = false;
  bool translate = false;
  bool help = false;
  std::string output_file;
  std::string input_file;

  int verbosity = 0;

  auto cli =
      clara::Help(help) |
      clara::Opt(compile)["-c"]["--compile"]("compile from C98 to MIPS") |
      clara::Opt(translate)["-t"]["--translate"](
          "translate from C89 to Python") |
      clara::Opt(verbosity, "from 0 to 10")["-v"]["--verbosity"](
          "set verbosity of messages") |
      clara::Opt(output_file, "output")["-o"]("place the output into <file>") |
      clara::Arg(input_file, "input")("Input file").required();

  cli.parse(clara::Args(argc, argv));
  if (help) {
    std::cout << cli;
    return 0;
  }
  loguru::g_stderr_verbosity = verbosity;
  LOG_F(INFO, "Hello world");
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
