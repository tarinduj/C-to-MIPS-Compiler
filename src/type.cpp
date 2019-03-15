#include "type.hpp"
#include "constants.hpp"

unsigned PrimitiveType::get_size() const { return WORD_BYTES; }

Type::Primitive PrimitiveType::get_primitive_type() const { return Type::INT; }

Type::TypeCategory PrimitiveType::get_type_category() const {
  return Type::PRIMITIVE;
}