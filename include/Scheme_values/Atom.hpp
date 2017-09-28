#ifndef SCHEME_VALUES_ATOM_HPP
#define SCHEME_VALUES_ATOM_HPP

#include <string>

class Atom
{
public:
  explicit Atom(const std::string& atom);

  std::string as_string() const
  {
    return name;
  };

private:
  std::string name;
};

#endif // SCHEME_VALUES_ATOM_HPP
