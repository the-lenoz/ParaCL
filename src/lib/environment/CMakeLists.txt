add_library(environment STATIC)
target_compile_options(environment PUBLIC -Wall -O2)
target_sources(environment
  PUBLIC
    FILE_SET CXX_MODULES
    FILES
      environment.cppm
)
