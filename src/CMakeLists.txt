## #################################################################
## Example library
## #################################################################

add_library(scheme-lib
  Environment.cpp
  Parser.cpp
  Scheme.cpp
  Scheme_values/Scheme_value.cpp
  Scheme_values/Atom.cpp
  Scheme_values/Bool.cpp
  Scheme_values/Built_in.cpp
  Scheme_values/Character.cpp
  Scheme_values/Lambda.cpp
  Scheme_values/List.cpp
  Scheme_values/Nil.cpp
  Scheme_values/Number.cpp
  Scheme_values/String.cpp
  Scheme_values/Vector.cpp
  Utils.cpp
  )

target_link_libraries(scheme-lib
  PUBLIC
  PRIVATE
  fmt::fmt-header-only
  stdc++fs
  ${SFML_LIBRARIES}
  )

target_include_directories(scheme-lib
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE
  ${PROJECT_SOURCE_DIR}/src
  )

if(${FOUND_IWYU})
  set_property(TARGET  PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  target_compile_options(scheme-lib
    PUBLIC -Wall -Wextra -pedantic -Wnon-virtual-dtor
    -Wcast-align -Wunused -Woverloaded-virtual
    -Wold-style-cast -fno-omit-frame-pointer
    )
  if(COVERAGE)
    add_coverage_to_target(scheme-lib)
  endif()
elseif (MSVC)
  target_compile_options(scheme-lib
    PUBLIC /W4 /W44640
    )
endif()

## #################################################################
## Example executable
## #################################################################

add_executable(main
  main.cpp
  )

target_link_libraries(main
  PUBLIC
  scheme-lib
  edit
  )

target_include_directories(main
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${PROJECT_SOURCE_DIR}/src
  )
