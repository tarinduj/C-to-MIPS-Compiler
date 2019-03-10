#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "Chunk"
#include <map>
#include <string>
#include <vector>

class SymbolTable {
  std::vector<std::map<std::string, std::variant<TypePtr, Chunk>>>;

public:
  void begin_scope();
  void end_scope();
  int get_entry_offset();
  int get_chunk();
};

#endif