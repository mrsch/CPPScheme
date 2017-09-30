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
  explicit List(const std::vector<Scheme_value>& list);

  std::string as_string();
  Maybe<Scheme_value> eval(const Env_ptr& env);

  const std::vector<Scheme_value>& get_list() const;

private:
  std::vector<Scheme_value> list;

  Maybe<Scheme_value> eval_special_forms(Atom atom, const Env_ptr& env);
};

#endif // SCHEME_VALUES_LIST_HPP
