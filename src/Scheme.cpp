#include "Scheme.hpp"

#include "Procedures.hpp"
#include <experimental/filesystem>
#include <fmt/format.h>

namespace fs = std::experimental::filesystem;

Scheme::Scheme() : default_env(std::make_shared<Environment>())
{
  build_default_environment();

  if (fs::exists("stdlib.scm")) {
    std::string load = "(load \"stdlib.scm\")";
    eval(parse(load), default_env);
  };

  if (fs::exists("resources/stdlib.scm")) {
    std::string load = "(load \"resources/stdlib.scm\")";
    eval(parse(load), default_env);
  };

  if (fs::exists("../resources/stdlib.scm")) {
    std::string load = "(load \"../resources/stdlib.scm\")";
    eval(parse(load), default_env);
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

    auto& res = eval(parse(next), default_env);
    next = "";
    if (res) {
      std::cout << (*res)->as_string() << '\n';
    } else {
      fmt::print("ERROR:\n{}\n", res.error());
    }
  }
}

void Scheme::build_default_environment()
{
  default_env->add_to_env("display",
                          std::make_shared<Scheme_value>(Built_in(display)));
  default_env->add_to_env("apply",
                          std::make_shared<Scheme_value>(Built_in(apply)));
  default_env->add_to_env("eval",
                          std::make_shared<Scheme_value>(Built_in(eval_bi)));
  default_env->add_to_env("eqv?",
                          std::make_shared<Scheme_value>(Built_in(eqv)));
  default_env->add_to_env("+", std::make_shared<Scheme_value>(Built_in(add)));
  default_env->add_to_env("-", std::make_shared<Scheme_value>(Built_in(sub)));
  default_env->add_to_env("*", std::make_shared<Scheme_value>(Built_in(mul)));
  default_env->add_to_env("/",
                          std::make_shared<Scheme_value>(Built_in(divide)));
  default_env->add_to_env("modulo",
                          std::make_shared<Scheme_value>(Built_in(modulo)));
  default_env->add_to_env("car", std::make_shared<Scheme_value>(Built_in(car)));
  default_env->add_to_env("cdr", std::make_shared<Scheme_value>(Built_in(cdr)));
  default_env->add_to_env("cons",
                          std::make_shared<Scheme_value>(Built_in(cons)));
  default_env->add_to_env("list",
                          std::make_shared<Scheme_value>(Built_in(list)));
  default_env->add_to_env("append",
                          std::make_shared<Scheme_value>(Built_in(append)));
  default_env->add_to_env(">", std::make_shared<Scheme_value>(Built_in(gt)));
  default_env->add_to_env(">=", std::make_shared<Scheme_value>(Built_in(gte)));
  default_env->add_to_env("<", std::make_shared<Scheme_value>(Built_in(lt)));
  default_env->add_to_env("<=", std::make_shared<Scheme_value>(Built_in(lte)));
  default_env->add_to_env("=",
                          std::make_shared<Scheme_value>(Built_in(num_equal)));

  // Graphic
  default_env->add_to_env("open-image",
                          std::make_shared<Scheme_value>(Built_in(open_image)));
  default_env->add_to_env("save-image",
                          std::make_shared<Scheme_value>(Built_in(save_image)));
  default_env->add_to_env("rotate",
                          std::make_shared<Scheme_value>(Built_in(rotate)));
  default_env->add_to_env("show",
                          std::make_shared<Scheme_value>(Built_in(show)));
  default_env->add_to_env("above",
                          std::make_shared<Scheme_value>(Built_in(above)));
  default_env->add_to_env("beside",
                          std::make_shared<Scheme_value>(Built_in(beside)));
}
