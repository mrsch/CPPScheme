#ifndef SCHEME_VALUES_NUMBER_HPP
#define SCHEME_VALUES_NUMBER_HPP

#include <memory>
#include <string>

class Scheme_value;
class Environment;

class Number
{
public:
  explicit Number(int number);

  std::string as_string() const;
  Scheme_value eval(const std::shared_ptr<Environment>& env);

  int get_number() const
  {
    return number;
  }

private:
  int number;
};

#endif // SCHEME_VALUES_NUMBER_HPP
