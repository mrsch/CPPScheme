#ifndef SCHEME_VALUES_BOOL_HPP
#define SCHEME_VALUES_BOOL_HPP

#include <memory>
#include <string>

class Scheme_value;
class Environment;

class Bool
{
public:
  explicit Bool(bool b);

  std::string as_string();
  Scheme_value eval(const std::shared_ptr<Environment>& env);

  bool get_bool() const;

private:
  bool b;
};

#endif // SCHEME_VALUES_BOOL_HPP
