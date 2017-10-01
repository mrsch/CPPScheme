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
#include <string>
#include <variant>

class Environment;
class Scheme_value
{
  // TODO: Dotted list/Pair
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

public:
  Scheme_value() = default;
  Scheme_value(const Scheme_value&) = default;
  Scheme_value(Scheme_value&&) = default;
  Scheme_value& operator=(const Scheme_value&) = default;
  Scheme_value& operator=(Scheme_value&&) = default;

  explicit Scheme_value(Value value);

  template <typename T>
  Maybe<T> get()
  {
    if (std::holds_alternative<T>(value)) {
      return std::get<T>(value);
    } else {
      return {};
    }
  }

  std::string as_string() const;
  Eval_result eval(const Env_ptr& env) const;

private:
  Value value = Nil();
};

#endif // SCHEME_VALUE_HPP
