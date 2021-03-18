add_executable(test_array_iterator
    main_array_iterator.cpp
    array_iterator.hpp
)

target_include_directories(test_array_iterator PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)