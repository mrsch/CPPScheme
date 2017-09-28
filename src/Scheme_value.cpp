#include "Scheme_value.hpp"

#include <iostream>

struct Print_visitor {
  template <typename T>
  std::string operator()(T value) const
  {
    return value.as_string();
  }
};

Scheme_value::Scheme_value(Value value) : value(value)
{
}

std::string Scheme_value::as_string()
{
  return std::visit(Print_visitor{}, value);
}
