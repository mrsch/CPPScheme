#ifndef SCHEME_VALUES_CHARACTER_HPP
#define SCHEME_VALUES_CHARACTER_HPP

#include "Utils.hpp"
#include <memory>
#include <string>

class Scheme_value;
class Environment;

class Character
{
public:
  explicit Character(char c);

  std::string as_string() const;

private:
  char value;
};

#endif // SCHEME_VALUES_CHARACTER_HPP
