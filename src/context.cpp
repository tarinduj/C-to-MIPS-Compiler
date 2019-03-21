#include "context.hpp"
#include "chunk.hpp"
#include "fmt/format.h"
#include "logger_macros.hpp"
#include "run.hpp"
#include <iostream>
#include <ostream>
#include <stdexcept>

using namespace fmt::literals;

Context::Context(std::ostream *os) : os(os) {
  type_table.emplace_back();
  chunk_table.emplace_back();
  initialize_regs();
}

void Context::initialize_regs() {
  for (auto it = regs.begin(); it != regs.end(); ++it) {
    *it = 0;
  }
  // Freely usable temporary registers
  regs[8] = true;
  regs[9] = true;
  regs[10] = true;
  regs[11] = true;
  regs[12] = true;
  regs[13] = true;
  regs[14] = true;
  regs[15] = true;
  regs[24] = true;
}

int Context::allocate_reg() {
  for (auto reg = regs.begin(); reg != regs.end(); ++reg) {
    if (*reg) {
      *reg = false;
      return reg - regs.begin();
    }
  }
  return -1;
}

std::ostream *Context::get_stream() const { return os; }

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
  *get_stream() << "\t#registering chunk with offset {}($fp)\n"_format(get_stack_size()) 
                << "\taddiu\t$sp,$sp,-{}\n"_format(type->get_size());
  auto chunk = std::shared_ptr<Chunk>(new LocalChunk(type, this));
  chunk_table.back()[identifier] = chunk;
  return chunk;
}

ChunkPtr Context::register_global_chunk(std::string identifier, TypePtr type) {
  auto chunk = std::shared_ptr<Chunk>(new GlobalChunk(type, this, identifier));
  global_chunk_table[identifier] = chunk;
  *get_stream() << "\t.globl\t{}\n"_format(identifier)
                << "\t.data\n"
                << "\t.align\t2\n"
                << "\t.size\t{}, 4\n"_format(identifier)
                << "{}:\n"_format(identifier);
  return chunk;
}

ChunkPtr Context::resolve_chunk(std::string identifier) const {
  for (auto it = chunk_table.rbegin(); it != chunk_table.rend(); ++it) {
    auto chunk = it->find(identifier);
    if (chunk != it->end()) {
      return chunk->second;
    }
  }
  auto chunk = global_chunk_table.find(identifier);
  if (chunk != global_chunk_table.end()) {
    return chunk->second;
  }
  std::string message = fmt::format("Cannot resolve chunk {}", identifier);
  MSG << message << "\n";
  throw std::logic_error(message);
}

void Context::new_scope() {
  type_table.emplace_back();
  chunk_table.emplace_back();
}

void Context::del_scope() {
  *get_stream() << "\t#leaving scope no.{}\n"_format(get_scope_num()) 
                << "\taddiu\t$sp,$sp,{}\n"_format(get_scope_size(get_scope_num()));
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

unsigned Context::get_scope_size(unsigned scope) const {
    int scope_size = 0;
    for (auto chunk_it = chunk_table.at(scope).begin(); chunk_it != chunk_table.at(scope).end(); ++chunk_it) {
        scope_size += chunk_it->second->get_type()->get_size();
    }
    return scope_size;
}
