#include "Scheme_values/String.hpp"

#include "Scheme_values/Scheme_value.hpp"

String::String(const std::string& str) : str(str)
{
}

std::string String::as_string() const
{
  return "\"" + str + "\"";
}

Scheme_value String::eval(const std::shared_ptr<Environment>& /* env */)
{
  return Scheme_value{*this};
}
