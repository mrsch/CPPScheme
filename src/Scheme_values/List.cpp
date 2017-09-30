#include "Scheme_values/List.hpp"

#include "Environment.hpp"
#include "Parser.hpp"
#include "Scheme_values/Scheme_value.hpp"
#include <fmt/format.h>
#include <fstream>

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

Maybe<Scheme_value> List::eval(const std::shared_ptr<Environment>& env)
{
  if (list.size() == 0) { // Empty list return ()
    return Scheme_value{*this};
  }

  if (auto maybe_atom = list[0].get_value<Atom>();
      maybe_atom.has_value()) { // Special Form
    auto maybe = eval_special_forms(maybe_atom.value(), env);
    if (maybe.has_value()) {
      return maybe.value();
    }
  }

  // No Special syntax. Check for bindings
  auto first = list[0].eval(env);

  if (auto maybe_builtin = first.value().get_value<Built_in>();
      maybe_builtin.has_value()) {
    auto builtin = maybe_builtin.value();
    list.erase(list.begin());
    return builtin.execute(env, *this);
  } else if (auto maybe_lambda = first.value().get_value<Lambda>();
             maybe_lambda.has_value()) {
    auto lambda = maybe_lambda.value();
    list.erase(list.begin());
    return lambda.execute(env, *this);
  }

  return Scheme_value{};
}

const std::vector<Scheme_value>& List::get_list() const
{
  return list;
}

Maybe<Scheme_value> List::eval_special_forms(Atom atom, const Env_ptr& env)
{
  // Primitive Expressions
  if (atom.as_string() == "define") {
    if (auto atom = list[1].get_value<Atom>(); atom.has_value()) {
      env->add_to_env(atom.value().as_string(), list[2].eval(env).value());
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
    if (auto b = cond.value().get_value<Bool>(); b.has_value()) {
      value = b.value().get_bool();
    }

    if (value) {
      return list[2].eval(env);
    } else {
      return list[3].eval(env);
    }

  } else if (atom.as_string() == "cond") {
    list.erase(list.begin());
    for (auto& maybe_clause : list) {
      auto clause = maybe_clause.get_value<List>().value();
      auto clause_list = clause.get_list();
      auto cond = clause_list[0];

      bool eval_expressions = false;
      if (auto atom = cond.get_value<Atom>(); atom.has_value()) {
        if (atom.value().as_string() == "else") {
          eval_expressions = true;
        }
      } else if (cond.eval(env).value().get_value<Bool>().value().get_bool()) {
        eval_expressions = true;
      }

      if (eval_expressions) {
        Maybe<Scheme_value> res;
        for (int i = 1; i < clause_list.size(); ++i) {
          res = clause_list[i].eval(env);
        }

        return res;
      }
    }
  } else if (atom.as_string() == "set!") {
    if (env->get(list[1].as_string()).has_value()) {
      env->add_to_env(list[1].get_value<Atom>().value().as_string(),
                      list[2].eval(env).value());

      return Scheme_value{list[1]};
    } else {
      fmt::print("Unbound varable: {}\n", list[1].as_string());
      return Scheme_value{};
    }
  } else if (atom.as_string() == "load") { // load has to be here because it
                                           // has to be executed in the root
                                           // Environment
    std::ifstream source;

    source.open(list[1].get_value<String>().value().get_string(), std::ios::in);

    if (source.is_open()) {
      std::string program((std::istreambuf_iterator<char>(source)),
                          std::istreambuf_iterator<char>());

      while (program.size() != 0) {
        parse(program).eval(env);
      }
    }

    return Scheme_value();
  }

  return {};
}
