#include "Scheme_values/Bool.hpp"

#include "Environment.hpp"
#include "Scheme_value.hpp"

Bool::Bool(bool b) : b(b)
{
}

Scheme_value Bool::eval(const std::shared_ptr<Environment>& /* env */)
{
  return Scheme_value{*this};
}

std::string Bool::as_string()
{
  return b ? "#t" : "#f";
}
