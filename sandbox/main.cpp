#include <iostream>
#include "game_manager.h"
#include "game_registry.h"

int main(int argc, char* argv[])
{
    using namespace Games;
    
    // 创建游戏管理器
    game_manager manager;
    
    // 注册所有游戏
    register_all_games(manager);
    
    // 运行游戏管理器主菜单
    manager.run();
    
    return 0;
}

