# 1
add_executable(test_pointer
    main_pointer.cpp
)

target_include_directories(test_pointer PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)

# 2
add_executable(test_pointer_2
    main_pointer_2.cpp
)

target_include_directories(test_pointer_2 PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)

# 3
add_executable(test_pointer_3
    main_pointer_3.cpp
)

target_include_directories(test_pointer_3 PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)

# naive
add_executable(test_naive_pointer
    main_pointer_naive.cpp
)

target_include_directories(test_naive_pointer PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)