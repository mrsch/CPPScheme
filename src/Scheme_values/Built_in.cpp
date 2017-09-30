#include "Scheme_values/Built_in.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

Built_in::Built_in(Procedure proc) : proc(proc)
{
}

Eval_result Built_in::eval(const Env_ptr& /* env */)
{
  return Eval_result(Scheme_value{String("Built-in procedure")});
}

std::string Built_in::as_string()
{
  return "Built-in procedure";
}

Eval_result Built_in::execute(const std::shared_ptr<Environment>& env,
                              List args)
{
  std::vector<Scheme_value> evaled_args;
  for (auto& arg : args.get_list()) {
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
