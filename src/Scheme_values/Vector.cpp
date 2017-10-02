#include "Scheme_values/Vector.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

Vector::Vector(const std::deque<Scheme_ptr>& vector) : vector(vector)
{
}

std::string Vector::as_string() const
{
  std::string res = "#(";
  for (auto& e : vector) {
    res += e->as_string() + " ";
  }
  res.erase(res.length() - 1, 1);
  res += ")";

  return res;
}
const std::deque<Scheme_ptr>& Vector::get_vector() const
{
  return vector;
}
