cmake_minimum_required(VERSION 3.0.0)


add_executable(test_numeric 
    main_numeric.cpp
)

target_include_directories(test_numeric PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)