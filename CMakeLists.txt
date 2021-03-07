cmake_minimum_required(VERSION 3.0.0)
project(cpp_tutorial VERSION 0.1.0)

# include(CTest)
# enable_testing()

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")

add_subdirectory(ch11_numeric) # 整数
add_subdirectory(ch12_floating_point) # 浮動小数点数
add_subdirectory(ch13_keyword)
add_subdirectory(ch14_basic_iterator)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
