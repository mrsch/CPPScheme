#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <string>

void left_trim(std::string& s);
void right_trim(std::string& s);
void trim(std::string& s);

std::string substr_and_remove(std::string& str, int length);

#endif // UTILS_HPP
