add_executable(test_std_array3
    main_std_array3.cpp
    std_array3.hpp
)

target_include_directories(test_std_array3 PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)