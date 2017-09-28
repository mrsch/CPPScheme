#include <iostream>

#include "Parser.hpp"
#include "Scheme_value.hpp"

#include <algorithm>
#include <editline/readline.h>
#include <variant>

int main()
{
  std::string next;

  while (true) {
    if (next.length() == 0) {
      next += readline(">>> ");
    } else {
      next += readline("... ");
    }

    if (next.size() == 0) {
      continue;
    }

    // count parenthesis
    auto left_paren = std::count(next.begin(), next.end(), '(');
    auto right_paren = std::count(next.begin(), next.end(), ')');
    if (left_paren != right_paren) {
      next += " ";
      continue;
    }

    add_history(next.c_str());

    auto res = parse(next);
    next = "";

    std::cout << res.as_string() << '\n';
  }
}
