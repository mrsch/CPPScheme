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
  List() = default;
  explicit List(std::vector<std::unique_ptr<Scheme_value>>& list);

  List(const List&);
  List& operator=(const List&);
  // List(List&&) = default;
  // List& operator=(List&&) = default;

  std::string as_string();
  Scheme_value eval(Environment& env);

  const std::vector<std::unique_ptr<Scheme_value>>& get_list() const;

private:
  std::vector<std::unique_ptr<Scheme_value>> list;
};

#endif // SCHEME_VALUES_LIST_HPP
