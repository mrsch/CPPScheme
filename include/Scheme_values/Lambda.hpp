#ifndef SCHEME_VALUES_LAMBDA_HPP
#define SCHEME_VALUES_LAMBDA_HPP

#include "List.hpp"
#include <string>

class Scheme_value;
class Environment;

class Lambda
{
public:
  Lambda(List arg_list,
         const std::vector<Scheme_value>& body_expressions,
         const std::shared_ptr<Environment>& closure);

  std::string as_string();
  Scheme_value eval(const std::shared_ptr<Environment>& env);
  Scheme_value execute(const std::shared_ptr<Environment>& env,
                       List args) const;

private:
  List arg_list;
  std::vector<Scheme_value> body_expressions;
  std::shared_ptr<Environment> closure;
};

#endif // SCHEME_VALUES_LAMBDA_HPP
