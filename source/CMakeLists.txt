add_executable(${CMAKE_PROJECT_NAME} main.cpp lexer.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)