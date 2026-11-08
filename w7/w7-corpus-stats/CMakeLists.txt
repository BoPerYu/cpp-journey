cmake_minimum_required(VERSION 3.20)

project(w7_corpus_stats VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(
    CORPUS_STATS_ENABLE_ASAN
    "Enable AddressSanitizer in Debug builds"
    ON
)

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

if(CORPUS_STATS_ENABLE_ASAN)
    foreach(target
            corpus_stats_lib
            corpus_stats
            corpus_stats_tests)
        if(MSVC)
            target_compile_options(${target}
                PRIVATE $<$<CONFIG:Debug>:/fsanitize=address>
            )
        else()
            target_compile_options(${target}
                PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>
            )
        endif()
    endforeach()

    foreach(target
            corpus_stats
            corpus_stats_tests)
        if(MSVC)
            target_link_options(${target}
                PRIVATE $<$<CONFIG:Debug>:/INCREMENTAL:NO>
            )
        else()
            target_link_options(${target}
                PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>
            )
        endif()
    endforeach()

    if(MSVC)
        get_filename_component(
            CORPUS_STATS_MSVC_BIN_DIR
            "${CMAKE_CXX_COMPILER}"
            DIRECTORY
        )
        foreach(target
                corpus_stats
                corpus_stats_tests)
            add_custom_command(
                TARGET ${target}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${CORPUS_STATS_MSVC_BIN_DIR}/clang_rt.asan_dbg_dynamic-x86_64.dll"
                    "${CORPUS_STATS_MSVC_BIN_DIR}/clang_rt.asan_dynamic-x86_64.dll"
                    "$<TARGET_FILE_DIR:${target}>"
                COMMENT "Copy AddressSanitizer runtime DLL"
                VERBATIM
            )
        endforeach()
    endif()
endif()

enable_testing()

add_test(
    NAME corpus_stats_tests
    COMMAND corpus_stats_tests
)
