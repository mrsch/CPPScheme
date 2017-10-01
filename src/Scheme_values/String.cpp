#include "Scheme_values/String.hpp"

#include "Scheme_values/Scheme_value.hpp"

String::String(const std::string& str) : str(str)
{
}

std::string String::as_string() const
{
  return "\"" + str + "\"";
}

std::string String::get_string() const
{
  return str;
}
