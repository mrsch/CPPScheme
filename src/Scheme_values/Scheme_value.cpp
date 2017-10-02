#include "Scheme_values/Scheme_value.hpp"

#include "Environment.hpp"

#include <fmt/format.h>
#include <iostream>

struct Print_visitor {
  template <typename T>
  std::string operator()(const T& value) const
  {
    return value.as_string();
  }
};

Scheme_value::Scheme_value(const Value& value) : value(value)
{
}

std::string Scheme_value::as_string() const
{
  return std::visit(Print_visitor{}, value);
}

const Eval_result eval(const Scheme_ptr& scheme,
                       const std::shared_ptr<Environment>& env)
{
  auto& value = scheme->get_value();

  if (std::holds_alternative<Nil>(value)
      || std::holds_alternative<Character>(value)
      || std::holds_alternative<Scheme_bool>(value)
      || std::holds_alternative<Number>(value)
      || std::holds_alternative<String>(value)
      || std::holds_alternative<Vector>(value)) {
    return scheme;
  } else if (std::holds_alternative<Symbol>(value)) {
    auto name = std::get<Symbol>(value).as_string();
    if (auto res = env->get(name)) {
      return *res;
    } else {
      return fmt::format("Unbound variable: {}\n", name);
    }
  } else if (std::holds_alternative<Built_in>(value)) {
    return std::make_shared<Scheme_value>(String("Built-in procedure"));
  } else if (std::holds_alternative<Lambda>(value)) {
    return std::make_shared<Scheme_value>(String("Defined lambda"));
  } else if (std::holds_alternative<List>(value)) {
    return std::get<List>(value).eval_list(env);
  } else {
    return std::string("ERROR: Eval not handled!");
  }
}
