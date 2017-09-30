#include "Scheme_values/Lambda.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

Lambda::Lambda(List arg_list,
               const std::vector<Scheme_value>& body_expressions,
               const std::shared_ptr<Environment>& closure)
  : arg_list(arg_list), body_expressions(body_expressions), closure(closure)
{
}

Eval_result Lambda::eval(const std::shared_ptr<Environment>& /* env */)
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

Eval_result Lambda::execute(const std::shared_ptr<Environment>& env,
                            List args) const
{
  // TODO: Switch for dynamic/lexical scoping
  auto temp_env = std::make_shared<Environment>(closure);

  auto& list = arg_list.get_list();
  for (size_t i = 0; i < list.size(); ++i) {
    auto evaled_arg = args.get_list()[i].eval(env);
    if (evaled_arg) {
      temp_env->add_to_env(list[i].as_string(), *evaled_arg);
    } else {
      // TODO: error message
      return evaled_arg;
    }
  }

  Eval_result result;
  for (auto& body : body_expressions) {
    result = body.eval(temp_env);
    if (!result) {
      // TODO: Error message
      return result;
    }
  }

  return result;
}
