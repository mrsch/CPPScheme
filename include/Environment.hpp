#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "Scheme_values/Scheme_value.hpp"

#include <memory>
#include <unordered_map>

class Environment
{
public:
  explicit Environment(const std::shared_ptr<Environment>& parent = nullptr);

  std::optional<Scheme_value> get(const std::string& key);
  std::optional<Scheme_value> get_from_this(const std::string& key);

  void add_to_env(const std::string& key, Scheme_value value);

private:
  std::shared_ptr<Environment> parent;
  std::unordered_map<std::string, Scheme_value> env;
};

#endif // ENVIRONMENT_HPP
