#ifndef SCHEME_VALUES_NIL_HPP
#define SCHEME_VALUES_NIL_HPP

#include <string>

class Scheme_value;
class Environment;

class Nil
{
public:
  Nil();

  std::string as_string();
  Scheme_value eval(Environment& env);
};

#endif // SCHEME_VALUES_NIL_HPP
