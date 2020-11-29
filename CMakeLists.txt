cmake_minimum_required(VERSION 2.8.12)

# Project configuration.
project(mmscenegraph)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(PROJECT_HOMEPAGE_URL "https://github.com/david-cattermole/cxx-demo-example")
set(PROJECT_DESCRIPTION "Demo project for the cxx rust crate.")
set(PROJECT_AUTHOR "David Cattermole")
set(PROJECT_COPYRIGHT "2020, David Cattermole.")


# Static build information.
set(target_lib "mmscenegraph")
set(target_test_exe "mmscenegraph_tests")


# Add custom modules to the module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
include(CxxDemoExampleUtils)

set_cxx_standard_cpp_11()

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(tests)
