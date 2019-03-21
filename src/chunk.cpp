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
	*context->get_stream() << "\tsw\t${}, {}($fp)\n"_format(*reg, get_offset())
						   << "\tnop\n"; 
}

unsigned LocalChunk::get_reg() const {
	return *reg;
}

unsigned LocalChunk::load() {
	reg = context->allocate_reg();
	if (reg != -1){
		*context->get_stream() << "\tlw\t${}, {}($fp)\n"_format(*reg, get_offset())
							   << "\tnop\n";
		return *reg;
	} else {
		*context->get_stream() << "\t#fatal error, out of free registers\n"; 
	}
}

void LocalChunk::discard() {
	context->regs[*reg] = true;
	reg.reset();
}
