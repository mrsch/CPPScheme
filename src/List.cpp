#include "Scheme_values/List.hpp"

#include "Environment.hpp"
#include "Scheme_value.hpp"

List::List(std::vector<std::unique_ptr<Scheme_value>>& list)
  : list(std::move(list))
{
}

List::List(const List& other)
{
  for (auto& e : other.list) {
    list.emplace_back(std::make_unique<Scheme_value>(*e));
  }
}

List& List::operator=(const List& other)
{
  list.clear();
  for (auto& e : other.list) {
    list.emplace_back(std::make_unique<Scheme_value>(*e));
  }
  return *this;
}

std::string List::as_string()
{
  std::string res = "(";
  for (auto& e : list) {
    res += e->as_string() + " ";
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
Scheme_value List::eval(Environment& env)
{
  if (list.size() == 0) {
    return Scheme_value{*this};
  }

  // Get first element in list
  auto first = list[0].get();

  if (auto maybe_atom = first->get_value<Atom>(); maybe_atom.has_value()) {
    auto atom = maybe_atom.value();

    // Primitive Expressions
    if (atom.as_string() == "define") {
      env.add_to_env(list[1]->get_value<Atom>().value().as_string(),
                     list[2]->eval(env));

      return Scheme_value{*list[1].get()};
    } else if (atom.as_string() == "quote") {
      return Scheme_value{*list[1].get()};
    } else if (atom.as_string() == "lambda") {
      std::vector<Scheme_value> body_expressions;
      for (size_t i = 2; i < list.size(); ++i) {
        body_expressions.emplace_back(*list[i]);
      }

      return Scheme_value{
        Lambda(list[1]->get_value<List>().value(), body_expressions, env)};
    } else if (atom.as_string() == "if") { // TODO: Conditional
      return Scheme_value{};
    } else if (atom.as_string() == "set!") { // TODO: assignment
      return Scheme_value{};
    } else if (auto maybe_lambda = env.get(atom.as_string());
               maybe_lambda.has_value()) {
      auto lambda = maybe_lambda.value();
      list.erase(list.begin());
      return lambda.get_value<Lambda>().value().execute(env, *this);
    }

    return Scheme_value{};
  }
}

const std::vector<std::unique_ptr<Scheme_value>>& List::get_list() const
{
  return list;
}
