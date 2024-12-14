# CMake 最低版本要求，指定使用的 CMake 最低版本，这里设置为 3.10，可根据实际情况调整
cmake_minimum_required(VERSION 3.10)

# 项目名称，会用于生成最终的可执行文件等相关命名等情况，可自行修改项目名称
project(My_STL)

# 设置 C++ 标准，这里指定为 C++11，你可以根据项目需求修改为比如 C++14、C++17 等
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定头文件查找目录，这里把项目下的 `include` 目录添加进去
include_directories(include)

# 添加可执行文件目标，第一个参数是生成的可执行文件名，第二个参数是对应的源文件列表
add_executable(My_STL main.cpp)

set_target_properties(My_STL PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)