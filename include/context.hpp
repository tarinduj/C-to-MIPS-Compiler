#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "chunk.hpp"
#include "type.hpp"
#include <map>
#include <ostream>
#include <vector>

class Chunk;
class LocalChunk;
class GlobalChunk;

class Context {
private:
  std::array<bool, 32> regs;
  std::vector<std::map<std::string, ChunkPtr>> chunk_table;
  std::map<std::string, ChunkPtr> global_chunk_table;
  std::vector<std::map<std::string, TypePtr>> type_table;
  std::map<std::string, TypePtr> global_type_table;
  std::ostream *os;
  unsigned offset = 0;

public:
  Context(std::ostream *os);
  Context();
  void initialize_regs();
  int allocate_reg();
  void order(std::string id, int &out_reg);
  std::pair<unsigned int, unsigned int> order(std::string id1, std::string id2);
  void new_scope();
  void del_scope();
  void new_frame();
  unsigned get_scope_size(unsigned scope) const;
  unsigned get_scope_num() const;
  unsigned get_stack_size() const;
  ChunkPtr register_chunk(std::string, TypePtr);
  ChunkPtr register_global_chunk(std::string, TypePtr);
  ChunkPtr resolve_chunk(std::string) const;
  TypePtr register_type(std::string, TypePtr);
  TypePtr register_global_type(std::string, TypePtr);
  TypePtr resolve_type(std::string) const;
  std::ostream *get_stream() const;
  friend Chunk;
  friend LocalChunk;
  friend GlobalChunk;
};

#endif
