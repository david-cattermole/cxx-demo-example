
# Enable c++11
macro(set_cxx_standard_cpp_11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro()


# Find the Rust compiled library
function(find_rust_library lib_name build_dir out_linktime_file)
  if (MSVC)
    set(staticlib_name "${lib_name}.lib")

    # Get the Rust Library .lib (for Windows).
    message(STATUS "Finding: ${staticlib_name}")
    message(DEBUG "RUST BUILD DIR: ${build_dir}")
    find_path(linktime_dir ${staticlib_name}
      HINTS ${build_dir}
      PATHS ${build_dir}
      )
    if(EXISTS ${linktime_dir})
      set(${out_linktime_file} ${linktime_dir}/${staticlib_name} PARENT_SCOPE)
    endif()

  elseif (UNIX)
    set(archive_name "lib${lib_name}.a")

    # Get the Rust Library .a (for Linux).
    message(STATUS "Finding: ${archive_name}")
    message(DEBUG "RUST BUILD DIR: ${build_dir}")
    find_path(linktime_dir ${archive_name}
      HINTS ${build_dir}
      PATHS ${build_dir}
      )
    if(EXISTS ${linktime_dir})
      set(${out_linktime_file} ${linktime_dir}/${archive_name} PARENT_SCOPE)
    endif()

  else ()
    message(FATAL_ERROR "Only Linux and Windows are supported.")
  endif ()
endfunction()


macro(set_relative_library_rpath target relative_path)
  # HACK: We must change the RPATH variable for the library so that a
  # binary can find the shared object, even if it's not in the
  # $LD_LIBRARY_PATH.
  if (UNIX)
    # We must escape the '$' symbol to make sure it is passed to the
    # compiler.
    set_target_properties(${target} PROPERTIES
      BUILD_WITH_INSTALL_RPATH ON
      INSTALL_RPATH "\$ORIGIN/${relative_path}"
      )
  endif ()
endmacro()
