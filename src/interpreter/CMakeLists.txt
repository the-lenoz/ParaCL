add_executable(paracl main.cpp)

include(FetchContent)

FetchContent_Declare(
  cli11
  URL https://github.com/CLIUtils/CLI11/archive/refs/tags/v2.7.2.zip
  FIND_PACKAGE_ARGS NAMES CLI11 CONFIG
)
FetchContent_Declare(
  fmt
  URL https://github.com/fmtlib/fmt/releases/download/12.2.1/fmt-12.2.1.zip
  FIND_PACKAGE_ARGS NAMES fmt CONFIG
)

set(FMT_MODULE OFF CACHE BOOL "" FORCE) # don't build fmt modules
FetchContent_MakeAvailable(cli11 fmt)

target_sources(paracl
  PUBLIC
    FILE_SET CXX_MODULES
    FILES
      interpreter.cppm
      execute_file.cppm
      repl.cppm

  PRIVATE
    interpreter.cpp
)

target_link_libraries(paracl
  PRIVATE
    exceptions
    file_management
    environment
    parser_lib
    dumper
    CLI11::CLI11
    fmt::fmt
)

set_target_properties(paracl
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
