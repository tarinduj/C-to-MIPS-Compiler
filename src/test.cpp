#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "chunk.hpp"
#include "constants.hpp"
#include "context.hpp"
#include "type.hpp"
#include <memory>

TEST_CASE("Type", "[Type]") {
  TypePtr integer_type = std::make_shared<PrimitiveType>();
  CHECK(integer_type->get_size() == WORD_BYTES);
  CHECK(integer_type->get_type_category() == Type::PRIMITIVE);
  CHECK(integer_type->get_primitive_type() == Type::INT);
}

TEST_CASE("Context type retreival", "[Type][Context]") {
  std::stringstream ss;
  Context context(&ss);
  TypePtr type = context.register_type(
      "type1", std::shared_ptr<PrimitiveType>(new PrimitiveType()));
  CHECK(type->get_type_category() == Type::PRIMITIVE);
  CHECK(type->get_primitive_type() == Type::INT);
  TypePtr type_2 = context.resolve_type("type1");
  CHECK(type_2->get_type_category() == Type::PRIMITIVE);
  CHECK(type_2->get_primitive_type() == Type::INT);
}

TEST_CASE("Chunk", "[Chunk][Type]") {
  std::stringstream ss;
  Context context(&ss);
  TypePtr integer_type = std::make_shared<PrimitiveType>();
  ChunkPtr a = context.register_chunk("a", integer_type);
  CHECK(a->get_type() == integer_type);
  CHECK(a->get_offset() == 0);
}

TEST_CASE("Register and resolve Chunk", "[Chunk][Type]") {
  std::stringstream ss;
  Context context(&ss);
  TypePtr integer_type = std::make_shared<PrimitiveType>();
  auto a_1 = context.register_chunk("a", integer_type);
  auto a_2 = context.resolve_chunk("a");
  CHECK(a_1 == a_2);
  CHECK(a_1->get_type() == integer_type);
  CHECK(a_1->get_offset() == 0);
  auto b_1 = context.register_chunk("b", integer_type);
  auto b_2 = context.resolve_chunk("b");
  CHECK(b_1 == b_2);
  CHECK(b_1->get_type() == integer_type);
  CHECK(b_1->get_offset() == integer_type->get_size());
}

TEST_CASE("Scoping types", "[Scope][Type]") {
  TypePtr type1 = std::shared_ptr<PrimitiveType>(new PrimitiveType());
  TypePtr type2 = std::shared_ptr<PrimitiveType>(new PrimitiveType());
  TypePtr type3 = std::shared_ptr<PrimitiveType>(new PrimitiveType());
  std::stringstream ss;
  Context context(&ss);
  INFO("Scope 0");
  context.register_type("type", type1);
  CHECK(context.resolve_type("type") == type1);
  context.new_scope();
  INFO("Scope 1");
  context.register_type("type", type2);
  CHECK(context.resolve_type("type") == type2);
  context.new_scope();
  INFO("Scope 2");
  context.register_type("type", type3);
  CHECK(context.resolve_type("type") == type3);
  context.del_scope();
  INFO("Scope 1");
  CHECK(context.resolve_type("type") == type2);
  context.del_scope();
  INFO("Scope 0");
  CHECK(context.resolve_type("type") == type1);
}

TEST_CASE("Scoping chunks", "[Scope][Chunk]") {
  TypePtr type = std::shared_ptr<PrimitiveType>(new PrimitiveType());
  std::stringstream ss;
  Context context(&ss);
  INFO("Scope 0");
  auto chunk0 = context.register_chunk("chunk", type);
  unsigned chunksize = chunk0->get_type()->get_size();
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk0);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 0 * chunksize);
  context.new_scope();
  INFO("Scope 0-1");
  auto chunk1 = context.register_chunk("chunk", type);
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk1);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 1 * chunksize);
  context.new_scope();
  INFO("Scope 0-1-2");
  auto chunk2 = context.register_chunk("chunk", type);
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk2);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 2 * chunksize);
  context.del_scope();
  INFO("Scope 0-1");
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk1);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 1 * chunksize);
  auto chunk3 = context.register_chunk("another_chunk", type);
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("another_chunk") == chunk3);
  CHECK(context.resolve_chunk("another_chunk")->get_offset() == 2 * chunksize);
  context.new_scope();
  INFO("Scope 0-1-2");
  auto chunk4 = context.register_chunk("chunk", type);
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk4);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 3 * chunksize);
  CHECK(context.resolve_chunk("another_chunk") == chunk3);
  CHECK(context.resolve_chunk("another_chunk")->get_offset() == 2 * chunksize);
  context.del_scope();
  INFO("Scope 0-1");
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk1);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 1 * chunksize);
  CHECK(context.resolve_chunk("another_chunk") == chunk3);
  CHECK(context.resolve_chunk("another_chunk")->get_offset() == 2 * chunksize);
  context.del_scope();
  INFO("Scope 0");
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk0);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 0 * chunksize);
  std::cout << ss.str();
}

TEST_CASE("Scoping chunks 2", "[Scope][Chunk]") {
  TypePtr type = std::shared_ptr<PrimitiveType>(new PrimitiveType());
  std::stringstream ss;
  Context context(&ss);
  INFO("Scope 0");
  auto chunk0 = context.register_chunk("chunk", type);
  unsigned chunksize = chunk0->get_type()->get_size();
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk0);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 0 * chunksize);
  context.new_scope();
  INFO("Scope 0-1");
  auto chunk1 = context.register_chunk("chunk", type);
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk1);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 1 * chunksize);
  context.new_scope();
  INFO("Scope 0-1-2");
  auto chunk2 = context.register_chunk("chunk", type);
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk2);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 2 * chunksize);
  context.del_scope();
  INFO("Scope 0-1");
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk1);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 1 * chunksize);
  context.new_scope();
  INFO("Scope 0-1-2");
  auto chunk3 = context.register_chunk("chunk", type);
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk3);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 2 * chunksize);
  context.del_scope();
  INFO("Scope 0-1");
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk1);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 1 * chunksize);
  context.del_scope();
  INFO("Scope 0");
  CAPTURE(context.get_stack_size());
  CHECK(context.resolve_chunk("chunk") == chunk0);
  CHECK(context.resolve_chunk("chunk")->get_offset() == 0 * chunksize);
}
TEST_CASE("Loading and storing chunks to registers", "[Load][Store][Chunk]") {}

TEST_CASE("Context printing", "[Context][Codegen]") {
  std::stringstream ss;
  Context context(&ss);
  *context.get_stream() << "Hello, ";
  *context.get_stream() << "world.\n";
  REQUIRE(ss.str() == std::string("Hello, world.\n"));
}

TEST_CASE("Register allocation by context", "[Context]") {
  std::stringstream ss;
  Context context(&ss);
  TypePtr type = std::shared_ptr<PrimitiveType>(new PrimitiveType());
  auto chunk8 = context.register_chunk("chunk8", type);
  CHECK(chunk8->load() == 8);
  CHECK(chunk8->get_reg() == 8);
  auto chunk9 = context.register_chunk("chunk9", type);
  CHECK(chunk9->load() == 9);
  CHECK(chunk9->get_reg() == 9);
  auto chunk10 = context.register_chunk("chunk10", type);
  CHECK(chunk10->load() == 10);
  CHECK(chunk10->get_reg() == 10);
  auto chunk11 = context.register_chunk("chunk11", type);
  CHECK(chunk11->load() == 11);
  CHECK(chunk11->get_reg() == 11);
  auto chunk12 = context.register_chunk("chunk12", type);
  CHECK(chunk12->load() == 12);
  CHECK(chunk12->get_reg() == 12);
  auto chunk13 = context.register_chunk("chunk13", type);
  CHECK(chunk13->load() == 13);
  CHECK(chunk13->get_reg() == 13);
  auto chunk14 = context.register_chunk("chunk14", type);
  CHECK(chunk14->load() == 14);
  CHECK(chunk14->get_reg() == 14);
  auto chunk15 = context.register_chunk("chunk15", type);
  CHECK(chunk15->load() == 15);
  CHECK(chunk15->get_reg() == 15);
  auto chunk24 = context.register_chunk("chunk16", type);
  CHECK(chunk24->load() == 24);
  CHECK(chunk24->get_reg() == 24);
  auto extra = context.register_chunk("extra", type);
  CHECK(extra->load() == 0);
  CHECK(extra->get_reg() == -1);
  auto one_more_extra = context.register_chunk("one_more_extra", type);
  chunk13->store();
  one_more_extra->load();
  CHECK(one_more_extra->get_reg() == 13);
  std::cout << ss.str();
}

TEST_CASE("Global Chunks", "[Chunk]") {
  std::stringstream ss;
  Context context(&ss);
  TypePtr type = std::shared_ptr<PrimitiveType>(new PrimitiveType());
  auto chunk8 = context.register_global_chunk("chunk8", type);
  auto chunk9 = context.register_global_chunk("chunk9", type);
  auto chunk10 = context.register_global_chunk("chunk10", type);
  auto chunk11 = context.register_global_chunk("chunk11", type);
  auto chunk12 = context.register_global_chunk("chunk12", type);
  auto chunk13 = context.register_global_chunk("chunk13", type);
  auto chunk14 = context.register_global_chunk("chunk14", type);
  auto chunk15 = context.register_global_chunk("chunk15", type);
  auto chunk24 = context.register_global_chunk("chunk16", type);
  auto extra = context.register_global_chunk("extra", type);
  auto one_more_extra = context.register_global_chunk("one_more_extra", type);
  CHECK(chunk8->load() == 8);
  CHECK(chunk8->get_reg() == 8);
  CHECK(chunk9->load() == 9);
  CHECK(chunk9->get_reg() == 9);
  CHECK(chunk10->load() == 10);
  CHECK(chunk10->get_reg() == 10);
  CHECK(chunk11->load() == 11);
  CHECK(chunk11->get_reg() == 11);
  CHECK(chunk12->load() == 12);
  CHECK(chunk12->get_reg() == 12);
  CHECK(chunk13->load() == 13);
  CHECK(chunk13->get_reg() == 13);
  CHECK(chunk14->load() == 14);
  CHECK(chunk14->get_reg() == 14);
  CHECK(chunk15->load() == 15);
  CHECK(chunk15->get_reg() == 15);
  CHECK(chunk24->load() == 24);
  CHECK(chunk24->get_reg() == 24);
  CHECK(extra->load() == 0);
  CHECK(extra->get_reg() == -1);
  chunk13->store();
  one_more_extra->load();
  CHECK(one_more_extra->get_reg() == 13);
  std::cout << ss.str();
}

TEST_CASE("Repeated load handling", "[Chunk][GlobalChunk][LocalChunk]") {
  std::stringstream ss;
  Context context(&ss);
  TypePtr type = std::shared_ptr<PrimitiveType>(new PrimitiveType());
  auto globalChunk = context.register_global_chunk("global", type);
  auto localChunk = context.register_chunk("local", type);
  auto reg1 = globalChunk->load();
  auto reg2 = globalChunk->load();
  auto reg3 = globalChunk->get_reg();
  CHECK(reg1 == reg2);
  CHECK(reg2 == reg3);
  reg1 = localChunk->load();
  reg2 = localChunk->load();
  reg3 = localChunk->get_reg();
  CHECK(reg1 == reg2);
  CHECK(reg2 == reg3);
}

TEST_CASE("Size of scope"){
  std::stringstream ss;
  Context context(&ss);
  TypePtr type = std::shared_ptr<PrimitiveType>(new PrimitiveType());
  context.register_chunk("scope0a", type);
  CHECK(context.get_scope_size(0) == 1 * WORD_BYTES);
  context.register_chunk("scope0b", type);
  CHECK(context.get_scope_size(0) == 2 * WORD_BYTES);
  context.new_scope();
  context.register_chunk("scope1", type);
  context.new_scope();
  context.new_scope();
  context.register_chunk("scope3a", type);
  context.register_chunk("scope3b", type);
  CHECK(context.get_scope_size(0) == 2 * WORD_BYTES);
  CHECK(context.get_scope_size(1) == 1 * WORD_BYTES);
  CHECK(context.get_scope_size(2) == 0 * WORD_BYTES);
  CHECK(context.get_scope_size(3) == 2 * WORD_BYTES);
}
