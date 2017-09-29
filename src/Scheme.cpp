#include "Scheme.hpp"

Scheme::Scheme()
{
  build_default_environment();
}

void Scheme::start_repl()
{
  std::string next;
  Environment env;

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
    res = res.eval(env);
    next = "";

    std::cout << res.as_string() << '\n';
  }
}

void Scheme::build_default_environment()
{
  // TODO:
}
