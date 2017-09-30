#include "Scheme_values/Nil.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

#include <memory>

Nil::Nil()
{
}

Eval_result Nil::eval(const Env_ptr& /* env */)
{
  return Scheme_value{*this};
}

std::string Nil::as_string()
{
  return "nil";
}
