#include "chunk.hpp"

Chunk::Chunk(TypePtr type, Context *context) : type(type), context(context) {}

TypePtr Chunk::get_type() const { return type; }

int Chunk::get_offset() const { return 0; }

LocalChunk::LocalChunk(TypePtr type, Context *context) : Chunk(type, context) {
  offset = context->get_stack_size();
}

int LocalChunk::get_offset() const { return offset; }

void LocalChunk::store() {}
unsigned LocalChunk::get_reg() const {}
unsigned LocalChunk::load() {}
void LocalChunk::discard() {}
