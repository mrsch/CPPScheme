#include "Scheme_values/Built_in.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

Built_in::Built_in(Procedure proc) : proc(proc)
{
}

std::string Built_in::as_string()
{
  return "Built-in procedure";
}

Eval_result Built_in::execute(const std::shared_ptr<Environment>& env,
                              const std::deque<Scheme_value>& args) const
{
  std::deque<Scheme_value> evaled_args;
  for (auto& arg : args) {
    auto result = arg.eval(env);
    if (result) {
      evaled_args.emplace_back(*result);
    } else {
      // TODO: error message
      return result;
    }
  }

  return proc(evaled_args, env);
}
