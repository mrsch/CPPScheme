#include "Scheme_values/List.hpp"

#include "Environment.hpp"
#include "Parser.hpp"
#include "Scheme_values/Scheme_value.hpp"
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <range/v3/view.hpp>

using namespace ranges;

List::List(const std::deque<Scheme_ptr>& list) : list(list)
{
}

std::string List::as_string() const
{
  if (list.size() == 0) {
    return "()";
  }

  std::string res = "(";
  for (auto& e : list) {
    res += e->as_string() + " ";
  }
  res.erase(res.length() - 1, 1);
  res += ")";

  return res;
}

Eval_result List::eval_list(const std::shared_ptr<Environment>& env) const
{
  if (list.size() == 0) { // Empty list, return ()
    return std::make_shared<Scheme_value>(List());
  }

  if (auto maybe_atom = list[0]->get<Symbol>()) { // First check special forms
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
  auto first = eval(list[0], env);
  auto list_view = list | view::drop(1);

  if (!first) {
    return fmt::format("Could not evaluate expression: {}\nMessage: {}",
                       as_string(),
                       first.error());
  }

  if (auto maybe_builtin = (*first)->get<Built_in>()) {
    auto builtin = *maybe_builtin;
    return builtin.execute(env, list_view);
  } else if (auto maybe_lambda = (*first)->get<Lambda>()) {
    auto lambda = *maybe_lambda;
    return lambda.execute(env, list_view);
  }

  return fmt::format("Could not evaluate expression: {}", as_string());
}

const std::deque<Scheme_ptr>& List::get_list() const
{
  return list;
}

Eval_result List::eval_special_forms(const Symbol& atom,
                                     const Env_ptr& env) const
{
  // Primitive Expressions
  if (atom.as_string() == "define") {
    if (list.size() != 3) {
      return fmt::format(
        "define requires exactly 2 arguments, {} given in Expression: {}",
        list.size(),
        as_string());
    }

    if (auto atom = list[1]->get<Symbol>()) {
      auto result = eval(list[2], env);
      if (!result) {
        return result;
      } else {
        env->add_to_env(atom->as_string(), *result);
        return list[1];
      }
    } else if (auto func_definition =
                 list[1]->get<List>()) { // Lambda definition
      auto definition_list = func_definition->get_list();
      auto func_name = definition_list[0];
      std::deque<Scheme_ptr> params;
      for (size_t i = 1; i < definition_list.size(); ++i) {
        params.push_back(definition_list[i]);
      }

      std::deque<Scheme_ptr> body_expressions;
      for (size_t i = 2; i < list.size(); ++i) {
        body_expressions.emplace_back(list[i]);
      }

      env->add_to_env(func_name->as_string(),
                      std::make_shared<Scheme_value>(
                        Lambda(List(params), body_expressions, env)));

      return func_name;

    } else {
      return fmt::format("Invalid define syntax: {}", as_string());
    }
  } else if (atom.as_string() == "quote") {
    return Scheme_ptr{list[1]};
  } else if (atom.as_string() == "lambda") {
    std::deque<Scheme_ptr> body_expressions;
    for (size_t i = 2; i < list.size(); ++i) {
      body_expressions.emplace_back(list[i]);
    }

    return std::make_shared<Scheme_value>(
      Lambda(list[1]->get<List>().value(), body_expressions, env));
  } else if (atom.as_string() == "if") {
    auto cond = eval(list[1], env);
    if (!cond) {
      // TODO: Handle error
    }

    Scheme_bool b((*cond));
    if (b.get_bool()) {
      return eval(list[2], env);
    } else {
      return eval(list[3], env);
    }
  } else if (atom.as_string() == "cond") {
    auto list_view = list | view::drop(1);
    for (auto& maybe_clause : list_view) {
      auto clause = maybe_clause->get<List>().value();
      auto clause_list = clause.get_list();
      auto cond = clause_list.front();
      clause_list.pop_front();

      if (auto atom = cond->get<Symbol>()) {
        if (atom->as_string() == "else") {
          return eval_expressions(clause_list, env);
        }
      } else if (auto result = eval(cond, env)) {
        if ((*result)->get<Scheme_bool>()->get_bool()) {
          return eval_expressions(clause_list, env);
        }
      }
    }
  } else if (atom.as_string() == "case") {
    if (auto key = eval(list[1], env)) {
      auto list_view = list | view::drop(2);
      for (auto& maybe_clause : list_view) {
        auto clause = maybe_clause->get<List>().value();
        auto clause_list = clause.get_list();

        if (auto atom = clause_list.front()->get<Symbol>()) {
          clause_list.pop_front();
          if (atom->as_string() == "else") {
            return eval_expressions(clause_list, env);
          }
        }

        if (auto objects = clause_list.front()->get<List>()) {
          clause_list.pop_front();
          for (auto& object : objects->get_list()) {
            if ((*key)->as_string() == object->as_string()) { // FIXME: Use eqv?
              return eval_expressions(clause_list, env);
            }
          }
        };
      }
    } else {
      return fmt::format("Invalid first argument to case: {} ", key.error());
    }

  } else if (atom.as_string() == "set!") {
    auto atom_name = list[1]->as_string();
    if (env->get(list[1]->as_string())) {
      auto res = eval(list[2], env);
      if (res) {
        env->add_to_env(atom_name, *res);
      } else {
        // TODO: handle_error
      }

      return list[1];
    } else {
      fmt::print("Unbound varable: {}\n", list[1]->as_string());
      return Scheme_ptr{};
    }
  } else if (atom.as_string() == "and") {
    if (list.size() == 1) {
      return std::make_shared<Scheme_value>(Scheme_bool(true));
    } else {
      auto list_view = list | view::drop(1);
      Eval_result res;
      for (auto& test : list_view) {
        if ((res = eval(test, env))) {
          Scheme_bool b(res->get());
          if (!b.get_bool()) {
            return std::make_shared<Scheme_value>(b);
          }
        }
      }
      return res;
    }
  } else if (atom.as_string() == "or") {
    if (list.size() == 1) {
      return std::make_shared<Scheme_value>(Scheme_bool(false));
    } else {
      auto list_view = list | view::drop(1);
      Eval_result res;
      for (auto& test : list_view) {
        if ((res = eval(test, env))) {
          Scheme_bool b(res->get());
          if (b.get_bool()) {
            return std::make_shared<Scheme_value>(b);
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

    if (auto bindings = list[1]->get<List>()) {
      Env_ptr let_env = std::make_shared<Environment>(env);
      for (auto& binding : bindings->get_list()) {
        if (bindings->get_list().size() != 2) {
          // TODO: Return useful message
          return std::string("Error in binding list");
        }

        // FIXME: Error handling
        auto var_list = binding->get<List>()->get_list();
        let_env->add_to_env(var_list[0]->as_string(),
                            *(eval(var_list[1], env)));
      }

      auto list_view = list | view::drop(2);
      return eval_expressions(list_view, let_env);

    } else {
      return fmt::format("First parameter for let must be a List");
    }

  } else if (atom.as_string() == "begin") {
    auto list_view = list | view::drop(1);
    return eval_expressions(list_view, env);
  } else if (atom.as_string() == "load") {
    // load has to be here because it
    // has to be executed in the root
    // Environment
    std::ifstream source;

    source.open(list[1]->get<String>().value().get_string(), std::ios::in);

    if (source.is_open()) {
      std::string program((std::istreambuf_iterator<char>(source)),
                          std::istreambuf_iterator<char>());

      while (program.size() != 0) {
        auto res = eval(parse(program), env);
        if (!res) {
          return res;
        }
      }
    }

    return Scheme_ptr();
  }

  return {std::string("")};
}

Eval_result List::eval_expressions(const std::deque<Scheme_ptr>& expr_list,
                                   const Env_ptr& env) const
{
  Eval_result res;
  for (size_t i = 0; i < expr_list.size(); ++i) {
    res = eval(expr_list[i], env);
  }
  return res;
}
