#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "chunk.hpp"
#include "type.hpp"
#include <map>
#include <vector>

class Context {
private:
  std::vector<std::map<std::string, ChunkPtr>> chunk_table;
  std::vector<std::map<std::string, TypePtr>> type_table;

public:
  Context();
  void order(std::string id, int &out_reg);
  std::pair<unsigned int, unsigned int> order(std::string id1, std::string id2);
  void new_scope();
  void del_scope();
  void new_frame();
  void register_type(std::string, TypePtr);
  void register_chunk(std::string, ChunkPtr);
  TypePtr resolve_type(std::string);
  ChunkPtr resolve_chunk(std::string);
};

#endif
