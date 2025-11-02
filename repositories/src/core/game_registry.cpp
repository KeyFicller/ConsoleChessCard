#include "game_registry.h"
#include "games/tic_tac_toe/tic_tac_toe_game.h"

namespace Games {

// 注册所有游戏到管理器
void register_all_games(game_manager& _manager) {
    // 注册井字棋游戏
    _manager.register_game(std::make_unique<tic_tac_toe_game>());
    
    // 未来可以在这里注册更多游戏
    // _manager.register_game(std::make_unique<another_game>());
}

} // namespace Games

