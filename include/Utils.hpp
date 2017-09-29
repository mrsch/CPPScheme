#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <optional>
#include <string>
#include <unordered_map>

template <class K, class V>
std::optional<V> get_from_map(K key, const std::unordered_map<K, V>& map)
{
  if (map.count(key)) {
    return map.at(key);
  } else {
    return {};
  }
}

void left_trim(std::string& s);
void right_trim(std::string& s);
void trim(std::string& s);

std::string substr_and_remove(std::string& str, int length);

#endif // UTILS_HPP
