#include "Scheme_values/List.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"
#include <fmt/format.h>

List::List(const std::vector<Scheme_value>& list) : list(list)
{
}

std::string List::as_string()
{
  if (list.size() == 0) {
    return "()";
  }

  std::string res = "(";
  for (auto& e : list) {
    res += e.as_string() + " ";
  }
  res.erase(res.length() - 1, 1);
  res += ")";

  return res;
}

// Special Forms:
// - define
// - if
// - quote
// - set!
// - lambda
Scheme_value List::eval(const std::shared_ptr<Environment>& env)
{
  if (list.size() == 0) {
    return Scheme_value{*this};
  }

  // Get first element in list
  auto first = list[0];

  if (auto maybe_atom = first.get_value<Atom>(); maybe_atom.has_value()) {
    auto atom = maybe_atom.value();

    // Primitive Expressions
    if (atom.as_string() == "define") {
      if (auto atom = list[1].get_value<Atom>(); atom.has_value()) {
        env->add_to_env(atom.value().as_string(), list[2].eval(env));
        return Scheme_value{atom.value()};
      } else { // Lambda definition
        auto func_definition = list[1].get_value<List>().value();
        auto func_name = func_definition.get_list()[0].as_string();

        std::vector<Scheme_value> params;
        for (size_t i = 1; i < func_definition.get_list().size(); ++i) {
          params.push_back(func_definition.get_list()[i]);
        }

        std::vector<Scheme_value> body_expressions;
        for (size_t i = 2; i < list.size(); ++i) {
          body_expressions.emplace_back(list[i]);
        }

        env->add_to_env(
          func_name, Scheme_value{Lambda(List(params), body_expressions, env)});

        return func_definition.get_list()[0];
      }
    } else if (atom.as_string() == "quote") {
      return Scheme_value{list[1]};
    } else if (atom.as_string() == "lambda") {
      std::vector<Scheme_value> body_expressions;
      for (size_t i = 2; i < list.size(); ++i) {
        body_expressions.emplace_back(list[i]);
      }

      return Scheme_value{
        Lambda(list[1].get_value<List>().value(), body_expressions, env)};
    } else if (atom.as_string() == "if") {
      auto cond = list[1].eval(env);
      auto value = true;
      if (auto b = cond.get_value<Bool>(); b.has_value()) {
        value = b.value().get_bool();
      }

      if (value) {
        return list[2].eval(env);
      } else {
        return list[3].eval(env);
      }

    } else if (atom.as_string() == "set!") {
      if (env->get(list[1].as_string()).has_value()) {
        env->add_to_env(list[1].get_value<Atom>().value().as_string(),
                        list[2].eval(env));

        return Scheme_value{list[1]};
      } else {
        fmt::print("Unbound varable: {}\n", list[1].as_string());
        return Scheme_value{};
      }
    } else if (auto maybe_procedure = env->get(atom.as_string());
               maybe_procedure.has_value()) {
      auto procedure = maybe_procedure.value();
      list.erase(list.begin());

      if (auto lambda = procedure.get_value<Lambda>(); lambda.has_value()) {
        return lambda.value().execute(env, *this);
      } else if (auto built_in = procedure.get_value<Built_in>();
                 built_in.has_value()) {
        return built_in.value().execute(env, *this);
      }
    }
  }
  return Scheme_value{};
}

const std::vector<Scheme_value>& List::get_list() const
{
  return list;
}
