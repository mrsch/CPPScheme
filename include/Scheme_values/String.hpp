#ifndef SCHEME_VALUES_STRING_HPP
#define SCHEME_VALUES_STRING_HPP

#include "Utils.hpp"

#include <memory>
#include <string>

class Scheme_value;
class Environment;

class String
{
public:
  explicit String(const std::string& str);

  std::string as_string() const;
  Eval_result eval(const Env_ptr& env);

  std::string get_string() const;

private:
  std::string str;
};

#endif // SCHEME_VALUES_STRING_HPP
