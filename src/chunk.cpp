#include "chunk.hpp"

Chunk::Chunk(unsigned offset, TypePtr type, Context *context)
    : offset(offset), chunkType(chunkType), type(type), context(context) {}

Chunk::ChunkType Chunk::get_chunk_type() const { return GLOBAL; }

TypePtr Chunk::get_type() const { return type; }

unsigned Chunk::get_offset() const { return offset; }
