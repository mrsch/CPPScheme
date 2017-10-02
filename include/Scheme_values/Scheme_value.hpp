#ifndef SCHEME_VALUE_HPP
#define SCHEME_VALUE_HPP

#include "Scheme_values/Atom.hpp"
#include "Scheme_values/Bool.hpp"
#include "Scheme_values/Built_in.hpp"
#include "Scheme_values/Character.hpp"
#include "Scheme_values/Lambda.hpp"
#include "Scheme_values/List.hpp"
#include "Scheme_values/Nil.hpp"
#include "Scheme_values/Number.hpp"
#include "Scheme_values/String.hpp"
#include "Scheme_values/Vector.hpp"
#include "Scheme_values/graphics/Image.hpp"

#include "Utils.hpp"

#include <optional>
#include <signal.h>
#include <string>
#include <variant>

class Environment;

using Value = std::variant<Nil,
                           Symbol,
                           List,
                           String,
                           Character,
                           Number,
                           Scheme_bool,
                           Lambda,
                           Built_in,
                           Vector,
                           // Custom Scheme values
                           Image>;

class Scheme_value
{
public:
  // template <typename V, typename... Args>
  // explicit Scheme_value(id<V>, Args&&... args)
  // {
  //   value.emplace<V>(args...);
  // }

  Scheme_value(const Value& value);

  Scheme_value() = default;
  Scheme_value(const Scheme_value&) = delete;
  Scheme_value& operator=(const Scheme_value&) = delete;
  Scheme_value(Scheme_value&&) = delete;
  Scheme_value& operator=(Scheme_value&&) = delete;

  template <typename T>
  Maybe<T> get() const
  {
    if (std::holds_alternative<T>(value)) {
      return std::get<T>(value);
    } else {
      return {};
    }
  }

  const Value& get_value() const
  {
    return value;
  }

  std::string as_string() const;

private:
  Value value = Nil();
};

const Eval_result eval(const Scheme_ptr& scheme,
                       const std::shared_ptr<Environment>& env);

#endif // SCHEME_VALUE_HPP
