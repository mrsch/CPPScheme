#include "Scheme_values/Nil.hpp"

#include "Environment.hpp"
#include "Scheme_value.hpp"

Nil::Nil()
{
}

Scheme_value Nil::eval(Environment& /* env */)
{
  return Scheme_value{*this};
}

std::string Nil::as_string()
{
  return "nil";
}
