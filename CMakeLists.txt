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
add_subdirectory(ch15_lvalue_ref_and_const)
add_subdirectory(ch16_algorithm)
add_subdirectory(ch20_std_array)
add_subdirectory(ch22_std_array2)
add_subdirectory(ch24_std_array3)
add_subdirectory(ch25_array_iterator)
add_subdirectory(ch26_array_exception)
add_subdirectory(ch27_pointer)
add_subdirectory(ch28_detail_iterator)
add_subdirectory(ch29_malloc_memory)
add_subdirectory(ch30_basic_vector)
add_subdirectory(ch31_implement_vector)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
