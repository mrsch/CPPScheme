#ifndef SCHEME_VALUES_BUILT_IN_HPP
#define SCHEME_VALUES_BUILT_IN_HPP

#include "List.hpp"
#include "Utils.hpp"
#include <functional>
#include <string>

class Scheme_value;
class Environment;

using Procedure =
  std::function<Eval_result(const std::deque<Scheme_ptr>&, const Env_ptr&)>;

class Built_in
{
public:
  explicit Built_in(Procedure proc);

  std::string as_string() const;
  Eval_result execute(const Env_ptr& env,
                      const std::deque<Scheme_ptr>& args) const;

private:
  Procedure proc;
};

#endif // SCHEME_VALUES_BUILT_IN_HPP
