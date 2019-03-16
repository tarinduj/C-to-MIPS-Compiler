#define CATCH_CONFIG_MAIN

#include "catch.hpp"
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
  context.register_type("type1",
                        std::shared_ptr<PrimitiveType>(new PrimitiveType()));
  auto type = context.resolve_type("type1");
  REQUIRE(type->get_type_category() == Type::PRIMITIVE);
  REQUIRE(type->get_primitive_type() == Type::INT);
}