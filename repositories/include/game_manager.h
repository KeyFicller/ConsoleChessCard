#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "repository_export.h"
#include "game_base.h"
#include <vector>
#include <memory>
#include <string>
#include <cstddef>

namespace Games {

// 游戏管理器类
class REPOSITORY_API game_manager {
public:
    game_manager();
    ~game_manager();
    
    // 注册游戏
    void register_game(std::unique_ptr<game_base> _game);
    
    // 显示游戏列表
    void show_game_list() const;
    
    // 运行指定游戏
    void run_game(size_t _index);
    
    // 运行指定名称的游戏
    void run_game(const std::string& _name);
    
    // 获取游戏数量
    size_t get_game_count() const;
    
    // 运行主菜单循环
    void run();

private:
    std::vector<std::unique_ptr<game_base>> games_;
    
    // 显示主菜单
    void show_main_menu() const;
    
    // 获取用户选择的游戏索引
    size_t get_user_choice() const;
};

} // namespace Games

#endif // GAME_MANAGER_H

