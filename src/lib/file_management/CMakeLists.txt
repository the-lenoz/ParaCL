add_library(file_management OBJECT)
target_compile_options(file_management PUBLIC -Wall -O2)
target_sources(file_management
  PUBLIC
    FILE_SET CXX_MODULES
    FILES
      file_management.cppm
)
target_link_libraries(file_management PUBLIC exceptions)
