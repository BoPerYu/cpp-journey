cmake_minimum_required(VERSION 3.20)

project(w5_stl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/utf-8)
    add_compile_options(/W4)
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    add_compile_options(/permissive-)
endif ()

function(w5_enable_asan target)
    if (MSVC)
        target_compile_options(${target} PRIVATE $<$<CONFIG:Debug>:/fsanitize=address>)
        target_link_options(${target} PRIVATE $<$<CONFIG:Debug>:/fsanitize=address>)
        get_filename_component(MSVC_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${MSVC_BIN_DIR}/clang_rt.asan_dbg_dynamic-x86_64.dll"
                "${MSVC_BIN_DIR}/clang_rt.asan_dynamic-x86_64.dll"
                "$<TARGET_FILE_DIR:${target}>"
            COMMENT "拷贝 ASan 运行库 DLL 到输出目录"
            VERBATIM)
    endif ()
endfunction()

file(GLOB W5_LAB_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/labs/*.cpp")
foreach(lab_src IN LISTS W5_LAB_SOURCES)
    get_filename_component(lab_name "${lab_src}" NAME_WE)
    add_executable(${lab_name} "${lab_src}")
    w5_enable_asan(${lab_name})
endforeach()

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/my/word_count.cpp")
    add_executable(word_count my/word_count.cpp)
    w5_enable_asan(word_count)
endif ()
