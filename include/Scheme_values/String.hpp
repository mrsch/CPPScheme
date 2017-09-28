#ifndef SCHEME_VALUES_STRING_HPP
#define SCHEME_VALUES_STRING_HPP

#include <string>

class String
{
public:
  explicit String(const std::string& str) : str(str){};

  std::string as_string() const
  {
    return str;
  };

private:
  std::string str;
};

#endif // SCHEME_VALUES_STRING_HPP
