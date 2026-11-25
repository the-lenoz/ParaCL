add_executable(paracl main.cpp)

target_sources(paracl
  PUBLIC
    FILE_SET CXX_MODULES
    FILES
      interpreter.cppm

  PRIVATE
    interpreter.cpp
)

target_link_libraries(paracl PRIVATE exceptions environment parser_lib dumper)

set_target_properties(paracl
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
