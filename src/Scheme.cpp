#include "Scheme.hpp"

#include "Procedures.hpp"
#include <experimental/filesystem>
#include <fmt/format.h>
#include <fstream>

namespace fs = std::experimental::filesystem;

Scheme::Scheme() : default_env(std::make_shared<Environment>())
{
  build_default_environment();
  std::ifstream stdlib;

  if (fs::exists("stdlib.scm")) {
    std::string load = "(load \"stdlib.scm\")";
    parse(load).eval(default_env);
  };

  if (fs::exists("resources/stdlib.scm")) {
    std::string load = "(load \"resources/stdlib.scm\")";
    parse(load).eval(default_env);
  };

  if (fs::exists("../resources/stdlib.scm")) {
    std::string load = "(load \"../resources/stdlib.scm\")";
    parse(load).eval(default_env);
  };
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

    auto res = parse(next).eval(default_env);
    next = "";
    if (res) {
      std::cout << res->as_string() << '\n';
    } else {
      fmt::print("ERROR:\n{}\n", res.error());
    }
  }
}

void Scheme::build_default_environment()
{
  default_env->add_to_env("display", Scheme_value(Built_in(display)));
  default_env->add_to_env("apply", Scheme_value(Built_in(apply)));
  default_env->add_to_env("eval", Scheme_value(Built_in(eval)));
  default_env->add_to_env("eqv?", Scheme_value(Built_in(eqv)));
  default_env->add_to_env("+", Scheme_value(Built_in(add)));
  default_env->add_to_env("-", Scheme_value(Built_in(sub)));
  default_env->add_to_env("*", Scheme_value(Built_in(mul)));
  default_env->add_to_env("/", Scheme_value(Built_in(divide)));
  default_env->add_to_env("modulo", Scheme_value(Built_in(modulo)));
  default_env->add_to_env("car", Scheme_value(Built_in(car)));
  default_env->add_to_env("cdr", Scheme_value(Built_in(cdr)));
  default_env->add_to_env("cons", Scheme_value(Built_in(cons)));
  default_env->add_to_env("list", Scheme_value(Built_in(list)));
  default_env->add_to_env("append", Scheme_value(Built_in(append)));
  default_env->add_to_env(">", Scheme_value(Built_in(gt)));
  default_env->add_to_env(">=", Scheme_value(Built_in(gte)));
  default_env->add_to_env("<", Scheme_value(Built_in(lt)));
  default_env->add_to_env("<=", Scheme_value(Built_in(lte)));
  default_env->add_to_env("=", Scheme_value(Built_in(num_equal)));
}
