#ifndef PROCEDURES_HPP
#define PROCEDURES_HPP

#include "Scheme_values/Scheme_value.hpp"

#include <fmt/format.h>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Equivalence predicated
////////////////////////////////////////////////////////////////////////////////

inline Eval_result eqv(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  return Scheme_value(Scheme_bool(args[0].as_string() == args[1].as_string()));
}

////////////////////////////////////////////////////////////////////////////////
// Output
////////////////////////////////////////////////////////////////////////////////

inline Eval_result display(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  if (auto string = args[0].get<String>()) {
    fmt::print("{}\n", string->get_string());
  } else {
    fmt::print("{}\n", args[0].as_string());
  }

  return Scheme_value(); // Return value is unspecified
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
  if (auto list = args[1].get<List>()) {
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
  auto first_list = args[0].get<List>().value().get_list();

  auto second_list = args[1].get<List>().value().get_list();
  for (auto& val : second_list) {
    first_list.push_back(val);
  }

  return Scheme_value(List(first_list));
}

inline Eval_result car(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  return args[0].get<List>().value().get_list()[0];
}

Scheme_value cdr(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  auto list = args[0].get<List>().value().get_list();
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
    arg_list = *((*appended_list).get<List>());
  }

  if (auto lambda = args[0].get<Lambda>()) {
    return lambda->execute(env, arg_list.get_list());
  } else if (auto lambda = args[0].get<Built_in>()) {
    return lambda->execute(env, arg_list.get_list());
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
    sum += arg.get<Number>().value().get_number();
  }

  return Scheme_value(Number(sum));
}

inline Eval_result sub(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  auto res = args[0].get<Number>().value().get_number();

  if (args.size() == 1) {
    return Scheme_value(Number(-res));
  }

  res *= 2;
  for (auto& arg : args) {
    res -= arg.get<Number>().value().get_number();
  }

  return Scheme_value(Number(res));
}

inline Eval_result mul(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  float res = 1;

  for (auto& arg : args) {
    res *= arg.get<Number>().value().get_number();
  }

  return Scheme_value(Number(res));
}

inline Eval_result divide(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  auto res = args[0].get<Number>().value().get_number();

  res *= res;

  for (auto& arg : args) {
    res /= arg.get<Number>().value().get_number();
  }

  return Scheme_value(Number(res));
}

inline Eval_result modulo(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  int x = args[0].get<Number>().value().get_number();
  int y = args[1].get<Number>().value().get_number();

  return Scheme_value(Number(x % y));
}

////////////////////////////////////////////////////////////////////////////////
// Numerical
////////////////////////////////////////////////////////////////////////////////

Scheme_value gt(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get<Number>().value().get_number()
      > args[1].get<Number>().value().get_number()) {
    return Scheme_value(Scheme_bool(true));
  } else {
    return Scheme_value(Scheme_bool(false));
  }
}

Scheme_value gte(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get<Number>().value().get_number()
      >= args[1].get<Number>().value().get_number()) {
    return Scheme_value(Scheme_bool(true));
  } else {
    return Scheme_value(Scheme_bool(false));
  }
}

Scheme_value lt(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get<Number>().value().get_number()
      < args[1].get<Number>().value().get_number()) {
    return Scheme_value(Scheme_bool(true));
  } else {
    return Scheme_value(Scheme_bool(false));
  }
}

Scheme_value lte(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get<Number>().value().get_number()
      <= args[1].get<Number>().value().get_number()) {
    return Scheme_value(Scheme_bool(true));
  } else {
    return Scheme_value(Scheme_bool(false));
  }
}

Scheme_value num_equal(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  if (args[0].get<Number>().value().get_number()
      == args[1].get<Number>().value().get_number()) {
    return Scheme_value(Scheme_bool(true));
  } else {
    return Scheme_value(Scheme_bool(false));
  }
}

Scheme_value open_image(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  return Scheme_value(Image(args[0].get<String>()->get_string()));
}

Scheme_value rotate(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  if (args.size() == 2) {
    auto image = args[0].get<Image>();
    auto angle = args[1].get<Number>();
    auto res = image->rotate(angle->get_number());
    return Scheme_value(res);
  } else {
    auto image = args[0].get<Image>();
    auto angle = args[1].get<Number>();
    auto x_axis = args[2].get<Number>();
    auto y_axis = args[3].get<Number>();

    auto res = image->rotate(
      angle->get_number(), x_axis->get_number(), y_axis->get_number());
    return Scheme_value(res);
  }
}

Scheme_value above(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  auto image1 = args[0].get<Image>();
  auto image2 = args[1].get<Image>();

  auto res = image1->above(*image2);

  return Scheme_value(res);
}

Scheme_value beside(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  auto image1 = args[0].get<Image>();
  auto image2 = args[1].get<Image>();

  auto res = image1->beside(*image2);

  return Scheme_value(res);
}

Scheme_value save_image(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  auto image1 = args[0].get<Image>();
  auto name = args[1].get<String>();

  image1->save(name->get_string());
  return args[0];
}

Scheme_value show(const std::deque<Scheme_value>& args, const Env_ptr&)
{
  auto image = args[0].get<Image>();
  auto angle = args[1].get<Number>();

  image->show();

  return args[0];
}

#endif // PROCEDURES_HPP
