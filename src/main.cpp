#include <iostream>

#include "Parser.hpp"
#include "Scheme_value.hpp"
#include <variant>

int main()
{
  std::string str = "(define a (+ 1 200))";
  auto res = parse(str);
  std::cout << res.as_string() << '\n';
}
