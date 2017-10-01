#include "Scheme_values/Bool.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

Scheme_bool::Scheme_bool(bool b) : b(b)
{
}

Scheme_bool::Scheme_bool(Scheme_value val)
{
  b = true;
  if (auto res = val.get<Scheme_bool>()) {
    b = res->get_bool();
  }
}

Eval_result Scheme_bool::eval(const Env_ptr& /* env */)
{
  return Scheme_value{*this};
}

std::string Scheme_bool::as_string()
{
  return b ? "#t" : "#f";
}

bool Scheme_bool::get_bool() const
{
  return b;
}
