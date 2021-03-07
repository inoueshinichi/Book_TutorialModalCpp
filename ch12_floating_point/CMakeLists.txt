cmake_minimum_required(VERSION 3.0.0)

add_executable(test_floating_point
    main_floating_point.cpp
)

# add_executable(test_mathmatics_constant
#     main_mathmatics_constant.cpp
# )

target_include_directories(test_numeric PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)