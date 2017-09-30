#ifndef SCHEME_VALUES_NIL_HPP
#define SCHEME_VALUES_NIL_HPP

#include "Utils.hpp"
#include <memory>
#include <string>

class Scheme_value;
class Environment;

class Nil
{
public:
  Nil();

  std::string as_string();
  Maybe<Scheme_value> eval(const Env_ptr& env);
};

#endif // SCHEME_VALUES_NIL_HPP
