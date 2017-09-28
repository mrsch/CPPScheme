#ifndef SCHEME_VALUES_NUMBER_HPP
#define SCHEME_VALUES_NUMBER_HPP

#include <string>

class Number
{
public:
  explicit Number(int number) : number(number){};

  std::string as_string() const
  {
    return std::to_string(number);
  };

private:
  int number;
};

#endif // SCHEME_VALUES_NUMBER_HPP
