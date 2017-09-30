#ifndef SCHEME_VALUES_LIST_HPP
#define SCHEME_VALUES_LIST_HPP

#include "Scheme_values/Atom.hpp"
#include "Scheme_values/String.hpp"
#include "Utils.hpp"
#include <memory>
#include <variant>
#include <vector>

class Scheme_value;
class Environment;

class List
{
public:
  List() = default;
  explicit List(const std::vector<Scheme_value>& list);

  std::string as_string();
  Eval_result eval(const Env_ptr& env);

  const std::vector<Scheme_value>& get_list() const;

private:
  std::vector<Scheme_value> list;

  Eval_result eval_special_forms(const Atom& atom, const Env_ptr& env);
};

#endif // SCHEME_VALUES_LIST_HPP
