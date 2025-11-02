# Repositories 动态库项目
include(${CMAKE_SOURCE_DIR}/template/template.txt)

# ==================== 核心文件 ====================
# 核心接口和工具（对外暴露）
set(CORE_SOURCES
    src/core/game_manager.cpp
    src/core/game_registry.cpp
)

set(CORE_HEADERS
    include/game_base.h
    include/game_manager.h
    include/game_registry.h
)

# ==================== 井字棋游戏 ====================
# 游戏实现（内部，不对外暴露）
set(TIC_TAC_TOE_SOURCES
    src/games/tic_tac_toe/tic_tac_toe.cpp
    src/games/tic_tac_toe/tic_tac_toe_ai.cpp
    src/games/tic_tac_toe/tic_tac_toe_game.cpp
)

# ==================== 合并所有源文件 ====================
set(REPOSITORY_SOURCES
    ${CORE_SOURCES}
    ${TIC_TAC_TOE_SOURCES}
)

# ==================== 公共头文件（只暴露游戏管理接口） ====================
set(REPOSITORY_HEADERS
    ${CORE_HEADERS}
)

# 定义公共头文件（只暴露给外部使用的头文件）
set(REPOSITORY_PUBLIC_HEADERS
    include/game_base.h
    include/game_manager.h
    include/game_registry.h
)

# 定义包含目录（公共头文件目录）
set(REPOSITORY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 定义内部头文件目录（不暴露给外部）
set(REPOSITORY_INTERNAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# 使用模板函数创建动态库
add_shared_library_template(
    TARGET_NAME repository
    SOURCES ${REPOSITORY_SOURCES}
    HEADERS ${REPOSITORY_HEADERS}
    INCLUDE_DIR ${REPOSITORY_INCLUDE_DIR}
)

# 为内部源文件添加所有必要的包含路径
target_include_directories(repository PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include    # include/ 目录，公共头文件
    ${CMAKE_CURRENT_SOURCE_DIR}/inc        # inc/ 目录，内部头文件
)

# 设置输出属性
set_target_properties(repository PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
    PUBLIC_HEADER "${REPOSITORY_PUBLIC_HEADERS}"
)
