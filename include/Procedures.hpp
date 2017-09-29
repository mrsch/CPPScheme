#ifndef PROCEDURES_HPP
#define PROCEDURES_HPP

#include "Scheme_value.hpp"

inline Scheme_value add(const std::vector<Scheme_value>& args)
{
  int sum = 0;
  for (auto& arg : args) {
    sum += arg.get_value<Number>().value().get_number();
  }

  return Scheme_value(Number(sum));
}

inline Scheme_value car(const std::vector<Scheme_value>& args)
{
  return args[0];
}

  // Scheme_value cdr(const std::vector<Scheme_value>& args)
  // {
  //   auto result = std::vector<Scheme_value>(args.begin() + 1, args.end());
  //   return Scheme_value(List(result));
  // }

  // Scheme_value gt(const std::vector<Scheme_value>& args)
  // {
  //   auto list = args.get_list();

  //   if (list[0].get_number() > list[1].get_number()) {
  //     return Scheme_value("True");
  //   } else {
  //     return Scheme_value();
  //   }
  // }

  // Scheme_value lt(const std::vector<Scheme_value>& args)
  // {
  //   auto list = args.get_list();

  //   if (list[0].get_number() < list[1].get_number()) {
  //     return Scheme_value("True");
  //   } else {
  //     return Scheme_value();
  //   }
  // }

  // Scheme_value gte(const std::vector<Scheme_value>& args)
  // {
  //   auto list = args.get_list();

  //   if (list[0].get_number() >= list[1].get_number()) {
  //     return Scheme_value("True");
  //   } else {
  //     return Scheme_value();
  //   }
  // }

  // Scheme_value lte(const std::vector<Scheme_value>& args)
  // {
  //   auto list = args.get_list();

  //   if (list[0].get_number() <= list[1].get_number()) {
  //     return Scheme_value("True");
  //   } else {
  //     return Scheme_value();
  //   }
  // }

  // Scheme_value sub(const std::vector<Scheme_value>& args)
  // {
  //   int res = 2 * args.get_list()[0].get_number();

  //   for (auto& arg : args.get_list()) {
  //     res -= arg.get_number();
  //   }

  //   return Scheme_value(res);
  // }

  // Scheme_value mul(const std::vector<Scheme_value>& args)
  // {
  //   int res = 1;

  //   for (auto& arg : args.get_list()) {
  //     res *= arg.get_number();
  //   }

  //   return Scheme_value(res);
  // }

  // Scheme_value divide(const std::vector<Scheme_value>& args)
  // {
  //   int res = args.get_list()[0].get_number();

  //   res *= res;

  //   for (auto& arg : args.get_list()) {
  //     res /= arg.get_number();
  //   }

  //   return Scheme_value(res);
  // }

#endif // PROCEDURES_HPP
