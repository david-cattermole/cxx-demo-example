# Integration Test files.
#
# This explains how to use the library in a executable.
#

include(CxxDemoExampleUtils)

# Add C++ test executable
add_executable(${target_test_exe}
  main.cpp
  test_a.cpp
  test_b.cpp

  # The generated C++ files are also needed, otherwise symbols will be
  # missing in the executable.
  ${CMAKE_SOURCE_DIR}/src/_cxxbridge.cpp
  ${CMAKE_SOURCE_DIR}/src/lib.cpp)
target_link_libraries(${target_test_exe} ${target_lib})
target_include_directories(${target_test_exe}
  PUBLIC ${CMAKE_SOURCE_DIR}/include
  PRIVATE ${CMAKE_SOURCE_DIR}/src
  )
# Required for Linux, not needed for MS Windows.
set_relative_library_rpath(${target_test_exe} "../lib/")

install(FILES
  DESTINATION "bin")
install(
  TARGETS
  ${target_test_exe}
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib"
  RUNTIME DESTINATION "bin")
