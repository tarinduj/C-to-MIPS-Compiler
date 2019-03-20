#include "context.hpp"
#include "chunk.hpp"
#include "fmt/format.h"
#include "run.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

Context::Context(std::stringstream *os): os(os) {
  type_table.emplace_back();
  chunk_table.emplace_back();
}

Context::Context():os(nullptr){
  type_table.emplace_back();
  chunk_table.emplace_back();
}

std::stringstream *Context::get_stream() const {
  return os;
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
  std::string message = fmt::format("Cannot resolve type {}", identifier),
              msg(message);
  throw std::logic_error(message);
}

ChunkPtr Context::register_chunk(std::string identifier, TypePtr type) {
  auto chunk = std::make_shared<Chunk>(get_stack_size(), type, this);
  chunk_table.back()[identifier] = chunk;
  return chunk;
}

ChunkPtr Context::resolve_chunk(std::string identifier) const {
  for (auto it = chunk_table.rbegin(); it != chunk_table.rend(); ++it) {
    auto chunk = it->find(identifier);
    if (chunk != it->end()) {
      return chunk->second;
    }
  }
  std::string message = fmt::format("Cannot resolve chunk {}", identifier),
              msg(message);
  throw std::logic_error(message);
}

void Context::new_scope() {
  type_table.emplace_back();
  chunk_table.emplace_back();
}

void Context::del_scope() {
  type_table.pop_back();
  chunk_table.pop_back();
}

unsigned Context::get_stack_size() const {
  int stack_size = 0;
  for (auto chunk_scope = chunk_table.begin(); chunk_scope != chunk_table.end();
       ++chunk_scope) {
    for (auto chunk_it = chunk_scope->begin(); chunk_it != chunk_scope->end();
         ++chunk_it) {
      stack_size += chunk_it->second->get_type()->get_size();
    }
  }
  return stack_size;
}
