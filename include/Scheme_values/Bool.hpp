#ifndef SCHEME_VALUES_BOOL_HPP
#define SCHEME_VALUES_BOOL_HPP

#include <string>

class Scheme_value;
class Environment;

class Bool
{
public:
  explicit Bool(bool b);

  std::string as_string();
  Scheme_value eval(Environment& env);

private:
  bool b;
};

#endif // SCHEME_VALUES_BOOL_HPP
