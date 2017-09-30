#include "Scheme_values/Scheme_value.hpp"

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
  explicit Eval_visitor(const std::shared_ptr<Environment>& env) : env(env){};

  template <typename T>
  Maybe<Scheme_value> operator()(T value) const
  {
    return value.eval(env);
  }

private:
  const std::shared_ptr<Environment>& env;
};

Scheme_value::Scheme_value(Value value) : value(value)
{
}

std::string Scheme_value::as_string() const
{
  return std::visit(Print_visitor{}, value);
}

Maybe<Scheme_value>
Scheme_value::eval(const std::shared_ptr<Environment>& env) const
{
  return std::visit(Eval_visitor(env), value);
}
