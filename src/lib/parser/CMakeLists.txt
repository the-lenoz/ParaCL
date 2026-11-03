

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_DIR})


add_custom_command(
    OUTPUT "${GENERATED_DIR}/parser.tab.cc" "${GENERATED_DIR}/parser.tab.hh"
    COMMAND ${BISON_EXECUTABLE} -d "${CMAKE_CURRENT_SOURCE_DIR}/parser.y" -o "${GENERATED_DIR}/parser.tab.cc"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/parser.y"
    COMMENT "Generating Bison parser"
    VERBATIM
)

add_custom_command(
    OUTPUT "${GENERATED_DIR}/lex.yy.cc"
    COMMAND ${FLEX_EXECUTABLE} -o "${GENERATED_DIR}/lex.yy.cc" "${CMAKE_CURRENT_SOURCE_DIR}/lexer.l"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/lexer.l" "${GENERATED_DIR}/parser.tab.hh" # Lexer generation depends on parser 
    COMMENT "Generating Flex lexer"
    VERBATIM
)

add_library(parser_lib OBJECT)

target_sources(parser_lib
    PUBLIC FILE_SET CXX_MODULES
    FILES
        parser.cppm
)

target_sources(parser_lib PRIVATE
    "${GENERATED_DIR}/parser.tab.cc"
    "${GENERATED_DIR}/lex.yy.cc"
)

target_include_directories(parser_lib
    PRIVATE ${GENERATED_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})



