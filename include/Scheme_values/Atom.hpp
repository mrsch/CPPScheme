#ifndef SCHEME_VALUES_ATOM_HPP
#define SCHEME_VALUES_ATOM_HPP

#include "Utils.hpp"

#include <memory>
#include <string>

class Scheme_value;
class Environment;

class Symbol
{
public:
  explicit Symbol(const std::string& atom);

  std::string as_string() const;

private:
  std::string name;
};

#endif // SCHEME_VALUES_ATOM_HPP
