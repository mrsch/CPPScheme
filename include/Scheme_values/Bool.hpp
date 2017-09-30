#ifndef SCHEME_VALUES_BOOL_HPP
#define SCHEME_VALUES_BOOL_HPP

#include "Utils.hpp"
#include <memory>
#include <string>

class Scheme_value;
class Environment;

class Bool
{
public:
  explicit Bool(bool b);

  std::string as_string();
  Eval_result eval(const Env_ptr& env);

  bool get_bool() const;

private:
  bool b;
};

#endif // SCHEME_VALUES_BOOL_HPP
