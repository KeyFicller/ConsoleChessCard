#ifndef GAME_REGISTRY_H
#define GAME_REGISTRY_H

#include "repository_export.h"
#include "game_manager.h"

namespace Games {

// 注册所有游戏到管理器
REPOSITORY_API void register_all_games(game_manager& _manager);

} // namespace Games

#endif // GAME_REGISTRY_H

