#include "Scheme_values/Vector.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

Vector::Vector(const std::vector<Scheme_value>& vector) : vector(vector)
{
}

std::string Vector::as_string()
{
  std::string res = "#(";
  for (auto& e : vector) {
    res += e.as_string() + " ";
  }
  res.erase(res.length() - 1, 1);
  res += ")";

  return res;
}

Maybe<Scheme_value> Vector::eval(const std::shared_ptr<Environment>& env)
{
  return Scheme_value{*this};
}

const std::vector<Scheme_value>& Vector::get_vector() const
{
  return vector;
}
