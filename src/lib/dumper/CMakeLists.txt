add_library(dumper OBJECT)
target_sources(dumper
  PUBLIC
    FILE_SET CXX_MODULES
    FILES
      dumper.cppm
)

target_link_libraries(dumper PUBLIC parser_lib)