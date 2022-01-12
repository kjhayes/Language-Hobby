add_executable(${CMAKE_PROJECT_NAME} main.cpp lexer.cpp parser.cpp tokens.cpp parse_expr.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)