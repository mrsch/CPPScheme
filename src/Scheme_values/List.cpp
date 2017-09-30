#include "Scheme_values/List.hpp"

#include "Environment.hpp"
#include "Parser.hpp"
#include "Scheme_values/Scheme_value.hpp"
#include <fmt/format.h>
#include <fstream>
#include <iostream>

List::List(const std::deque<Scheme_value>& list) : list(list)
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

Eval_result List::eval(const std::shared_ptr<Environment>& env)
{
  if (list.size() == 0) { // Empty list, return ()
    return Scheme_value{*this};
  }

  if (auto maybe_atom =
        list[0].get_value<Atom>()) { // First check special forms
    auto maybe = eval_special_forms(*maybe_atom, env);
    if (maybe) {
      return *maybe;
    } else {
      // Check for error, if error message is empty continue to lambda+builtin
      // evaluation
      if (maybe.error() != "") {
        return fmt::format("Could not evaluate special form: {}\nMessage: {}",
                           as_string(),
                           maybe.error());
      }
    }
  }

  // No Special syntax. Check for lamba/bultin bindings
  auto first = list[0].eval(env);

  if (!first) {
    return fmt::format("Could not evaluate expression: {}\nMessage: {}",
                       as_string(),
                       first.error());
  }

  if (auto maybe_builtin = first->get_value<Built_in>()) {
    auto builtin = *maybe_builtin;
    list.erase(list.begin());
    return builtin.execute(env, *this);
  } else if (auto maybe_lambda = first->get_value<Lambda>()) {
    auto lambda = *maybe_lambda;
    list.erase(list.begin());
    return lambda.execute(env, *this);
  }

  return fmt::format("Could not evaluate expression: {}", as_string());
}

const std::deque<Scheme_value>& List::get_list() const
{
  return list;
}

Eval_result List::eval_special_forms(const Atom& atom, const Env_ptr& env)
{
  // Primitive Expressions
  if (atom.as_string() == "define") {
    if (list.size() != 3) {
      return fmt::format(
        "define requires exactly 2 arguments, {} given in Expression: {}",
        list.size(),
        as_string());
    }

    if (auto atom = list[1].get_value<Atom>()) {
      auto result = list[2].eval(env);
      if (!result) {
        return result;
      } else {
        env->add_to_env(atom->as_string(), *result);
        return Scheme_value{*atom};
      }
    } else if (auto func_definition =
                 list[1].get_value<List>()) { // Lambda definition
      auto definition_list = func_definition->get_list();
      auto func_name = definition_list[0];
      std::deque<Scheme_value> params;
      for (size_t i = 1; i < definition_list.size(); ++i) {
        params.push_back(definition_list[i]);
      }

      std::deque<Scheme_value> body_expressions;
      for (size_t i = 2; i < list.size(); ++i) {
        body_expressions.emplace_back(list[i]);
      }

      env->add_to_env(
        func_name.as_string(),
        Scheme_value{Lambda(List(params), body_expressions, env)});

      return func_name;

    } else {
      return fmt::format("Invalid define syntax: {}", as_string());
    }
  } else if (atom.as_string() == "quote") {
    return Scheme_value{list[1]};
  } else if (atom.as_string() == "lambda") {
    std::deque<Scheme_value> body_expressions;
    for (size_t i = 2; i < list.size(); ++i) {
      body_expressions.emplace_back(list[i]);
    }

    return Scheme_value{
      Lambda(list[1].get_value<List>().value(), body_expressions, env)};
  } else if (atom.as_string() == "if") {
    auto cond = list[1].eval(env);
    if (!cond) {
      // TODO: Handle error
    }

    Bool b(cond);
    if (b.get_bool()) {
      return list[2].eval(env);
    } else {
      return list[3].eval(env);
    }
  } else if (atom.as_string() == "cond") {
    list.erase(list.begin());
    for (auto& maybe_clause : list) {
      auto clause = maybe_clause.get_value<List>().value();
      auto clause_list = clause.get_list();
      auto cond = clause_list.front();
      clause_list.pop_front();

      if (auto atom = cond.get_value<Atom>()) {
        if (atom->as_string() == "else") {
          return eval_expressions(clause_list, env);
        }
      } else if (auto result = cond.eval(env)) {
        if (result->get_value<Bool>()->get_bool()) {
          return eval_expressions(clause_list, env);
        }
      }
    }
  } else if (atom.as_string() == "case") {
    list.erase(list.begin());
    if (auto key = list[0].eval(env)) {
      list.erase(list.begin());
      for (auto& maybe_clause : list) {
        auto clause = maybe_clause.get_value<List>().value();
        auto clause_list = clause.get_list();

        if (auto atom = clause_list.front().get_value<Atom>()) {
          clause_list.pop_front();
          if (atom->as_string() == "else") {
            return eval_expressions(clause_list, env);
          }
        }

        if (auto objects = clause_list.front().get_value<List>()) {
          clause_list.pop_front();
          for (auto& object : objects->get_list()) {
            if (key->as_string() == object.as_string()) { // FIXME: Use eqv?
              return eval_expressions(clause_list, env);
            }
          }
        };
      }
    } else {
      return fmt::format("Invalid first argument to case: {} ", key.error());
    }

  } else if (atom.as_string() == "set!") {
    auto atom_name = list[1].as_string();
    if (env->get(list[1].as_string())) {
      auto res = list[2].eval(env);
      if (res) {
        env->add_to_env(atom_name, *res);
      } else {
        // TODO: handle_error
      }

      return Scheme_value{list[1]};
    } else {
      fmt::print("Unbound varable: {}\n", list[1].as_string());
      return Scheme_value{};
    }
  } else if (atom.as_string() == "and") {
    if (list.size() == 1) {
      return Scheme_value(Bool(true));
    } else {
      list.erase(list.begin());
      Eval_result res;
      for (auto& test : list) {
        if ((res = test.eval(env))) {
          Bool b(*res);
          if (!b.get_bool()) {
            return Scheme_value(b);
          }
        }
      }
      return res;
    }
  } else if (atom.as_string() == "or") {
    if (list.size() == 1) {
      return Scheme_value(Bool(false));
    } else {
      list.erase(list.begin());
      Eval_result res;
      for (auto& test : list) {
        if ((res = test.eval(env))) {
          Bool b(*res);
          if (b.get_bool()) {
            return Scheme_value(b);
          }
        }
      }
      return res;
    }
  } else if (atom.as_string() == "let") {
    if (list.size() < 3) {
      return fmt::format("let requires at least 2 arguments, {} given.",
                         list.size() - 1);
    }

    if (auto bindings = list[1].get_value<List>()) {
      Env_ptr let_env = std::make_shared<Environment>(env);
      for (auto& binding : bindings->get_list()) {
        if (bindings->get_list().size() != 2) {
          // TODO: Return useful message
          return std::string("Error in binding list");
        }

        // FIXME: Error handling
        auto var_list = binding.get_value<List>()->get_list();
        let_env->add_to_env(var_list[0].as_string(), *(var_list[1].eval(env)));
      }

      list.pop_front();
      list.pop_front();
      return eval_expressions(list, let_env);

    } else {
      return fmt::format("First parameter for let must be a List");
    }

  } else if (atom.as_string() == "begin") {
    list.pop_front();
    return eval_expressions(list, env);
  } else if (atom.as_string() == "load") {
    // load has to be here because it
    // has to be executed in the root
    // Environment
    std::ifstream source;

    source.open(list[1].get_value<String>().value().get_string(), std::ios::in);

    if (source.is_open()) {
      std::string program((std::istreambuf_iterator<char>(source)),
                          std::istreambuf_iterator<char>());

      while (program.size() != 0) {
        auto res = parse(program).eval(env);
        if (!res) {
          return res;
        }
      }
    }

    return Scheme_value();
  }

  return {std::string("")};
}

Eval_result List::eval_expressions(const std::deque<Scheme_value>& expr_list,
                                   const Env_ptr& env)
{
  Eval_result res;
  for (size_t i = 0; i < expr_list.size(); ++i) {
    res = expr_list[i].eval(env);
  }
  return res;
}
