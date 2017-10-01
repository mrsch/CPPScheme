cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

## #################################################################
## Include cmake modules
## #################################################################

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(ExternalProject)

## #################################################################
## Generate compilation databases
## #################################################################

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

## #################################################################
## Project name and version
## #################################################################

project("Scheme" VERSION "0.0.1" LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

## #################################################################
## Output paths of library/executable
## #################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY         "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY         "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/lib")

# Create version file
file(WRITE "${PROJECT_BINARY_DIR}/VERSION" "${PROJECT_VERSION}")

# Generate folders for IDEs (e.g. VisualStudio)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

## #################################################################
## Find include-what-you-use http://include-what-you-use.org/
## #################################################################

find_program(iwyu_path NAMES include-what-you-use iwyu)
if(iwyu_path)
  set(FOUND_IWYU TRUE)
endif()

## #################################################################
## Thirdparty libs
## #################################################################

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

set(EXT_PROJECTS_DIR
  ${PROJECT_SOURCE_DIR}/thirdparty)

add_subdirectory(${EXT_PROJECTS_DIR}/fmtlib EXCLUDE_FROM_ALL)

include_directories(SYSTEM ${EXT_PROJECTS_DIR}/CImg/)
set (CIMG_LIBRARIES)
if(NOT WIN32)
  FIND_PACKAGE(X11 REQUIRED)
  include_directories(${X11_INCLUDE_DIR})
  FIND_PACKAGE(Threads REQUIRED)
  set (CIMG_LIBRARIES
    ${CIMG_LIBRARIES}
    ${X11_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})
endif()

include_directories(SYSTEM ${EXT_PROJECTS_DIR}/range-v3/include)

## #################################################################
## Source Path
## #################################################################

add_subdirectory(${PROJECT_SOURCE_DIR}/src/)

## #################################################################
## Testing
## #################################################################

enable_testing(true)
add_subdirectory(${PROJECT_SOURCE_DIR}/test/)

## #################################################################
## Documentation
## #################################################################

add_subdirectory(${PROJECT_SOURCE_DIR}/doc/)
