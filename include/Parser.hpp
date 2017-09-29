#ifndef PARSER_HPP
#define PARSER_HPP

#include "Scheme_values/Atom.hpp"
#include "Scheme_values/Bool.hpp"
#include "Scheme_values/Character.hpp"
#include "Scheme_values/List.hpp"
#include "Scheme_values/Number.hpp"
#include "Scheme_values/String.hpp"
#include "Scheme_values/Vector.hpp"

#include <optional>
#include <string>

Scheme_value parse(std::string& expr);

std::optional<Atom> parse_atom(std::string& expr);
std::optional<Bool> parse_bool(std::string& expr);
std::optional<Character> parse_character(std::string& expr);
std::optional<String> parse_string(std::string& expr);
std::optional<List> parse_list(std::string& expr);
std::optional<List> parse_specials(std::string& expr);
std::optional<Number> parse_number(std::string& expr);
std::optional<Vector> parse_vector(std::string& expr);
void parse_comment(std::string& expr);

#endif // PARSER_HPP
