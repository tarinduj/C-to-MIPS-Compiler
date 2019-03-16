#include "context.hpp"
#include "chunk.hpp"
#include <iostream>

Context::Context() {
  type_table.emplace_back();
  chunk_table.emplace_back();
}

TypePtr Context::register_type(std::string identifier, TypePtr type) {
  type_table[0][identifier] = type;
  return type;
}

TypePtr Context::resolve_type(std::string identifier) const {
  std::cout << type_table[0].size() << "resolving type\n";
  return type_table[0].find(identifier)->second;
}

ChunkPtr Context::register_chunk(std::string identifier, TypePtr type) {
  auto chunk = std::make_shared<Chunk>(offset, type, this);
  chunk_table[0][identifier] = chunk;
  offset += chunk->get_type()->get_size();
  return chunk;
}

ChunkPtr Context::resolve_chunk(std::string identifier) const {
  return chunk_table[0].find(identifier)->second;
}
