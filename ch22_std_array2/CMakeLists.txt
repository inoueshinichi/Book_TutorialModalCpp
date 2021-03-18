

add_executable(test_std_array2
    main_std_array2.cpp
)

target_include_directories(test_std_array2 PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)