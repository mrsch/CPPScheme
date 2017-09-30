#ifndef SCHEME_VALUES_NUMBER_HPP
#define SCHEME_VALUES_NUMBER_HPP

#include "Utils.hpp"
#include <memory>
#include <string>

class Scheme_value;
class Environment;

class Number
{
public:
  explicit Number(float number);

  std::string as_string() const;
  Eval_result eval(const Env_ptr& env);

  float get_number() const
  {
    return number;
  }

private:
  float number;
};

#endif // SCHEME_VALUES_NUMBER_HPP
