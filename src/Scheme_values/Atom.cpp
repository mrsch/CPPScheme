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

Eval_result Atom::eval(const std::shared_ptr<Environment>& env)
{
  if (auto res = env->get(name)) {
    return *res;
  } else {
    return fmt::format("Unbound variable: {}\n", name);
  }
}
