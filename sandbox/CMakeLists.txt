# Sandbox 可执行文件项目
add_executable(sandbox main.cpp)

# 链接 repository 库
target_link_libraries(sandbox PRIVATE repository)

# 包含头文件目录
target_include_directories(sandbox PRIVATE 
    ${CMAKE_SOURCE_DIR}/repositories/include
)

# 设置输出目录（继承父目录设置）
# set_target_properties(sandbox PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
# )

