add_executable(test_pointer
    main_pointer.cpp
)

target_include_directories(test_pointer PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)

add_executable(test_pointer_2
    main_pointer_2.cpp
)

target_include_directories(test_pointer_2 PUBLIC
    ${CMAKE_SOURCE_DIR}/all.hpp
)