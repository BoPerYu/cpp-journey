cmake_minimum_required(VERSION 3.20)

project(w7_corpus_stats VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/w7-corpus-stats")

add_library(corpus_stats_lib
    "${SOURCE_DIR}/corpus_stats.cpp"
)

target_include_directories(corpus_stats_lib
    PUBLIC "${SOURCE_DIR}"
)

add_executable(corpus_stats
    "${SOURCE_DIR}/main.cpp"
)

target_link_libraries(corpus_stats
    PRIVATE corpus_stats_lib
)

add_executable(corpus_stats_tests
    "${SOURCE_DIR}/corpus_stats_test.cpp"
)

target_link_libraries(corpus_stats_tests
    PRIVATE corpus_stats_lib
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug 模式：开启 AddressSanitizer (ASan)")
    if(MSVC)
        # Windows MSVC 编译器开启 ASan
        add_compile_options(/fsanitize=address)
        add_link_options(/fsanitize=address)
    else()
        # Linux/Mac GCC/Clang 编译器开启 ASan
        add_compile_options(-fsanitize=address)
        add_link_options(-fsanitize=address)
    endif()
endif()

if(MSVC)
    foreach(target
            corpus_stats_lib
            corpus_stats
            corpus_stats_tests)
        target_compile_options(${target}
            PRIVATE /W4 /permissive- /utf-8
        )
    endforeach()
else()
    foreach(target
            corpus_stats_lib
            corpus_stats
            corpus_stats_tests)
        target_compile_options(${target}
            PRIVATE -Wall -Wextra -Wpedantic
        )
    endforeach()
endif()

enable_testing()

add_test(
    NAME corpus_stats_tests
    COMMAND corpus_stats_tests
)