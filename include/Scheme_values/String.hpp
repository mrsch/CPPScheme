#ifndef SCHEME_VALUES_STRING_HPP
#define SCHEME_VALUES_STRING_HPP

#include <string>

class Scheme_value;
class Environment;

class String
{
public:
  explicit String(const std::string& str);

  std::string as_string() const;
  Scheme_value eval(Environment& env);

private:
  std::string str;
};

#endif // SCHEME_VALUES_STRING_HPP
