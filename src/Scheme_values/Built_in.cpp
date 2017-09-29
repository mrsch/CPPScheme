#include "Scheme_values/Built_in.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

Built_in::Built_in(Procedure proc) : proc(proc)
{
}

Scheme_value Built_in::eval(const std::shared_ptr<Environment>& /* env */)
{
  return Scheme_value{String("Built-in procedure")};
}

std::string Built_in::as_string()
{
  return "Built-in procedure";
}

Scheme_value Built_in::execute(const std::shared_ptr<Environment>& env,
                               List args)
{
  std::vector<Scheme_value> evaled_args;
  for (auto& arg : args.get_list()) {
    evaled_args.emplace_back(arg.eval(env));
  }
  return proc(evaled_args);
}
