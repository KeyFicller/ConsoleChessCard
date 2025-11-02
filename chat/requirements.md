# 项目需求记录

本文档记录了 ConsoleChessCard 项目开发过程中提出的所有需求。

---

## 需求 #1: 初始化 Git 仓库
**时间**: 项目初始阶段  
**描述**: 初始化 git 仓库  
**实现**: 使用 `git init` 命令初始化仓库

---

## 需求 #2: 编写基本 CMake 文件
**时间**: 项目初始阶段  
**描述**: 编写基本的 CMake 文件，并在 template 子文件夹下添加动态库和可执行文件的 CMake 函数模板，命名为 template.txt  
**实现**:
- 创建了 `CMakeLists.txt`（基本的 CMake 配置文件）
- 创建了 `template/template.txt`（包含 `add_shared_library_template()` 和 `add_executable_template()` 函数）

---

## 需求 #3: 添加 sandbox 工程
**时间**: 项目初始阶段  
**描述**: 添加 sandbox 工程，项目类型为可执行文件，main.cpp 在此项目内  
**实现**:
- 创建了 `sandbox/` 目录
- 创建了 `sandbox/CMakeLists.txt`
- 创建了 `sandbox/main.cpp`
- 在主 CMakeLists.txt 中添加了 `add_subdirectory(sandbox)`

---

## 需求 #4: 编写 .gitignore 文件
**时间**: 项目初始阶段  
**描述**: 编写 .gitignore 文件  
**实现**: 创建了 `.gitignore` 文件，包含 CMake 构建文件、编译输出、IDE 配置等忽略规则

---

## 需求 #5: 配置 run debug
**时间**: 开发阶段  
**描述**: 配置 run debug  
**实现**:
- 创建了 `.vscode/launch.json`（调试配置）
- 创建了 `.vscode/tasks.json`（构建任务）
- 创建了 `.vscode/settings.json`（VS Code 设置）

---

## 需求 #6: 创建 repositories 文件夹并添加动态库
**时间**: 开发阶段  
**描述**: 创建 repositories 文件夹，并添加动态库  
**实现**:
- 创建了 `repositories/` 目录结构
- 创建了基本的动态库 CMakeLists.txt
- 使用 `set()` 单独定义 SOURCES、HEADERS 等变量

---

## 需求 #7: 在 repositories 中添加井字棋小游戏
**时间**: 开发阶段  
**描述**: 在 repositories 中添加一个井字棋的小游戏，控制台字符串风格  
**实现**:
- 创建了 `tic_tac_toe.h` 和 `tic_tac_toe.cpp`
- 实现了完整的井字棋游戏逻辑
- 支持控制台字符风格的棋盘显示

---

## 需求 #8: 将导出宏定义单独放在一个文件中
**时间**: 代码重构  
**描述**: 将导出宏定义单独放在一个文件中  
**实现**:
- 创建了 `repository_export.h` 文件
- 将所有导出宏定义移到该文件中
- 更新了相关头文件以包含新文件

---

## 需求 #9: 函数命名风格规范化
**时间**: 代码规范化  
**描述**: 类和函数名全小写加下划线，函数入参加下划线前缀  
**实现**:
- 将所有类名改为全小写加下划线（如 `Game` → `game`）
- 将所有函数名改为全小写加下划线（如 `makeMove` → `make_move`）
- 所有函数参数添加下划线前缀（如 `row` → `_row`）

---

## 需求 #10: 枚举命名规范化
**时间**: 代码规范化  
**描述**: 枚举也使用全小写加下划线，每个枚举项加 k_ 前缀  
**实现**:
- 枚举名改为全小写加下划线（如 `Player` → `player`）
- 枚举值添加 `k_` 前缀（如 `NONE` → `k_none`）

---

## 需求 #11: 将游戏加入到 sandbox 运行
**时间**: 集成阶段  
**描述**: 现在把刚写的游戏加入到 sandbox 运行吧  
**实现**:
- 更新了 `sandbox/CMakeLists.txt` 链接 repository 库
- 更新了 `sandbox/main.cpp` 运行井字棋游戏

---

## 需求 #12: 添加电脑玩家
**时间**: 功能增强  
**描述**: 我希望你为它添加一名电脑玩家  
**实现**:
- 添加了 `player_control` 枚举（k_human, k_computer）
- 实现了 AI 决策逻辑
- 支持人机对战模式，随机决定先后手

---

## 需求 #13: AI 决策代码独立
**时间**: 代码重构  
**描述**: 我希望你把 ai 的决策放到单独的文件中，这样维护性更高  
**实现**:
- 创建了 `tic_tac_toe_ai.h` 和 `tic_tac_toe_ai.cpp`
- 将 AI 决策逻辑独立出来
- 使用静态方法实现

---

## 需求 #14: AI 头文件不对外暴露
**时间**: 代码重构  
**描述**: ai.h 文件请不要暴露给外部使用，新建 inc 文件夹  
**实现**:
- 创建了 `inc/` 文件夹（内部头文件目录）
- 将 `tic_tac_toe_ai.h` 移动到 `inc/` 目录
- 更新了 CMakeLists.txt 配置

---

## 需求 #15: CMake 变量单独定义
**时间**: 代码优化  
**描述**: CMake 的 SOURCES、HEADERS、PUBLIC_HEADER 单独拎出来用 set 是指  
**实现**:
- 使用 `set()` 单独定义 SOURCES、HEADERS、PUBLIC_HEADERS
- 提高了可读性和可维护性

---

## 需求 #16: 添加 quit 退出功能
**时间**: 功能增强  
**描述**: 加入终止对局功能，键入 quit  
**实现**:
- 修改了 `get_user_input()` 函数支持检测 "quit" 命令
- 支持多种格式（quit, q, exit，不区分大小写）

---

## 需求 #17: 人机对战随机先后手
**时间**: 功能增强  
**描述**: 在人机对战时先后手可以随机  
**实现**:
- 使用 `std::random_device` 随机决定先后手
- 根据随机结果动态调整玩家角色

---

## 需求 #18: 优化项目架构
**时间**: 架构重构  
**描述**: 好了，恭喜你完成了第一个游戏，以后会添加更多的小游戏，能否优化一下当前的项目架构  
**实现**:
- 创建了 `game_base` 接口（游戏基类）
- 创建了 `game_manager` 类（游戏管理器）
- 创建了 `game_registry` 类（游戏注册）
- 重构了井字棋为适配器模式
- 重新组织了目录结构

---

## 需求 #19: 移除相对路径包含
**时间**: 代码优化  
**描述**: 请你处理掉项目中相对路径形式的包含，通过添加 cmake 包含目录实现  
**实现**:
- 移除了所有 `../` 相对路径包含
- 在 CMakeLists.txt 中配置了包含目录
- 所有包含使用简洁的路径

---

## 需求 #20: tic_tac_toe 不对外暴露
**时间**: 架构优化  
**描述**: 既然定义了 game manager 类，tic_tac_toe 就不用对外暴露了，在模块内完成注册即可。另外请你重新调整 repositories 的文件结构，目前有点混乱  
**实现**:
- 将 tic_tac_toe 相关文件移到内部目录
- 重新组织了目录结构：
  - `include/` - 只暴露游戏管理接口
  - `inc/games/tic_tac_toe/` - 井字棋内部头文件
  - `src/core/` - 核心功能源文件
  - `src/games/tic_tac_toe/` - 游戏实现源文件
- 移除了 tic_tac_toe.h 的对外暴露

---

## 需求 #21: 修复 BOARD_SIZE 重复定义
**时间**: 代码修复  
**描述**: BOARD_SIZE 重复定义了  
**实现**:
- 修复了 tic_tac_toe_ai.h 中的重复定义
- 统一从 tic_tac_toe.h 中获取 BOARD_SIZE 定义

---

## 需求 #22: 添加 README 文件
**时间**: 文档完善  
**描述**: 添加一个 readme 文件  
**实现**: 创建了详细的 README.md 文件，包含项目介绍、结构、构建说明、使用指南等

---

## 需求 #23: 说明项目性质
**时间**: 文档完善  
**描述**: 请在 readme 中提前说明，这个项目只是在试用 cursor 的编码能力  
**实现**: 在 README.md 开头添加了项目性质的说明

---

## 需求 #24: 记录需求文档
**时间**: 文档完善  
**描述**: 同理，这是一个演示项目，所以在 chat 文件夹下新建文本文件，记录我提出的每次需求  
**实现**: 创建了本文件 `chat/requirements.md` 记录所有需求

---

## 需求 #25: GitHub 仓库创建和推送
**时间**: 部署阶段  
**描述**: 在远端 github 创建仓库并推送  
**实现**: 
- 创建了 GitHub 设置指南文档和推送脚本（后已删除）
- 项目代码已准备就绪，可手动在 GitHub 创建仓库后推送
- 使用命令：`git remote add origin <url>` 和 `git push -u origin main`

---

## 需求 #26: 回退无意义提交
**时间**: 版本管理  
**描述**: 上一次提交没有什么意义，回退掉  
**实现**: 
- 使用 `git reset --soft HEAD~1` 回退提交
- 删除了 GitHub 设置相关的临时文件
- 保留了 requirements.md 并更新了需求记录

