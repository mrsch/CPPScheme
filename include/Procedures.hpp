#ifndef PROCEDURES_HPP
#define PROCEDURES_HPP

#include "Scheme_values/Scheme_value.hpp"

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Equivalence predicated
////////////////////////////////////////////////////////////////////////////////

inline Eval_result eqv(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  return Scheme_value(Bool(args[0].as_string() == args[1].as_string()));
}

////////////////////////////////////////////////////////////////////////////////
// List
////////////////////////////////////////////////////////////////////////////////

inline Eval_result list(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  return Scheme_value(List(args));
}

inline Eval_result cons(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  if (auto list = args[1].get_value<List>(); list.has_value()) {
    std::deque<Scheme_value> l;
    l.push_back(args[0]);
    for (auto& v : list.value().get_list()) {
      l.push_back(v);
    }
    return Scheme_value(List(l));
  } else {
    return Scheme_value(List(args));
  }
}

inline Eval_result append(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  auto first_list = args[0].get_value<List>().value().get_list();

  auto second_list = args[1].get_value<List>().value().get_list();
  for (auto& val : second_list) {
    first_list.push_back(val);
  }

  return Scheme_value(List(first_list));
}

inline Eval_result car(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  return args[0].get_value<List>().value().get_list()[0];
}

Scheme_value cdr(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  auto list = args[0].get_value<List>().value().get_list();
  auto result = std::deque<Scheme_value>(list.begin() + 1, list.end());
  return Scheme_value(List(result));
}

inline Eval_result eval(const std::deque<Scheme_value>& args,
                        const Env_ptr& env)
{
  return args[0].eval(env);
}

////////////////////////////////////////////////////////////////////////////////
// Control features
////////////////////////////////////////////////////////////////////////////////

inline Eval_result apply(const std::deque<Scheme_value>& args,
                         const Env_ptr& env)
{
  List arg_list(std::deque<Scheme_value>(args.begin() + 1, args.end() - 1));
  std::deque<Scheme_value> app;
  app.push_back(Scheme_value(arg_list));
  app.push_back(args.back());
  auto appended_list = append(app, env);
  if (appended_list) {
    arg_list = *((*appended_list).get_value<List>());
  }

  if (auto lambda = args[0].get_value<Lambda>()) {
    return lambda->execute(env, arg_list);
  } else if (auto lambda = args[0].get_value<Built_in>()) {
    return lambda->execute(env, arg_list);
  }

  // TODO: return error
  return std::string("apply failed");
}

////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////
inline Eval_result add(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  float sum = 0;
  for (auto& arg : args) {
    sum += arg.get_value<Number>().value().get_number();
  }

  return Scheme_value(Number(sum));
}

inline Eval_result sub(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  auto res = args[0].get_value<Number>().value().get_number();

  if (args.size() == 1) {
    return Scheme_value(Number(-res));
  }

  res *= 2;
  for (auto& arg : args) {
    res -= arg.get_value<Number>().value().get_number();
  }

  return Scheme_value(Number(res));
}

inline Eval_result mul(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  float res = 1;

  for (auto& arg : args) {
    res *= arg.get_value<Number>().value().get_number();
  }

  return Scheme_value(Number(res));
}

inline Eval_result divide(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  auto res = args[0].get_value<Number>().value().get_number();

  res *= res;

  for (auto& arg : args) {
    res /= arg.get_value<Number>().value().get_number();
  }

  return Scheme_value(Number(res));
}

inline Eval_result modulo(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  int x = args[0].get_value<Number>().value().get_number();
  int y = args[1].get_value<Number>().value().get_number();

  return Scheme_value(Number(x % y));
}

////////////////////////////////////////////////////////////////////////////////
// Numerical
////////////////////////////////////////////////////////////////////////////////

Scheme_value gt(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get_value<Number>().value().get_number()
      > args[1].get_value<Number>().value().get_number()) {
    return Scheme_value(Bool(true));
  } else {
    return Scheme_value(Bool(false));
  }
}

Scheme_value gte(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get_value<Number>().value().get_number()
      >= args[1].get_value<Number>().value().get_number()) {
    return Scheme_value(Bool(true));
  } else {
    return Scheme_value(Bool(false));
  }
}

Scheme_value lt(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get_value<Number>().value().get_number()
      < args[1].get_value<Number>().value().get_number()) {
    return Scheme_value(Bool(true));
  } else {
    return Scheme_value(Bool(false));
  }
}

Scheme_value lte(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get_value<Number>().value().get_number()
      <= args[1].get_value<Number>().value().get_number()) {
    return Scheme_value(Bool(true));
  } else {
    return Scheme_value(Bool(false));
  }
}

Scheme_value num_equal(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get_value<Number>().value().get_number()
      == args[1].get_value<Number>().value().get_number()) {
    return Scheme_value(Bool(true));
  } else {
    return Scheme_value(Bool(false));
  }
}

#endif // PROCEDURES_HPP
