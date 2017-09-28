#ifndef SCHEME_VALUE_HPP
#define SCHEME_VALUE_HPP

#include "Scheme_values/Atom.hpp"
#include "Scheme_values/Character.hpp"
#include "Scheme_values/List.hpp"
#include "Scheme_values/Number.hpp"
#include "Scheme_values/String.hpp"

#include <string>
#include <variant>

class Scheme_value
{
  using Value = std::variant<Atom, List, String, Character, Number>;

public:
  explicit Scheme_value(Value value);
  std::string as_string();

private:
  Value value;
};

#endif // SCHEME_VALUE_HPP
