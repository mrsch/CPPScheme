#ifndef SCHEME_VALUES_CHARACTER_HPP
#define SCHEME_VALUES_CHARACTER_HPP

#include <string>

class Character
{
public:
  explicit Character(char c) : value(c)
  {
  }

  std::string as_string() const
  {
    return std::to_string(value);
  };

private:
  char value;
};

#endif // SCHEME_VALUES_CHARACTER_HPP
