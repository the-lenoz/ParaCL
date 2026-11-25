

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_DIR})



BISON_TARGET(ParaCLParser
    "${CMAKE_CURRENT_SOURCE_DIR}/parser.y"
    "${GENERATED_DIR}/parser.tab.cc"
    DEFINES_FILE "${GENERATED_DIR}/parser.tab.hh"
)


FLEX_TARGET(ParaCLLexer
    "${CMAKE_CURRENT_SOURCE_DIR}/lexer.l"
    "${GENERATED_DIR}/lex.yy.cc"
)

ADD_FLEX_BISON_DEPENDENCY(ParaCLLexer ParaCLParser)

add_custom_target(generate_parser DEPENDS
    ${BISON_ParaCLParser_OUTPUTS}
    ${FLEX_ParaCLLexer_OUTPUTS}
)


add_library(parser_lib OBJECT)


add_dependencies(parser_lib generate_parser)

target_sources(parser_lib PRIVATE
    ${BISON_ParaCLParser_OUTPUTS}
    ${FLEX_ParaCLLexer_OUTPUTS}
)

target_include_directories(parser_lib
    PRIVATE ${GENERATED_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${FLEX_INCLUDE_DIR}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(parser_lib
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
            parser.cppm
)




