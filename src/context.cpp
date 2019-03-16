#include "context.hpp"
#include "chunk.hpp"
#include <iostream>

Context::Context() {
  type_table.emplace_back();
  chunk_table.emplace_back();
}

unsigned Context::get_scope_num() const { return chunk_table.size() - 1; }

TypePtr Context::register_type(std::string identifier, TypePtr type) {
  type_table.back()[identifier] = type;
  return type;
}

TypePtr Context::resolve_type(std::string identifier) const {
  for (auto it = type_table.rbegin(); it != type_table.rend(); ++it) {
    return it->find(identifier)->second;
  }
}

ChunkPtr Context::register_chunk(std::string identifier, TypePtr type) {
  auto chunk = std::make_shared<Chunk>(offset, type, this);
  chunk_table.back()[identifier] = chunk;
  offset += chunk->get_type()->get_size();
  return chunk;
}

ChunkPtr Context::resolve_chunk(std::string identifier) const {
  for (auto it = chunk_table.rbegin(); it != chunk_table.rend(); ++it) {
    return it->find(identifier)->second;
  }
}

void Context::new_scope() {
  type_table.emplace_back();
  chunk_table.emplace_back();
}

void Context::del_scope() {
  type_table.pop_back();
  chunk_table.pop_back();
}
