#include "context.hpp"
#include "chunk.hpp"
#include "constants.hpp"
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
  //register 25 used for internal purposes by context and chunk
}

int Context::allocate_reg() {
  for (auto reg = regs.begin(); reg != regs.end(); ++reg) {
    if (*reg) {
      *reg = false;
      return reg - regs.begin();
    }
  }
  ERR << "Out of registers.\n";
  return -1;
}

std::ostream *Context::get_stream() const { return os; }

unsigned Context::get_scope_num() const { return chunk_table.size() - 1; }

TypePtr Context::register_type(std::string identifier, TypePtr type) {
  LOG << "TL{}= {}\n"_format(get_scope_num(),identifier);
  type_table.back()[identifier] = type;
  return type;
}

TypePtr Context::register_global_type(std::string identifier, TypePtr type) {
  LOG << "TG= {}\n"_format(identifier);
  global_type_table[identifier] = type;
  return type;
}


TypePtr Context::resolve_type(std::string identifier) const {
  for (auto it = type_table.rbegin(); it != type_table.rend(); ++it) {
    auto identifier_type_pair = it->find(identifier);
    if (identifier_type_pair != it->end()) {
      return identifier_type_pair->second;
    }
  }
  auto type = global_type_table.find(identifier);
  if (type != global_type_table.end()) {
    return type->second;
  }
  ERR << fmt::format("Cannot resolve type {}", identifier);
  std::string message = fmt::format("Cannot resolve type {}", identifier);
  throw std::logic_error(message);
}

void Context::pass_args(std::vector<ChunkPtr> arguments){
  int unique = 0;
  for (auto chunk_it = arguments.rbegin(); chunk_it != arguments.rend(); ++chunk_it){
    auto to_chunk = register_chunk("__argument_{}"_format(unique++), (*chunk_it)->get_type());
    to_chunk->copy_from(*chunk_it);
  }
  *get_stream() << "\tlw\t$4,4($sp)\n"
                << "\tlw\t$5,8($sp)\n"
                << "\tlw\t$6,12($sp)\n"
                << "\tlw\t$7,16($sp)\n"
                << "\taddiu\t$sp,$sp,4\n";
}

ChunkPtr Context::register_argument_chunk(std::string identifier, TypePtr type) {
  LOG << "CA= {}\n"_format(identifier);
  auto localchunkptr = new LocalChunk(type, this);
  constexpr int args_offset = 2 * WORD_BYTES;
  localchunkptr->set_offset(-get_argument_stack_size()-args_offset);
  auto chunk = std::shared_ptr<Chunk>(localchunkptr);
  argument_chunk_table[identifier] = chunk;
  return chunk;
}

void Context::normalize_argument_chunks() const {
  *get_stream() << "\tsw\t$4,8($fp)\n"
                << "\tsw\t$5,12($fp)\n"
                << "\tsw\t$6,16($fp)\n"
                << "\tsw\t$7,20($fp)\n";
}

unsigned Context::get_argument_stack_size() const {
  unsigned argument_stack_size = 0;
  for (auto chunk_it = argument_chunk_table.begin(); chunk_it != argument_chunk_table.end(); ++chunk_it){
    argument_stack_size += chunk_it->second->get_type()->get_size();
  } 
  return argument_stack_size;
}

ChunkPtr Context::register_chunk(std::string identifier, TypePtr type) {
  LOG << "CL{}= {}\n"_format(get_scope_num(),identifier);
  *get_stream() << "\t#registering chunk with offset {}($fp)\n"_format(
                       get_stack_size())
                << "\taddiu\t$sp,$sp,-{}\n"_format(type->get_size());
  auto chunk = std::shared_ptr<Chunk>(new LocalChunk(type, this));
  chunk_table.back()[identifier] = chunk;
  return chunk;
}

ChunkPtr Context::register_global_chunk(std::string identifier, TypePtr type) {
  LOG << "CG= {}\n"_format(identifier);
  auto chunk = std::shared_ptr<Chunk>(new GlobalChunk(type, this, identifier));
  global_chunk_table[identifier] = chunk;
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
  chunk = argument_chunk_table.find(identifier);
  if (chunk != argument_chunk_table.end()) {
    return chunk->second;
  }
  std::string message = fmt::format("Cannot resolve chunk {}", identifier);
  ERR << message << "\n";
  throw std::logic_error(message);
}

void Context::new_scope() {
  type_table.emplace_back();
  chunk_table.emplace_back();
  CONTEXTLOG << ">>> New scope {}.\n"_format(get_scope_num());
}

void Context::del_scope() {
  CONTEXTLOG << "<<< Deleting scope {}.\n"_format(get_scope_num());
  *get_stream() << "\t#leaving scope no.{}\n"_format(get_scope_num())
                << "\taddiu\t$sp,$sp,{}\n"_format(
                       get_scope_size(get_scope_num()));
  type_table.pop_back();
  chunk_table.pop_back();
}

void Context::new_frame(){
  CONTEXTLOG << "|<< Reseting this frame. {} deleted.\n"_format(get_scope_num());
  while(get_scope_num() != -1){
    del_scope();
  }
  argument_chunk_table.clear();
  type_table.emplace_back();
  chunk_table.emplace_back();
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
  for (auto chunk_it = chunk_table.at(scope).begin();
       chunk_it != chunk_table.at(scope).end(); ++chunk_it) {
    scope_size += chunk_it->second->get_type()->get_size();
  }
  return scope_size;
}
