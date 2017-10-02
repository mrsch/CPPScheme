#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "Scheme_values/Scheme_value.hpp"

#include <memory>
#include <unordered_map>

class Environment
{
public:
  explicit Environment(const Env_ptr& parent = nullptr);

  Maybe<Scheme_ptr> get(const std::string& key);
  Maybe<Scheme_ptr> get_from_this(const std::string& key);

  void add_to_env(const std::string& key, Scheme_ptr value);

private:
  Env_ptr parent;
  std::unordered_map<std::string, Scheme_ptr> env;
};

#endif // ENVIRONMENT_HPP
