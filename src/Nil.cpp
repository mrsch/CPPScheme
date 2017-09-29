#include "Scheme_values/Nil.hpp"

#include "Environment.hpp"
#include "Scheme_value.hpp"

#include <memory>

Nil::Nil()
{
}

Scheme_value Nil::eval(const std::shared_ptr<Environment>& /* env */)
{
  return Scheme_value{*this};
}

std::string Nil::as_string()
{
  return "nil";
}
