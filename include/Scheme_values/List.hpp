#ifndef SCHEME_VALUES_LIST_HPP
#define SCHEME_VALUES_LIST_HPP

#include "Scheme_values/Atom.hpp"
#include "Scheme_values/String.hpp"
#include <memory>
#include <variant>
#include <vector>

class Scheme_value;
class Environment;

class List
{
public:
  explicit List(const std::vector<Scheme_value>& list);

  std::string as_string();
  Scheme_value eval(const std::shared_ptr<Environment>& env);

  const std::vector<Scheme_value>& get_list() const;

private:
  std::vector<Scheme_value> list;
};

#endif // SCHEME_VALUES_LIST_HPP
