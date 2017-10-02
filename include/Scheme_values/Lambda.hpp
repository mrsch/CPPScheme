#ifndef SCHEME_VALUES_LAMBDA_HPP
#define SCHEME_VALUES_LAMBDA_HPP

#include "List.hpp"
#include "Utils.hpp"
#include <string>

class Scheme_value;
class Environment;

class Lambda
{
public:
  Lambda(List arg_list,
         const std::deque<Scheme_ptr>& body_expressions,
         const Env_ptr& closure);

  std::string as_string() const;
  Eval_result execute(const Env_ptr& env,
                      const std::deque<Scheme_ptr>& args) const;

private:
  List arg_list;
  std::deque<Scheme_ptr> body_expressions;
  Env_ptr closure;
};

#endif // SCHEME_VALUES_LAMBDA_HPP
