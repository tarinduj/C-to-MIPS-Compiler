#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "chunk.hpp"
#include "type.hpp"
#include <map>
#include <ostream>
#include <vector>

class Context {
private:
  std::vector<std::map<std::string, ChunkPtr>> chunk_table;
  std::vector<std::map<std::string, TypePtr>> type_table;
  std::ostream *os;
  unsigned offset = 0;

public:
  Context(std::ostream *os);
  Context();
  void order(std::string id, int &out_reg);
  std::pair<unsigned int, unsigned int> order(std::string id1, std::string id2);
  void new_scope();
  void del_scope();
  void new_frame();
  unsigned get_scope_num() const;
  unsigned get_stack_size() const;
  ChunkPtr register_chunk(std::string, TypePtr);
  ChunkPtr resolve_chunk(std::string) const;
  TypePtr register_type(std::string, TypePtr);
  TypePtr resolve_type(std::string) const;
  std::ostream *get_stream() const;
};

#endif
