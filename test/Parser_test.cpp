#include "catch.hpp"

#include <Parser.hpp>

#include <iostream>

TEST_CASE("Test Parser", "[Parser]")
{
  std::string str = "hallo welt";
  auto res = parse_atom(str);

  str = "bla \"This is a string\" blubb";
  parse_atom(str);
  REQUIRE(str == "\"This is a string\" blubb");
  auto str_res = parse_string(str);
  REQUIRE(str == "blubb");
}
