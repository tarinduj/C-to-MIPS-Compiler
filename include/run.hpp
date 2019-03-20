#ifndef RUN_HPP
#define RUN_HPP

#include "context.hpp"
#include <ostream>
#include <string>
#include <vector>

//static Context *global_context;

void msg(std::string, bool endl = true);
void log(std::string, bool endl = true);

int run(int argc, char const *argv[]);

void addEnding(std::ostream &os);

#endif
