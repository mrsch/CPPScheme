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
  explicit Vector(const std::deque<Scheme_ptr>& vector);

  std::string as_string() const;

  const std::deque<Scheme_ptr>& get_vector() const;

private:
  std::deque<Scheme_ptr> vector;
};

#endif // SCHEME_VALUES_VECTOR_HPP
