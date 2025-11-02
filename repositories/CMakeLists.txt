# Repositories 动态库项目
include(${CMAKE_SOURCE_DIR}/template/template.txt)

# 定义源文件
set(REPOSITORY_SOURCES
    src/tic_tac_toe.cpp
)

# 定义头文件
set(REPOSITORY_HEADERS
    include/tic_tac_toe.h
)

# 定义公共头文件
set(REPOSITORY_PUBLIC_HEADERS
    include/tic_tac_toe.h
)

# 定义包含目录
set(REPOSITORY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 使用模板函数创建动态库
add_shared_library_template(
    TARGET_NAME repository
    SOURCES ${REPOSITORY_SOURCES}
    HEADERS ${REPOSITORY_HEADERS}
    INCLUDE_DIR ${REPOSITORY_INCLUDE_DIR}
)

# 设置输出属性
set_target_properties(repository PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
    PUBLIC_HEADER "${REPOSITORY_PUBLIC_HEADERS}"
)

