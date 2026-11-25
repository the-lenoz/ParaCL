add_executable(paracl main.cpp)

target_sources(paracl
  PUBLIC
    FILE_SET CXX_MODULES
    FILES
      interpreter.cppm

  PRIVATE
    interpreter.cpp
)

target_link_libraries(paracl PRIVATE exceptions environment parser_lib)
