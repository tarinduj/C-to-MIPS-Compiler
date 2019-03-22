#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <memory>
#include <optional>

class Chunk;
typedef std::shared_ptr<Chunk> ChunkPtr;

#include "context.hpp"
#include "type.hpp"

class Context;

class Chunk {
protected:
  std::optional<unsigned> reg;
  TypePtr type;
  Context *context;

public:
  Chunk(TypePtr, Context *);
  TypePtr get_type() const;
  virtual int get_offset() const;
  virtual void store() = 0;
  virtual unsigned get_reg() const = 0;
  virtual unsigned load() = 0;
  virtual void discard() = 0;
};

class GlobalChunk : public Chunk {
private:
  std::string name;

public:
  GlobalChunk(TypePtr, Context *, std::string name);
  virtual void store();
  virtual unsigned get_reg() const;
  virtual unsigned load();
  virtual void discard();
};

class LocalChunk : public Chunk {
private:
  int offset;

public:
  LocalChunk(TypePtr, Context *);
  virtual void set_offset(const int& in_offset);
  virtual int get_offset() const;
  virtual void store();
  virtual unsigned get_reg() const;
  virtual unsigned load();
  virtual void discard();
};

#endif