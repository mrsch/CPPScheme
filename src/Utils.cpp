#include "Utils.hpp"

#include <optional>
#include <unordered_map>

void left_trim(std::string& s)
{
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
          }));
}

void right_trim(std::string& s)
{
  s.erase(
    std::find_if(s.rbegin(), s.rend(), [](int ch) { return !std::isspace(ch); })
      .base(),
    s.end());
}

void trim(std::string& s)
{
  left_trim(s);
  right_trim(s);
}

std::string substr_and_remove(std::string& str, int length)
{
  auto res = str.substr(0, length);
  trim(str.erase(0, length));
  return res;
}
