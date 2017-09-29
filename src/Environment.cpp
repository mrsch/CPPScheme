#include "Environment.hpp"

#include "Scheme_values/Scheme_value.hpp"
#include "Utils.hpp"

Environment::Environment(const std::shared_ptr<Environment>& parent)
  : parent(parent)
{
}

void Environment::add_to_env(const std::string& key, Scheme_value value)
{
  env[key] = value;
}

std::optional<Scheme_value> Environment::get(const std::string& key)
{
  if (auto res = get_from_this(key); res.has_value()) {
    return res;
  } else if (parent != nullptr) {
    return parent->get(key);
  } else {
    return {};
  }
}

std::optional<Scheme_value> Environment::get_from_this(const std::string& key)
{
  return get_from_map(key, env);
}
