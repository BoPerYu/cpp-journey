cmake_minimum_required(VERSION 3.20)

project(w4_stl LANGUAGES CXX)

# 和 W3 保持一致，先不动标准版本（本周末之前用不到 C++20 的东西）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    # 中文注释 / 字符串按 UTF-8 读（约定第 4 条）
    add_compile_options(/utf-8)

    # W4 起换 /W4（W3 的 CMakeLists 用的是 /W3；约定第 4 条）
    # 注意：C4706（赋值当条件）在 /W3 下是沉默的，/W4 才报 —— W3 已踩过
    add_compile_options(/W4)
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

    # 严格标准模式（不开会放行不合标准的写法）
    add_compile_options(/permissive-)

    # 调试信息格式：CMake 的 Debug 默认就是 /Zi，不用自己加。
    # （D8016 那个坑只在手改 VS 工程、被 IDE 设成 /ZI 时出现。）
endif ()

# ------------------------------------------------------------
# 公共函数：给一个目标开 ASan，构建完把 ASan 运行库 DLL 拷到 exe 旁边
#   （MSVC 的 ASan 是动态运行库，exe 旁边没有 dll 会报 0xC0000135）
# ------------------------------------------------------------
function(w4_enable_asan target)
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

# ------------------------------------------------------------
# 探针：往 labs\ 里丢 .cpp，configure 时自动建一个同名目标
#   —— 新加探针**不用改这个文件**。文件名用 ASCII（中文写进注释）。
# ------------------------------------------------------------
file(GLOB W4_LAB_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/labs/*.cpp")
foreach(lab_src IN LISTS W4_LAB_SOURCES)
    get_filename_component(lab_name "${lab_src}" NAME_WE)
    add_executable(${lab_name} "${lab_src}")
    w4_enable_asan(${lab_name})
endforeach()

# ------------------------------------------------------------
# 本人的主程序（本周检验：用 string / vector 重写 W1 的成绩管理程序）
#   文件还没建，建了之后重新 configure 就自动有目标。
# ------------------------------------------------------------
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/my/scores.cpp")
    add_executable(my_scores my/scores.cpp)
    w4_enable_asan(my_scores)
endif ()
