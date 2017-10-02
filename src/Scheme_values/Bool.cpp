#include "Scheme_values/Bool.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

Scheme_bool::Scheme_bool(bool b) : b(b)
{
}

Scheme_bool::Scheme_bool(const Scheme_ptr& val)
{
  b = true;
  if (auto res = val->get<Scheme_bool>()) {
    b = res->get_bool();
  }
}

std::string Scheme_bool::as_string() const
{
  return b ? "#t" : "#f";
}

bool Scheme_bool::get_bool() const
{
  return b;
}
