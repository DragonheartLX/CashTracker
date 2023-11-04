cmake_minimum_required (VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)

# MSVC设置: 以utf8编译
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

project(CashTracker)

add_subdirectory(CashTracker)
