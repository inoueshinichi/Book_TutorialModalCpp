cmake_minimum_required(VERSION 3.0.0)

add_executable(test_basic_iterator
    main_basic_iterator.cpp
)

target_include_directories(test_namespace PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)