add_executable(paracl main.cpp)

CPMAddPackage(
  NAME cli11
  URL https://github.com/CLIUtils/CLI11/archive/refs/tags/v2.7.2.zip
  URL_HASH SHA256=a3ae013321de0bb9195913044a0dcda76cae69bdf34f0cd947998343246498e9
)

CPMAddPackage(
  NAME fmt
  URL https://github.com/fmtlib/fmt/releases/download/12.2.1/fmt-12.2.1.zip
  URL_HASH SHA256=870a49acec5bcdab236aeea834ebd7f0b8548a7d8cea33c996b6873a37f2d50c
  OPTIONS
    "FMT_MODULE OFF"
)

target_sources(paracl
  PUBLIC
    FILE_SET CXX_MODULES
    FILES
      interpreter.cppm
      execute_file.cppm
      repl.cppm

  PRIVATE
    interpreter.cpp
    repl.cpp
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
