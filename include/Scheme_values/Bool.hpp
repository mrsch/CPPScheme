#ifndef SCHEME_VALUES_BOOL_HPP
#define SCHEME_VALUES_BOOL_HPP

#include "Utils.hpp"
#include <memory>
#include <string>

class Scheme_value;
class Environment;

class Scheme_bool
{
public:
  explicit Scheme_bool(bool b);
  explicit Scheme_bool(const Scheme_ptr& val);

  std::string as_string() const;
  bool get_bool() const;

private:
  bool b;
};

#endif // SCHEME_VALUES_BOOL_HPP
