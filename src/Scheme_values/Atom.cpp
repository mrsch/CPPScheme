#include "Scheme_values/Atom.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

#include "fmt/format.h"

Atom::Atom(const std::string& atom) : name(atom)
{
}

std::string Atom::as_string() const
{
  return name;
}

Maybe<Scheme_value> Atom::eval(const std::shared_ptr<Environment>& env)
{
  if (auto res = env->get(name); res.has_value()) {
    return res.value();
  } else {
    fmt::print("Atom \"{}\" is not defined.\n", name);
    return Scheme_value{};
  }
}
