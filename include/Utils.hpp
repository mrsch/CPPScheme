#ifndef UTILS_HPP
#define UTILS_HPP

#include "Either.hpp"

#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

class Scheme_value;
using Eval_result = Either<Scheme_value, std::string>;

template <typename T>
using Maybe = std::optional<T>;

class Environment;
using Env_ptr = std::shared_ptr<Environment>;

template <class K, class V>
Maybe<V> get_from_map(K key, const std::unordered_map<K, V>& map)
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
