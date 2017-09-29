#include "Scheme_value.hpp"

#include "Environment.hpp"

#include <iostream>

struct Print_visitor {
  template <typename T>
  std::string operator()(T value) const
  {
    return value.as_string();
  }
};

struct Eval_visitor {
  explicit Eval_visitor(Environment& env) : env(env){};

  template <typename T>
  Scheme_value operator()(T value) const
  {
    return value.eval(env);
  }

private:
  Environment& env;
};

Scheme_value::Scheme_value(Value value) : value(value)
{
}

std::string Scheme_value::as_string() const
{
  return std::visit(Print_visitor{}, value);
}

Scheme_value Scheme_value::eval(Environment& env) const
{
  return std::visit(Eval_visitor(env), value);
}
