#include "Scheme_values/List.hpp"

#include "Scheme_value.hpp"

List::List(std::vector<std::unique_ptr<Scheme_value>>& list)
  : list(std::move(list)){};

List::List(const List& other)
{
  for (auto& e : other.list) {
    list.emplace_back(std::make_unique<Scheme_value>(*e));
  }
}

std::string List::as_string()
{
  std::string res = "(";
  for (auto& e : list) {
    res += e->as_string() + " ";
  }
  res.erase(res.length() - 1, 1);
  res += ")";

  return res;
}
