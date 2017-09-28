#catch
ExternalProject_Add(
  catch
  PREFIX ${CMAKE_BINARY_DIR}/catch
  GIT_REPOSITORY https://github.com/philsquared/Catch.git
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  LOG_DOWNLOAD ON
  )
ExternalProject_Get_Property(catch source_dir)
include_directories(SYSTEM ${source_dir}/include)

add_executable(unit_test
  unit_test.cpp

  Parser_test.cpp
  )

add_dependencies(unit_test catch)

target_compile_features(unit_test
  PUBLIC
  cxx_auto_type
  cxx_range_for
  cxx_return_type_deduction
  )

target_link_libraries(unit_test scheme-lib)

add_test(
  NAME UnitTests
  COMMAND $<TARGET_FILE:unit_test>
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

if(COVERAGE)
  setup_target_for_coverage(coverage unit_test coverage)
endif()

# Copy files to output directory

# add_custom_target(
#   copy_testfiles ALL
#   )

# add_custom_command(TARGET copy_testfiles
#   COMMAND ${CMAKE_COMMAND} -E copy_directory
#   ${CMAKE_CURRENT_SOURCE_DIR}/testfiles $<TARGET_FILE_DIR:unit_test>/testfiles
# )
