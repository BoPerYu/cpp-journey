cmake_minimum_required(VERSION 3.20)

project(pointer_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    # 1) 中文注释 / 字符串按 UTF-8 读，和 Project1 的约定一致
    add_compile_options(/utf-8)

    # 2) ASan 只在 Debug 下开。
    #    链接时可能看到 LNK4044「无法识别的选项 /fsanitize=address」——那是
    #    link.exe 不认识编译器的开关，可以忽略；目标文件里的 ASan 元数据会让
    #    链接器自动带上运行库（LNK4300 那条警告就是证据）。
    add_compile_options($<$<CONFIG:Debug>:/fsanitize=address>)
    add_link_options($<$<CONFIG:Debug>:/fsanitize=address>)
endif ()

add_executable(pointer_lab pointer-lab.cpp)

if (MSVC)
    # 3) MSVC 的 ASan 是「动态」运行库：exe 旁边（或 PATH 里）必须有
    #    clang_rt.asan_*_dynamic-x86_64.dll，否则从普通终端直接运行会报
    #    0xC0000135（找不到 DLL）——程序还没跑就退出，很容易误判成代码写错。
    #    这里构建完自动拷一份到 exe 的同级目录，这样命令行直接跑也能用。
    get_filename_component(MSVC_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    add_custom_command(TARGET pointer_lab POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MSVC_BIN_DIR}/clang_rt.asan_dbg_dynamic-x86_64.dll"
            "${MSVC_BIN_DIR}/clang_rt.asan_dynamic-x86_64.dll"
            "$<TARGET_FILE_DIR:pointer_lab>"
        COMMENT "拷贝 ASan 运行库 DLL 到输出目录"
        VERBATIM)
endif ()
