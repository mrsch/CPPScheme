#include "Scheme_values/Built_in.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

Built_in::Built_in(Procedure proc) : proc(proc)
{
}

std::string Built_in::as_string() const
{
  return "Built-in procedure";
}

Eval_result Built_in::execute(const std::shared_ptr<Environment>& env,
                              const std::deque<Scheme_ptr>& args) const
{
  std::deque<Scheme_ptr> evaled_args;
  for (auto& arg : args) {
    auto result = eval(arg, env);
    if (result) {
      evaled_args.emplace_back(*result);
    } else {
      // TODO: error message
      return result;
    }
  }

  return proc(evaled_args, env);
}
