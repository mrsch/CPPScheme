#ifndef SCHEME_VALUES_ATOM_HPP
#define SCHEME_VALUES_ATOM_HPP

#include "Utils.hpp"

#include <memory>
#include <string>

class Scheme_value;
class Environment;

class Atom
{
public:
  explicit Atom(const std::string& atom);

  Scheme_value eval(const Env_ptr& env);
  std::string as_string() const;

private:
  std::string name;
};

#endif // SCHEME_VALUES_ATOM_HPP
