#include "Scheme_values/Lambda.hpp"

#include "Environment.hpp"
#include "Scheme_value.hpp"

Lambda::Lambda(List arg_list,
               const std::vector<Scheme_value>& body_expressions,
               Environment& closure)
  : arg_list(arg_list), body_expressions(body_expressions), closure(&closure)
{
}

Scheme_value Lambda::eval(Environment& /* env */)
{
  return Scheme_value{String("Defined lambda")};
}

std::string Lambda::as_string()
{
  std::string result = "(lambda ";
  result += arg_list.as_string();
  for (auto& body : body_expressions) {
    result += " ";
    result += body.as_string();
  }
  result += ")";

  return result;
}

Scheme_value Lambda::execute(Environment& env, List args)
{
  // TODO: Switch for dynamic/lexical scoping
  Environment temp_env(*closure);

  auto& list = arg_list.get_list();
  for (size_t i = 0; i < list.size(); ++i) {
    auto evaled_arg = args.get_list()[i]->eval(env);
    temp_env.add_to_env(list[i]->as_string(), evaled_arg);
  }

  Scheme_value result;
  for (auto& body : body_expressions) {
    result = body.eval(temp_env);
  }

  return result;
}
