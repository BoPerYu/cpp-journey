cmake_minimum_required(VERSION 3.20)

project(w8_inverted_index VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(
    INVERTED_INDEX_ENABLE_ASAN
    "Enable AddressSanitizer in Debug builds"
    ON
)

add_library(inverted_index_lib
    src/inverted_index.cpp
)

target_include_directories(inverted_index_lib
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_executable(inverted_index
    src/main.cpp
)

target_link_libraries(inverted_index
    PRIVATE inverted_index_lib
)

add_executable(inverted_index_tests
    tests/inverted_index_test.cpp
)

target_link_libraries(inverted_index_tests
    PRIVATE inverted_index_lib
)

if(MSVC)
    foreach(target
            inverted_index_lib
            inverted_index
            inverted_index_tests)
        target_compile_options(${target}
            PRIVATE /W4 /permissive- /utf-8
        )
    endforeach()
else()
    foreach(target
            inverted_index_lib
            inverted_index
            inverted_index_tests)
        target_compile_options(${target}
            PRIVATE -Wall -Wextra -Wpedantic
        )
    endforeach()
endif()

if(INVERTED_INDEX_ENABLE_ASAN)
    foreach(target
            inverted_index_lib
            inverted_index
            inverted_index_tests)
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
            inverted_index
            inverted_index_tests)
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
            INVERTED_INDEX_MSVC_BIN_DIR
            "${CMAKE_CXX_COMPILER}"
            DIRECTORY
        )
        foreach(target
                inverted_index
                inverted_index_tests)
            add_custom_command(
                TARGET ${target}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${INVERTED_INDEX_MSVC_BIN_DIR}/clang_rt.asan_dbg_dynamic-x86_64.dll"
                    "${INVERTED_INDEX_MSVC_BIN_DIR}/clang_rt.asan_dynamic-x86_64.dll"
                    "$<TARGET_FILE_DIR:${target}>"
                COMMENT "Copy AddressSanitizer runtime DLL"
                VERBATIM
            )
        endforeach()
    endif()
endif()

enable_testing()

add_test(
    NAME inverted_index_tests
    COMMAND inverted_index_tests
)
