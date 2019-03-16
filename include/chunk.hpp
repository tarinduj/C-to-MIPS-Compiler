#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <memory>

class Chunk;
typedef std::shared_ptr<Chunk> ChunkPtr;

#include "context.hpp"
#include "type.hpp"

class Context;

class Chunk {
public:
  enum ChunkType { GLOBAL, LOCAL, DEREFERENCEE };

private:
  int offset;
  TypePtr type;
  ChunkType chunkType;
  Context *context;

public:
  Chunk(unsigned, TypePtr, Context *);
  TypePtr get_type() const;
  ChunkType get_chunk_type() const;
  unsigned get_offset() const;
  void store();
  unsigned load();
};

#endif