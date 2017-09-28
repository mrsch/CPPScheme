#ifndef SCHEME_VALUES_LIST_HPP
#define SCHEME_VALUES_LIST_HPP

#include "Scheme_values/Atom.hpp"
#include "Scheme_values/String.hpp"
#include <memory>
#include <variant>
#include <vector>

class Scheme_value;

class List
{
public:
  List() = default;
  explicit List(std::vector<std::unique_ptr<Scheme_value>>& list);

  List(const List&);
  // List(List&&) = default;
  // List& operator=(const List&) = default;
  // List& operator=(List&&) = default;

  std::string as_string();

private:
  std::vector<std::unique_ptr<Scheme_value>> list;
};

#endif // SCHEME_VALUES_LIST_HPP
