# Install C++ Headers, with bindings to Rust library.
#

install(DIRECTORY
  include/
  DESTINATION "include"
  FILES_MATCHING PATTERN "*.h")
