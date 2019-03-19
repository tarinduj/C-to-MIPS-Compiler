#include "run.hpp"
#include "ast.hpp"
#include "clara.hpp"
#include "fmt/format.h"
#include "verbosity.hpp"
#include <fstream>
#include <iostream>
#include <string>

int scopeCounter = 0;
std::vector<std::string> globalVarNames;
bool elif = 0;

void msg(std::string msg, bool endl) {
  if (verbosity_config == V_NORM || verbosity_config == V_HIGH) {
    std::cerr << msg;
    if (endl) {
      std::cerr << '\n';
    }
  }
}

void log(std::string msg, bool endl) {
  if (verbosity_config == V_HIGH) {
    std::cerr << msg;
    if (endl) {
      std::cerr << '\n';
    }
  }
}

int run(int argc, char const *argv[]) {
  bool compile = false;
  bool translate = false;
  bool help = false;
  std::string output_file;
  std::string input_file;

  auto const setVerbosity = [&](std::string const &verbosity_str) {
    if (verbosity_str == "quiet")
      verbosity_config = V_QUIET;
    else if (verbosity_str == "normal")
      verbosity_config = V_NORM;
    else if (verbosity_str == "high")
      verbosity_config = V_HIGH;
    else
      return clara::ParserResult::runtimeError("Unrecognised verbosity, '" +
                                               verbosity_str + "'");
    return clara::ParserResult::ok(clara::ParseResultType::Matched);
  };

  auto cli =
      clara::Help(help) |
      clara::Opt(compile)["-c"]["--compile"]("compile from C98 to MIPS") |
      clara::Opt(translate)["-t"]["--translate"](
          "translate from C89 to Python") |
      clara::Opt(setVerbosity, "quiet|normal|high")["-v"]["--verbosity"](
          "set verbosity of messages") |
      clara::Opt(output_file, "output")["-o"]("place the output into <file>") |
      clara::Arg(input_file, "input")("Input file").required();

  cli.parse(clara::Args(argc, argv));

  if (help) {
    std::cout << cli;
  } else if (compile) {
    msg(fmt::format("I am gonna compile from {} to {}.", input_file,
                    output_file));
  } else if (translate) {
    msg(fmt::format("I am gonna translate from {} to {}.", input_file,
                    output_file));
    std::ofstream target_file(output_file);
    NodePtr ast = parseAST(input_file);
    ast->pyPrint(target_file);
    addEnding(target_file);
    // testing purposes
    if (verbosity_config == V_HIGH) {
      globalVarNames.clear();
      ast->pyPrint(std::cerr);
    }
  }

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
