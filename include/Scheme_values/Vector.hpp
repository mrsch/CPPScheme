#ifndef SCHEME_VALUES_VECTOR_HPP
#define SCHEME_VALUES_VECTOR_HPP

#include "Scheme_values/Atom.hpp"
#include "Scheme_values/String.hpp"
#include "Utils.hpp"
#include <deque>
#include <memory>
#include <variant>

class Scheme_value;
class Environment;

class Vector
{
public:
  explicit Vector(const std::deque<Scheme_value>& vector);

  std::string as_string();
  Eval_result eval(const Env_ptr& env);

  const std::deque<Scheme_value>& get_vector() const;

private:
  std::deque<Scheme_value> vector;
};

#endif // SCHEME_VALUES_VECTOR_HPP
