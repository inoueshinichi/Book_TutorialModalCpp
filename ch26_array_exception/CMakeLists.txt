


add_executable(test_array_exception
    main_array_exception.cpp
    array_exception.hpp
)

target_include_directories(test_array_exception PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)
