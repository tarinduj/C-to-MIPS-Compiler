#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "type.hpp"

class Chunk
{
	enum Type {GLOBAL, LOCAL};
	int offset;
	TypePtr type;
public:
	Chunk(unsigned, Type);
	TypePtr get_type();
	void store();
	unsigned load();
};

typedef std::shared_ptr<Chunk> ChunkPtr;

#endif