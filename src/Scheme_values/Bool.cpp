#include "Scheme_values/Bool.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

Bool::Bool(bool b) : b(b)
{
}

Scheme_value Bool::eval(const Env_ptr& /* env */)
{
  return Scheme_value{*this};
}

std::string Bool::as_string()
{
  return b ? "#t" : "#f";
}

bool Bool::get_bool() const
{
  return b;
}
