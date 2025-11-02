cmake_minimum_required(VERSION 3.10)

# 项目名称
project(ConsoleChessCard)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置构建类型（如果没有指定）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 包含目录（如果有头文件目录）
# include_directories(${CMAKE_SOURCE_DIR}/include)

# 源文件（根据实际项目调整）
# file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

# 添加子目录（如果有子项目）
add_subdirectory(repositories)
add_subdirectory(sandbox)

# 可执行文件
# add_executable(${PROJECT_NAME} ${SOURCES})

# 链接库
# target_link_libraries(${PROJECT_NAME} PRIVATE library_name)

