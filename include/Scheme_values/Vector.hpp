#ifndef SCHEME_VALUES_VECTOR_HPP
#define SCHEME_VALUES_VECTOR_HPP

#include "Scheme_values/Atom.hpp"
#include "Scheme_values/String.hpp"
#include "Utils.hpp"
#include <memory>
#include <variant>
#include <vector>

class Scheme_value;
class Environment;

class Vector
{
public:
  explicit Vector(const std::vector<Scheme_value>& vector);

  std::string as_string();
  Scheme_value eval(const Env_ptr& env);

  const std::vector<Scheme_value>& get_vector() const;

private:
  std::vector<Scheme_value> vector;
};

#endif // SCHEME_VALUES_VECTOR_HPP
