#ifndef SCHEME_VALUES_STRING_HPP
#define SCHEME_VALUES_STRING_HPP

#include <memory>
#include <string>

class Scheme_value;
class Environment;

class String
{
public:
  explicit String(const std::string& str);

  std::string as_string() const;
  Scheme_value eval(const std::shared_ptr<Environment>& env);

  std::string get_string() const;

private:
  std::string str;
};

#endif // SCHEME_VALUES_STRING_HPP
