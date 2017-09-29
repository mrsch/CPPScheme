#ifndef SCHEME_VALUES_CHARACTER_HPP
#define SCHEME_VALUES_CHARACTER_HPP

#include <string>

class Scheme_value;
class Environment;

class Character
{
public:
  explicit Character(char c);

  std::string as_string() const;
  Scheme_value eval(Environment& env);

private:
  char value;
};

#endif // SCHEME_VALUES_CHARACTER_HPP
