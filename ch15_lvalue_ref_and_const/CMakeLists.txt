cmake_minimum_required(VERSION 3.0.0)

add_executable(test_lvalue_ref_and_const
    main_lvalue_ref_and_const.cpp
)

target_include_directories(test_lvalue_ref_and_const PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)