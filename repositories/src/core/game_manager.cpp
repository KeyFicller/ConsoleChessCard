#include "game_manager.h"
#include <iostream>
#include <limits>
#include <string>

namespace Games {

game_manager::game_manager() {
}

game_manager::~game_manager() {
}

void game_manager::register_game(std::unique_ptr<game_base> _game) {
    if (_game) {
        games_.push_back(std::move(_game));
    }
}

void game_manager::show_game_list() const {
    if (games_.empty()) {
        std::cout << "暂无可用游戏。\n";
        return;
    }
    
    std::cout << "\n========== 游戏列表 ==========\n";
    for (size_t i = 0; i < games_.size(); ++i) {
        std::cout << (i + 1) << ". " << games_[i]->get_name() 
                  << " - " << games_[i]->get_description() << "\n";
    }
    std::cout << "==============================\n\n";
}

void game_manager::run_game(size_t _index) {
    if (_index >= games_.size()) {
        std::cout << "无效的游戏索引！\n";
        return;
    }
    
    games_[_index]->run();
}

void game_manager::run_game(const std::string& _name) {
    for (auto& game : games_) {
        if (game->get_name() == _name) {
            game->run();
            return;
        }
    }
    std::cout << "未找到名为 \"" << _name << "\" 的游戏！\n";
}

size_t game_manager::get_game_count() const {
    return games_.size();
}

void game_manager::show_main_menu() const {
    std::cout << "\n========================================\n";
    std::cout << "        Console Chess Card Games       \n";
    std::cout << "========================================\n";
    show_game_list();
    std::cout << "0. 退出\n";
    std::cout << "请选择游戏 (0-" << games_.size() << "): ";
}

size_t game_manager::get_user_choice() const {
    size_t choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return SIZE_MAX;  // 无效选择
    }
    return choice;
}

void game_manager::run() {
    while (true) {
        show_main_menu();
        
        size_t choice = get_user_choice();
        
        if (choice == 0) {
            std::cout << "\n再见！\n";
            break;
        }
        
        if (choice == SIZE_MAX || choice > games_.size()) {
            std::cout << "无效的选择，请重试！\n\n";
            continue;
        }
        
        // 运行选中的游戏
        run_game(choice - 1);
        
        // 游戏结束后继续主菜单
        std::cout << "\n按回车键返回主菜单...\n";
        std::cin.ignore();
        std::cin.get();
    }
}

} // namespace Games

