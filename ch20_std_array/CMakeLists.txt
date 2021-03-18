cmake_minimum_required(VERSION 3.0.0)


add_executable(test_std_array
    main_std_array.cpp
)

target_include_directories(test_std_array PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)