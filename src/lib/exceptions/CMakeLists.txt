add_library(exceptions OBJECT)
target_compile_options(exceptions PUBLIC -Wall -O2)
target_sources(exceptions
  PUBLIC
    FILE_SET CXX_MODULES
    FILES
      exceptions.cppm
)
