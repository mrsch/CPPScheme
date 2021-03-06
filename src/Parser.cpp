#include "Parser.hpp"

#include "Scheme_values/Scheme_value.hpp"
#include "Utils.hpp"

#include <any>
#include <iostream>
#include <optional>

static std::string symbols = "!$%&|*.+-/:<=>?@^_~";

bool is_symbol(char c)
{
  return symbols.find(c) != std::string::npos;
}

Scheme_ptr parse(std::string& expr)
{
  while (expr.size() != 0) {
    trim(expr);

    if (auto res = parse_number(expr)) {
      return std::make_shared<Scheme_value>(*res);
    } else if (auto res = parse_atom(expr)) {
      return std::make_shared<Scheme_value>(*res);
    } else if (auto res = parse_vector(expr)) {
      return std::make_shared<Scheme_value>(*res);
    } else if (auto res = parse_string(expr)) {
      return std::make_shared<Scheme_value>(*res);
    } else if (auto res = parse_character(expr)) {
      return std::make_shared<Scheme_value>(*res);
    } else if (auto res = parse_list(expr)) {
      return std::make_shared<Scheme_value>(*res);
    } else if (auto res = parse_specials(expr)) {
      return std::make_shared<Scheme_value>(*res);
    } else if (auto res = parse_bool(expr)) {
      return std::make_shared<Scheme_value>(*res);
    } else {
      parse_comment(expr);
    }
  }

  return Scheme_ptr();
}

Maybe<List> parse_specials(std::string& expr)
{
  if (expr[0] == '\'') {
    expr.erase(0, 1);
    std::deque<Scheme_ptr> list;
    list.emplace_back(std::make_shared<Scheme_value>(Symbol("quote")));
    list.emplace_back(parse(expr));

    return List(list);
  }

  return {};
}

Maybe<List> parse_list(std::string& expr)
{
  if (expr[0] == '(') {
    expr.erase(0, 1);
    std::deque<Scheme_ptr> list;
    while (expr[0] != ')') {
      list.emplace_back(Scheme_ptr(parse(expr)));
    }
    expr.erase(0, 1);
    trim(expr);

    return List(list);
  }

  return {};
}

Maybe<Vector> parse_vector(std::string& expr)
{
  if (expr[0] == '#' && expr[1] == '(') {
    expr.erase(0, 2);
    std::deque<Scheme_ptr> vector;
    while (expr[0] != ')') {
      vector.emplace_back(Scheme_ptr(parse(expr)));
    }
    expr.erase(0, 1);
    trim(expr);

    return Vector(vector);
  }

  return {};
}

Maybe<Symbol> parse_atom(std::string& expr)
{
  if (std::isalpha(expr[0]) || is_symbol(expr[0])) {
    return Symbol(substr_and_remove(expr, expr.find_first_of(" )\n")));
  } else {
    return {};
  }
}

Maybe<Character> parse_character(std::string& expr)
{
  if (expr.find("#\\space") == 0) {
    expr.erase(0, 7);
    trim(expr);
    return Character(' ');
  } else if (expr.find("#\\newline") == 0) {
    expr.erase(0, 9);
    trim(expr);
    return Character('\n');
  } else if (expr.find("#\\") == 0) {
    expr.erase(0, 2);
    return Character(substr_and_remove(expr, 1)[0]);
  } else {
    return {};
  }
}

Maybe<Scheme_bool> parse_bool(std::string& expr)
{
  if (expr.find("#f") == 0) {
    expr.erase(0, 2);
    trim(expr);
    return Scheme_bool(false);
  } else if (expr.find("#t") == 0) {
    expr.erase(0, 2);
    trim(expr);
    return Scheme_bool(true);
  } else {
    return {};
  }
}

Maybe<String> parse_string(std::string& expr)
{
  if (expr.find("\"") == 0) {
    expr.erase(0, 1);
    auto pos = expr.find("\"");
    expr.erase(pos, 1);
    return String(substr_and_remove(expr, pos));
  }

  return {};
}

// FIXME: More number types (hex oct float ...)
Maybe<Number> parse_number(std::string& expr)
{
  if (std::isdigit(expr[0])
      || ((expr[0] == '+' || expr[0] == '-') && std::isdigit(expr[1]))) {
    return Number(std::stof(substr_and_remove(expr, expr.find_first_of(" )"))));
  } else {
    return {};
  }
}

void parse_comment(std::string& expr)
{
  if (expr[0] == ';') {
    expr.erase(0, expr.find('\n'));
  }
}
