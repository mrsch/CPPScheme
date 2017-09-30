#ifndef SCHEME_VALUES_BUILT_IN_HPP
#define SCHEME_VALUES_BUILT_IN_HPP

#include "List.hpp"
#include "Utils.hpp"
#include <functional>
#include <string>

class Scheme_value;
class Environment;

using Procedure =
  std::function<Eval_result(const std::deque<Scheme_value>&, const Env_ptr&)>;

class Built_in
{
public:
  explicit Built_in(Procedure proc);

  std::string as_string();
  Eval_result eval(const Env_ptr& env);
  Eval_result execute(const Env_ptr& env, List args);

private:
  Procedure proc;
};

#endif // SCHEME_VALUES_BUILT_IN_HPP
