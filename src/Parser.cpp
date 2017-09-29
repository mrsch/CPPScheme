#include "Parser.hpp"

#include "Scheme_values/Scheme_value.hpp"
#include "Utils.hpp"

#include <any>
#include <iostream>
#include <optional>

static std::string symbols = "!$%&|*+-./:<=>?@^_~";

bool is_symbol(char c)
{
  return symbols.find(c) != std::string::npos;
}

Scheme_value parse(std::string& expr)
{
  while (expr.size() != 0) {
    trim(expr);

    if (auto res = parse_atom(expr); res.has_value()) {
      return Scheme_value(res.value());
    } else if (auto res = parse_number(expr); res.has_value()) {
      return Scheme_value(res.value());
    } else if (auto res = parse_string(expr); res.has_value()) {
      return Scheme_value(res.value());
    } else if (auto res = parse_character(expr); res.has_value()) {
      return Scheme_value(res.value());
    } else if (auto res = parse_list(expr); res.has_value()) {
      return Scheme_value(res.value());
    } else if (auto res = parse_specials(expr); res.has_value()) {
      return Scheme_value(res.value());
    } else if (auto res = parse_bool(expr); res.has_value()) {
      return Scheme_value(res.value());
    } else {
      parse_comment(expr);
    }
  }

  return Scheme_value();
}

std::optional<List> parse_specials(std::string& expr)
{
  if (expr[0] == '\'') {
    expr.erase(0, 1);
    std::vector<Scheme_value> list;
    list.emplace_back(Scheme_value(Atom("quote")));
    list.emplace_back(Scheme_value(parse(expr)));

    return List(list);
  }

  return {};
}

std::optional<List> parse_list(std::string& expr)
{
  if (expr[0] == '(') {
    expr.erase(0, 1);
    std::vector<Scheme_value> list;
    while (expr[0] != ')') {
      list.emplace_back(Scheme_value(parse(expr)));
    }
    expr.erase(0, 1);
    trim(expr);

    return List(list);
  }

  return {};
}

std::optional<Atom> parse_atom(std::string& expr)
{
  if (std::isalpha(expr[0]) || is_symbol(expr[0])) {
    return Atom(substr_and_remove(expr, expr.find_first_of(" )")));
  } else {
    return {};
  }
}

std::optional<Character> parse_character(std::string& expr)
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

std::optional<Bool> parse_bool(std::string& expr)
{
  if (expr.find("#f") == 0) {
    expr.erase(0, 2);
    trim(expr);
    return Bool(false);
  } else if (expr.find("#t") == 0) {
    expr.erase(0, 2);
    trim(expr);
    return Bool(true);
  } else {
    return {};
  }
}

// FIXME: Handle escaped characters e.g. \"
std::optional<String> parse_string(std::string& expr)
{
  if (expr[0] == '"') {
    expr.erase(0, 1);
    auto pos = expr.find_first_of('"');
    expr.erase(pos, 1);
    return String(substr_and_remove(expr, pos));
  }

  return {};
}

// FIXME: More number types (hex oct float ...)
std::optional<Number> parse_number(std::string& expr)
{
  if (std::isdigit(expr[0])) {
    return Number(std::stoi(substr_and_remove(expr, expr.find_first_of(" )"))));
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
