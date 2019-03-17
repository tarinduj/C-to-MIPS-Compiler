#ifndef COMPILER_HPP
#define COMPILER_HPP
#include <ostream>

int main(int argc, char const *argv[]);
void addEnding(std::ostream &os) {
  os << "# Invoke main as the starting point\n";
  os << "if __name__ == \"__main__\":\n";
  os << "\timport sys\n";
  os << "\tret=main()\n";
  os << "\tprint(\"temporary exit code:\")\n\tprint(ret)\n"; //temporarty line
  os << "\tsys.exit(ret)\n";
};

#endif