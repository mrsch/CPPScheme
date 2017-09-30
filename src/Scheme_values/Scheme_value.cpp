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
  explicit Eval_visitor(const std::shared_ptr<Environment>& env,
                        const List& args)
    : env(env), args(args){};

  template <typename T>
  Eval_result operator()(T value) const
  {
    return value.eval(env);
  }

private:
  const std::shared_ptr<Environment>& env;
  List args;
};

Scheme_value::Scheme_value(Value value) : value(value)
{
}

std::string Scheme_value::as_string() const
{
  return std::visit(Print_visitor{}, value);
}

Eval_result Scheme_value::eval(const std::shared_ptr<Environment>& env) const
{
  return std::visit(Eval_visitor(env), value);
}

Eval_result Scheme_value::eval(const std::shared_ptr<Environment>& env,
                               List args) const
{
  return std::visit(Eval_visitor(env, args), value);
}
