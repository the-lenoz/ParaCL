add_library(dumper OBJECT)
target_sources(dumper
  PUBLIC
    FILE_SET CXX_MODULES
    FILES
      dumper.cppm
  PRIVATE
      one_line_dumper.cpp
      graphviz_dumper.cpp
)

# // TODO add cpm package boost
find_package(Boost REQUIRED COMPONENTS graph)

target_link_libraries(dumper PUBLIC parser_lib Boost::graph)
