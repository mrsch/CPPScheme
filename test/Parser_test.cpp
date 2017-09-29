#include "catch.hpp"

#include <Parser.hpp>

#include <iostream>

TEST_CASE("Test Parser", "[Parser]")
{
  std::string str = "\"stdlib.scm\"";
  auto res = parse_string(str);
  REQUIRE(res.value().as_string() == "stdlib.scm");
}
