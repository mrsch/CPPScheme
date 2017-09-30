#ifndef EITHER_HPP
#define EITHER_HPP

#include <functional>
#include <variant>

template <typename Left, typename Right>
class Either
{
  explicit Either(const std::variant<Left, Right>& val) : val(val)
  {
  }

  Either& left_map(const std::function<Left(Left)>& func)
  {
    if (std::holds_alternative<Left>(val)) {
      val = func(std::get<Left>(val));
    }

    return *this;
  }

  Either& right_map(const std::function<Right(Right)>& func)
  {
    if (std::holds_alternative<Left>(val)) {
      val = func(std::get<Left>(val));
    }

    return *this;
  }

private:
  std::variant<Left, Right> val;
};

#endif // EITHER_HPP
