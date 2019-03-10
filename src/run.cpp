#include "run.hpp"
#include "clara.hpp"
#include <iostream>

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
  }
  if (compile) {
    std::cout << "I am  ";
  } else if (translate) {
    std::cout << "I am translating ";
  }
  std::cout << "from " << input_file << " to " << output_file << '\n';
  return 0;
}