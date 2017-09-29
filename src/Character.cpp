#include "Scheme_values/Character.hpp"

#include "Environment.hpp"
#include "Scheme_value.hpp"

Character::Character(char c) : value(c)
{
}

std::string Character::as_string() const
{
  return std::string(1, value);
}

Scheme_value Character::eval(Environment& /* env */)
{
  return Scheme_value{*this};
}
