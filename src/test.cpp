#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "catch.hpp"
#include "constants.hpp"
#include "type.hpp"
#include <memory>

TEST_CASE("Type", "[Type]") {
  TypePtr integer_type = std::make_shared<PrimitiveType>();
  REQUIRE(integer_type->get_size() == WORD_BYTES);
  REQUIRE(integer_type->get_type_category() == Type::PRIMITIVE);
  REQUIRE(integer_type->get_primitive_type() == Type::INT);
}
