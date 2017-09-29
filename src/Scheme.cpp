#include "Scheme.hpp"

#include "Procedures.hpp"
#include <fstream>

Scheme::Scheme() : default_env(std::make_shared<Environment>())
{
  build_default_environment();
  std::ifstream stdlib;

  stdlib.open("stdlib.scm", std::ios::in);
  if (!stdlib.is_open()) {
    stdlib.open("resources/stdlib.scm", std::ios::in);
  }
  if (!stdlib.is_open()) {
    stdlib.open("../resources/stdlib.scm", std::ios::in);
  }

  if (stdlib.is_open()) {
    std::string program;
    std::string line;
    while (getline(stdlib, line)) {
      program += line;
    }

    while (program.size() != 0) {
      parse(program).eval(default_env);
    }
  }
}

void Scheme::start_repl()
{
  std::string next;

  while (true) {
    if (next.length() == 0) {
      next += readline(">>> ");
      next += '\n';
    } else {
      next += readline("... ") + std::string("\n");
      next += '\n';
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
    res = res.eval(default_env);
    next = "";

    std::cout << res.as_string() << '\n';
  }
}

void Scheme::build_default_environment()
{
  default_env->add_to_env("eval", Scheme_value(Built_in(eval)));
  default_env->add_to_env("+", Scheme_value(Built_in(add)));
}
