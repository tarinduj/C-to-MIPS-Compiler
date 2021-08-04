cmake_minimum_required(VERSION 3.13)

project(shadertrap
    VERSION 1.0
    DESCRIPTION "C to MIPS compiler"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(BISON)
find_package(FLEX)

bison_target(parser lexer_parser/C_parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
flex_target(scanner lexer_parser/C_lexer.flex ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
add_flex_bison_dependency(scanner parser)

add_library(compiler
  include/ast.hpp
  include/catch.hpp
  include/chunk.hpp
  include/clara.hpp
  include/constants.hpp
  include/context.hpp
  include/logger_macros.hpp
  include/rang.hpp
  include/run.hpp
  include/test.hpp
  include/type.hpp
  include/verbosity.hpp

  src/ast_binop.cpp
  src/ast_declarator.cpp
  src/ast_ifstatement.cpp
  src/ast_list.cpp
  src/ast_node.cpp
  src/ast_translation.cpp
  src/ast_variable.cpp
  src/run.cpp
  src/type.cpp
  src/ast_conditional.cpp
  src/ast_function.cpp
  src/ast_jump.cpp
  src/ast_loops.cpp
  src/ast_primitives.cpp
  src/ast_unaryop.cpp
  src/chunk.cpp
  src/context.cpp
  src/run.cpp
  src/verbosity.cpp
  src/run.cpp
  src_fmt/format.cc
  src_fmt/posix.cc
  
  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS}  
)

target_include_directories(compiler PUBLIC include)

add_executable(c-to-mips
  include/compiler.hpp
  src/compiler.cpp
)

target_link_libraries(c-to-mips PRIVATE compiler)
