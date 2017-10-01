#ifndef EITHER_HPP
#define EITHER_HPP

#include <functional>
#include <variant>

template <typename Left, typename Right>
class Either
{
public:
  Either() = default;

  Either(const Left& val) : val(val)
  {
  }

  Either(const Right& val) : val(val)
  {
  }

  Either(const std::variant<std::monostate, Left, Right>& val) : val(val)
  {
  }

  operator bool() const
  {
    return std::holds_alternative<Left>(val);
  }

  Left& operator*()
  {
    return std::get<Left>(val);
  }

  Left* operator->()
  {
    return &std::get<Left>(val);
  }

  const Left& operator*() const
  {
    return std::get<Left>(val);
  }

  const Left* operator->() const
  {
    return &std::get<Left>(val);
  }

  Right& error()
  {
    return std::get<Right>(val);
  }

  const Right& error() const
  {
    return std::get<Right>(val);
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
      val = func(std::get<Right>(val));
    }

    return *this;
  }

  std::variant<Left, Right> get() const
  {
    return val;
  }

private:
  std::variant<Left, Right> val;
};

#endif // EITHER_HPP
