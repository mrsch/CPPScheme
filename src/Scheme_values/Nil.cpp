#include "Scheme_values/Nil.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

#include <memory>

Nil::Nil()
{
}

std::string Nil::as_string() const
{
  return "nil";
}
