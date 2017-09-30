#ifndef PROCEDURES_HPP
#define PROCEDURES_HPP

#include "Scheme_values/Scheme_value.hpp"

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Equivalence predicated
////////////////////////////////////////////////////////////////////////////////

inline Scheme_value eqv(const std::vector<Scheme_value>& args, const Env_ptr&)
{
  return Scheme_value(Bool(args[0].as_string() == args[1].as_string()));
}

////////////////////////////////////////////////////////////////////////////////
// List
////////////////////////////////////////////////////////////////////////////////

inline Scheme_value list(const std::vector<Scheme_value>& args, const Env_ptr&)
{
  return Scheme_value(List(args));
}

inline Scheme_value cons(const std::vector<Scheme_value>& args, const Env_ptr&)
{
  if (auto list = args[1].get_value<List>(); list.has_value()) {
    std::vector<Scheme_value> l;
    l.push_back(args[0]);
    for (auto& v : list.value().get_list()) {
      l.push_back(v);
    }
    return Scheme_value(List(l));
  } else {
    return Scheme_value(List(args));
  }
}

inline Scheme_value append(const std::vector<Scheme_value>& args,
                           const Env_ptr&)
{
  auto first_list = args[0].get_value<List>().value().get_list();

  auto second_list = args[1].get_value<List>().value().get_list();
  for (auto& val : second_list) {
    first_list.push_back(val);
  }

  return Scheme_value(List(first_list));
}

inline Scheme_value car(const std::vector<Scheme_value>& args, const Env_ptr&)
{
  return args[0].get_value<List>().value().get_list()[0];
}

Scheme_value cdr(const std::vector<Scheme_value>& args, const Env_ptr&)
{
  auto list = args[0].get_value<List>().value().get_list();
  auto result = std::vector<Scheme_value>(list.begin() + 1, list.end());
  return Scheme_value(List(result));
}

inline Scheme_value eval(const std::vector<Scheme_value>& args,
                         const Env_ptr& env)
{
  return args[0].eval(env).value();
}

////////////////////////////////////////////////////////////////////////////////
// Control features
////////////////////////////////////////////////////////////////////////////////

Scheme_value apply(const std::vector<Scheme_value>& args, const Env_ptr& env)
{
  List arg_list(std::vector<Scheme_value>(args.begin() + 1, args.end() - 1));
  std::vector<Scheme_value> app;
  app.push_back(Scheme_value(arg_list));
  app.push_back(args.back());
  arg_list = append(app, env).get_value<List>().value();

  if (auto lambda = args[0].get_value<Lambda>(); lambda.has_value()) {
    return lambda.value().execute(env, arg_list);
  } else if (auto lambda = args[0].get_value<Built_in>(); lambda.has_value()) {
    return lambda.value().execute(env, arg_list);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////
inline Scheme_value add(const std::vector<Scheme_value>& args, const Env_ptr&)
{
  float sum = 0;
  for (auto& arg : args) {
    sum += arg.get_value<Number>().value().get_number();
  }

  return Scheme_value(Number(sum));
}

inline Scheme_value sub(const std::vector<Scheme_value>& args, const Env_ptr&)
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

inline Scheme_value mul(const std::vector<Scheme_value>& args, const Env_ptr&)
{
  float res = 1;

  for (auto& arg : args) {
    res *= arg.get_value<Number>().value().get_number();
  }

  return Scheme_value(Number(res));
}

inline Scheme_value divide(const std::vector<Scheme_value>& args,
                           const Env_ptr&)
{
  auto res = args[0].get_value<Number>().value().get_number();

  res *= res;

  for (auto& arg : args) {
    res /= arg.get_value<Number>().value().get_number();
  }

  return Scheme_value(Number(res));
}

inline Scheme_value modulo(const std::vector<Scheme_value>& args,
                           const Env_ptr&)
{
  int x = args[0].get_value<Number>().value().get_number();
  int y = args[1].get_value<Number>().value().get_number();

  return Scheme_value(Number(x % y));
}

////////////////////////////////////////////////////////////////////////////////
// Numerical
////////////////////////////////////////////////////////////////////////////////

Scheme_value gt(const std::vector<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get_value<Number>().value().get_number()
      > args[1].get_value<Number>().value().get_number()) {
    return Scheme_value(Bool(true));
  } else {
    return Scheme_value(Bool(false));
  }
}

Scheme_value gte(const std::vector<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get_value<Number>().value().get_number()
      >= args[1].get_value<Number>().value().get_number()) {
    return Scheme_value(Bool(true));
  } else {
    return Scheme_value(Bool(false));
  }
}

Scheme_value lt(const std::vector<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get_value<Number>().value().get_number()
      < args[1].get_value<Number>().value().get_number()) {
    return Scheme_value(Bool(true));
  } else {
    return Scheme_value(Bool(false));
  }
}

Scheme_value lte(const std::vector<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get_value<Number>().value().get_number()
      <= args[1].get_value<Number>().value().get_number()) {
    return Scheme_value(Bool(true));
  } else {
    return Scheme_value(Bool(false));
  }
}

Scheme_value num_equal(const std::vector<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get_value<Number>().value().get_number()
      == args[1].get_value<Number>().value().get_number()) {
    return Scheme_value(Bool(true));
  } else {
    return Scheme_value(Bool(false));
  }
}

#endif // PROCEDURES_HPP
