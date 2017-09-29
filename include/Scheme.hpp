#ifndef SCHEME_HPP
#define SCHEME_HPP

#include "Utils.hpp"
#include <iostream>

#include "Environment.hpp"
#include "Parser.hpp"
#include "Scheme_values/Scheme_value.hpp"

#include <algorithm>
#include <editline/readline.h>
#include <variant>

class Scheme
{
public:
  Scheme();
  void start_repl();

private:
  std::shared_ptr<Environment> default_env;
  void build_default_environment();

  std::string read();
};

#endif // SCHEME_HPP
