#include "chunk.hpp"
#include "fmt/format.h"

using namespace fmt::literals;

Chunk::Chunk(TypePtr type, Context *context) : type(type), context(context) {}

TypePtr Chunk::get_type() const { return type; }

int Chunk::get_offset() const { return 0; }

LocalChunk::LocalChunk(TypePtr type, Context *context) : Chunk(type, context) {
  offset = context->get_stack_size();
}

int LocalChunk::get_offset() const { return offset; }

void LocalChunk::store() {
	context->regs[*reg] = true;
	*context->get_stream() << "\tCode for storing  reg {} into fp + {}\n"_format(*reg, get_offset()); 
}

unsigned LocalChunk::get_reg() const {
	return *reg;
}

unsigned LocalChunk::load() {
	reg = context->allocate_reg();
	*context->get_stream() << "\tCode to load to reg {} from fp + {}\n"_format(*reg, get_offset()); 
}

void LocalChunk::discard() {
	context->regs[*reg] = true;
	reg.reset();
}
