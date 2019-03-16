#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "chunk.hpp"
#include "constants.hpp"
#include "context.hpp"
#include "type.hpp"
#include <memory>

TEST_CASE("Type", "[Type]") {
  TypePtr integer_type = std::make_shared<PrimitiveType>();
  REQUIRE(integer_type->get_size() == WORD_BYTES);
  REQUIRE(integer_type->get_type_category() == Type::PRIMITIVE);
  REQUIRE(integer_type->get_primitive_type() == Type::INT);
}

TEST_CASE("Context type retreival", "[Type][Context]") {
  Context context;
  TypePtr type = context.register_type(
      "type1", std::shared_ptr<PrimitiveType>(new PrimitiveType()));
  REQUIRE(type->get_type_category() == Type::PRIMITIVE);
  REQUIRE(type->get_primitive_type() == Type::INT);
  TypePtr type_2 = context.resolve_type("type1");
  REQUIRE(type_2->get_type_category() == Type::PRIMITIVE);
  REQUIRE(type_2->get_primitive_type() == Type::INT);
}

TEST_CASE("Chunk", "[Chunk][Type]") {
  Context context;
  TypePtr integer_type = std::make_shared<PrimitiveType>();
  ChunkPtr a = context.register_chunk("a", integer_type);
  REQUIRE(a->get_type() == integer_type);
  REQUIRE(a->get_chunk_type() == Chunk::GLOBAL);
  REQUIRE(a->get_offset() == 0);
}

TEST_CASE("Register and resolve Chunk", "[Chunk][Type]") {
  Context context;
  TypePtr integer_type = std::make_shared<PrimitiveType>();
  auto a_1 = context.register_chunk("a", integer_type);
  auto a_2 = context.resolve_chunk("a");
  REQUIRE(a_1 == a_2);
  REQUIRE(a_1->get_type() == integer_type);
  REQUIRE(a_1->get_chunk_type() == Chunk::GLOBAL);
  REQUIRE(a_1->get_offset() == 0);
  auto b_1 = context.register_chunk("b", integer_type);
  auto b_2 = context.resolve_chunk("b");
  REQUIRE(b_1 == b_2);
  REQUIRE(b_1->get_type() == integer_type);
  REQUIRE(b_1->get_chunk_type() == Chunk::GLOBAL);
  REQUIRE(b_1->get_offset() == integer_type->get_size());
}

TEST_CASE("Scoping types", "[Scope][Type]") {
  TypePtr type1 = std::shared_ptr<PrimitiveType>(new PrimitiveType());
  TypePtr type2 = std::shared_ptr<PrimitiveType>(new PrimitiveType());
  TypePtr type3 = std::shared_ptr<PrimitiveType>(new PrimitiveType());
  Context context;
  INFO("Scope 0");
  context.register_type("type", type1);
  REQUIRE(context.resolve_type("type") == type1);
  context.new_scope();
  INFO("Scope 1");
  context.register_type("type", type2);
  REQUIRE(context.resolve_type("type") == type2);
  context.new_scope();
  INFO("Scope 2");
  context.register_type("type", type3);
  REQUIRE(context.resolve_type("type") == type3);
  context.del_scope();
  INFO("Scope 1");
  REQUIRE(context.resolve_type("type") == type2);
  context.del_scope();
  INFO("Scope 0");
  REQUIRE(context.resolve_type("type") == type1);
}