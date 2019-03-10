#ifndef TYPE_HPP
#define TYPE_HPP

#include <memory>

class Type {
public:
  enum Primitive { INT };
  enum TypeCategory { PRIMITIVE };
  virtual unsigned get_size() const = 0;
  virtual Primitive get_primitive_type() const = 0;
  virtual TypeCategory get_type_category() const = 0;
};

typedef std::shared_ptr<Type> TypePtr;

class PrimitiveType : public Type {
public:
  PrimitiveType();
  virtual unsigned get_size() const override;
  virtual Primitive get_primitive_type() const override;
  virtual TypeCategory get_type_category() const override;
};

#endif