cmake_minimum_required(VERSION 3.0.0)

add_executable(test_algorithm
    main_algorithm.cpp
)

target_include_directories(test_algorithm PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)

add_executable(test_algorithm_2
    main_algorithm_2.cpp
)

target_include_directories(test_algorithm_2 PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)