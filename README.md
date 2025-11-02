# ConsoleChessCard

> **注意**：本项目仅用于试用 Cursor 的编码能力，是一个演示性质的示例项目。

一个控制台风格的多游戏平台，使用 C++ 和 CMake 构建。

## 项目简介

ConsoleChessCard 是一个集合了多个小游戏的控制台应用程序平台。目前支持井字棋游戏，未来将添加更多游戏。

## 项目结构

```
ConsoleChessCard/
├── CMakeLists.txt              # 主 CMake 配置文件
├── README.md                   # 项目说明文档
├── .gitignore                  # Git 忽略文件
├── template/                   # CMake 模板文件
│   └── template.txt            # 动态库和可执行文件模板
├── repositories/               # 游戏库（动态库）
│   ├── CMakeLists.txt
│   ├── include/                # 公共头文件（对外暴露）
│   │   ├── game_base.h         # 游戏基类接口
│   │   ├── game_manager.h      # 游戏管理器
│   │   ├── game_registry.h     # 游戏注册接口
│   │   └── repository_export.h # 导出宏定义
│   ├── inc/                    # 内部头文件（不对外暴露）
│   │   └── games/
│   │       └── tic_tac_toe/    # 井字棋内部头文件
│   │           ├── tic_tac_toe.h
│   │           ├── tic_tac_toe_ai.h
│   │           └── tic_tac_toe_game.h
│   ├── src/                    # 源文件
│   │   ├── core/               # 核心功能
│   │   │   ├── game_manager.cpp
│   │   │   └── game_registry.cpp
│   │   └── games/              # 游戏实现
│   │       └── tic_tac_toe/
│   │           ├── tic_tac_toe.cpp
│   │           ├── tic_tac_toe_ai.cpp
│   │           └── tic_tac_toe_game.cpp
│   └── .vscode/                # VS Code 配置（可选）
└── sandbox/                    # 可执行文件项目
    ├── CMakeLists.txt
    └── main.cpp                # 主程序入口
```

## 功能特性

### 当前支持的游戏

- **井字棋 (Tic-Tac-Toe)**
  - 人机对战模式（随机先后手）
  - 人人对战模式
  - AI 智能对手（策略：获胜优先 > 阻止对手 > 最佳位置）
  - 支持 `quit` 命令随时退出游戏

### 架构特性

- **模块化设计**：每个游戏独立封装，易于扩展
- **统一接口**：所有游戏实现 `game_base` 接口
- **游戏管理器**：统一管理和运行所有游戏
- **内部实现隐藏**：游戏实现细节不对外暴露

## 构建说明

### 前置要求

- CMake 3.10 或更高版本
- C++17 兼容的编译器（如 g++, clang++）
- 支持的操作系统：Linux, macOS, Windows

### 构建步骤

1. **配置项目**
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

2. **编译项目**
   ```bash
   cmake --build .
   ```

   或者使用：
   ```bash
   make  # Linux/macOS
   ```

3. **运行程序**
   ```bash
   ./bin/sandbox  # Linux/macOS
   # 或
   bin\sandbox.exe  # Windows
   ```

### 使用 VS Code

项目已配置 VS Code 调试和运行环境：

- 按 **F5** 启动调试
- 按 **Ctrl+Shift+B** (macOS: **Cmd+Shift+B**) 构建项目
- 在 `.vscode/tasks.json` 中配置了多个构建任务

## 使用指南

### 运行游戏

1. 启动程序后，会显示游戏菜单
2. 选择游戏编号（如 `1` 选择井字棋）
3. 选择游戏模式：
   - `1` - 人机对战（随机先后手）
   - `2` - 人人对战
4. 按照提示输入行列坐标（0-2）
5. 输入 `quit` 可随时退出游戏

### 游戏示例

```
========================================
        Console Chess Card Games       
========================================

========== 游戏列表 ==========
1. 井字棋 (Tic-Tac-Toe) - 经典的3x3棋盘游戏，三个连成一线即获胜
==============================

0. 退出
请选择游戏 (0-1): 1
```

## 开发指南

### 添加新游戏

1. **创建游戏目录**
   ```
   repositories/
   ├── inc/games/新游戏名称/
   │   └── 新游戏头文件.h
   └── src/games/新游戏名称/
       └── 新游戏实现.cpp
   ```

2. **实现游戏接口**
   - 创建适配器类，继承 `game_base`
   - 实现所有虚函数：
     - `get_name()` - 游戏名称
     - `get_description()` - 游戏描述
     - `initialize()` - 初始化
     - `reset()` - 重置游戏
     - `run()` - 运行游戏主循环
     - `get_status()` - 获取游戏状态
     - `is_finished()` - 检查是否结束

3. **注册游戏**
   在 `repositories/src/core/game_registry.cpp` 中添加：
   ```cpp
   _manager.register_game(std::make_unique<新游戏类名>());
   ```

4. **更新 CMakeLists.txt**
   在 `repositories/CMakeLists.txt` 中添加新游戏的源文件

### 代码风格

- **命名规范**：
  - 类名和函数名：全小写加下划线（snake_case）
  - 函数参数：下划线前缀（如 `_row`, `_col`）
  - 枚举值：全小写加下划线，带 `k_` 前缀（如 `k_none`, `k_x`）

- **文件组织**：
  - 公共接口：`include/` 目录
  - 内部实现：`inc/` 目录
  - 源文件：`src/` 目录

## 技术栈

- **语言**：C++17
- **构建系统**：CMake 3.10+
- **编译器**：支持 C++17 的编译器

## 目录说明

- **repositories/**：游戏库（动态库），包含所有游戏实现
- **sandbox/**：可执行程序，使用游戏库
- **template/**：CMake 函数模板，用于创建动态库和可执行文件
- **.vscode/**：VS Code 配置文件（调试、任务、设置）

## 许可证

本项目采用 MIT 许可证。

## 贡献

欢迎提交 Issue 和 Pull Request！

## 更新日志

### v1.0.0
- 初始版本
- 实现井字棋游戏
- 支持人机对战和人人对战
- 实现游戏管理器架构

