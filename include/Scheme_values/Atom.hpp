#ifndef SCHEME_VALUES_ATOM_HPP
#define SCHEME_VALUES_ATOM_HPP

#include <string>

class Scheme_value;
class Environment;

class Atom
{
public:
  explicit Atom(const std::string& atom);

  Scheme_value eval(Environment& env);
  std::string as_string() const;

private:
  std::string name;
};

#endif // SCHEME_VALUES_ATOM_HPP
