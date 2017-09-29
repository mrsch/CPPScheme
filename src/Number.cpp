#include "Scheme_values/Number.hpp"

#include "Environment.hpp"
#include "Scheme_value.hpp"

Number::Number(int number) : number(number)
{
}

std::string Number::as_string() const
{
  return std::to_string(number);
}

Scheme_value Number::eval(const std::shared_ptr<Environment>& /* env */)
{
  return Scheme_value{*this};
}
