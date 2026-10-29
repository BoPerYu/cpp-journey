cmake_minimum_required(VERSION 3.20)

project(w6_word_count VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(W6_ENABLE_ASAN "Enable AddressSanitizer in Debug builds" ON)

function(w6_configure_target target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive- /utf-8)
        target_link_options(
            ${target} PRIVATE $<$<CONFIG:Debug>:/INCREMENTAL:NO>
        )
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    if(W6_ENABLE_ASAN)
        if(MSVC)
            target_compile_options(
                ${target} PRIVATE $<$<CONFIG:Debug>:/fsanitize=address>
            )
            get_filename_component(
                W6_MSVC_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY
            )
            add_custom_command(
                TARGET ${target}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${W6_MSVC_BIN_DIR}/clang_rt.asan_dbg_dynamic-x86_64.dll"
                    "${W6_MSVC_BIN_DIR}/clang_rt.asan_dynamic-x86_64.dll"
                    "$<TARGET_FILE_DIR:${target}>"
                COMMENT "Copy AddressSanitizer runtime DLL"
                VERBATIM
            )
        else()
            target_compile_options(
                ${target} PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>
            )
            target_link_options(
                ${target} PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>
            )
        endif()
    endif()
endfunction()

add_library(word_count_lib src/word_count.cpp)
target_include_directories(
    word_count_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_compile_features(word_count_lib PUBLIC cxx_std_17)
w6_configure_target(word_count_lib)

add_executable(
    word_count
    app/main.cpp
    app/option.cpp
)
target_link_libraries(word_count PRIVATE word_count_lib)
w6_configure_target(word_count)

add_executable(word_count_tests tests/word_count_test.cpp)
target_link_libraries(word_count_tests PRIVATE word_count_lib)
w6_configure_target(word_count_tests)

add_executable(w6d1_transfer_drill drills/w6d1_transfer.cpp)
target_link_libraries(w6d1_transfer_drill PRIVATE word_count_lib)
w6_configure_target(w6d1_transfer_drill)

add_executable(w6d3_core_features drills/w6d3_core_features.cpp)
w6_configure_target(w6d3_core_features)

add_executable(
    option_parser_tests
    tests/option_test.cpp
    app/option.cpp
)
target_include_directories(option_parser_tests PRIVATE app)
w6_configure_target(option_parser_tests)

enable_testing()
add_test(NAME word_count_selftest COMMAND word_count_tests)
add_test(NAME w6d1_transfer_drill COMMAND w6d1_transfer_drill)
add_test(NAME w6d3_core_features COMMAND w6d3_core_features)
add_test(NAME option_parser_tests COMMAND option_parser_tests)
