## #################################################################
## Example library
## #################################################################

add_library(scheme-lib
  Parser.cpp
  Utils.cpp
  Atom.cpp
  List.cpp
  Scheme_value.cpp
  )

target_link_libraries(scheme-lib
  PUBLIC)

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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

## #################################################################
## Example executable
## #################################################################

add_executable(main
  main.cpp
  )

target_link_libraries(main
  PUBLIC
  scheme-lib
  )

target_include_directories(main
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${PROJECT_SOURCE_DIR}/src
  )
