#ifndef PARSER_HPP
#define PARSER_HPP

#include "Scheme_values/Atom.hpp"
#include "Scheme_values/Bool.hpp"
#include "Scheme_values/Character.hpp"
#include "Scheme_values/List.hpp"
#include "Scheme_values/Number.hpp"
#include "Scheme_values/String.hpp"
#include "Scheme_values/Vector.hpp"
#include "Utils.hpp"

#include <optional>
#include <string>

Scheme_value parse(std::string& expr);

Maybe<Symbol> parse_atom(std::string& expr);
Maybe<Scheme_bool> parse_bool(std::string& expr);
Maybe<Character> parse_character(std::string& expr);
Maybe<String> parse_string(std::string& expr);
Maybe<List> parse_list(std::string& expr);
Maybe<List> parse_specials(std::string& expr);
Maybe<Number> parse_number(std::string& expr);
Maybe<Vector> parse_vector(std::string& expr);
void parse_comment(std::string& expr);

#endif // PARSER_HPP
