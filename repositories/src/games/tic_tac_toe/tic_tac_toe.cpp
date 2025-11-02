#include "games/tic_tac_toe/tic_tac_toe_ai.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <random>
#include <string>
#include <algorithm>
#include <cctype>

namespace TicTacToe {

game::game() : move_count_(0), player_x_control_(player_control::k_human), 
                player_o_control_(player_control::k_human) {
    reset();
}

void game::reset() {
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        for (size_t j = 0; j < BOARD_SIZE; ++j) {
            board_[i][j] = player::k_none;
        }
    }
    move_count_ = 0;
}

void game::set_player_control(player _player, player_control _control) {
    if (_player == player::k_x) {
        player_x_control_ = _control;
    } else if (_player == player::k_o) {
        player_o_control_ = _control;
    }
}

player_control game::get_player_control(player _player) const {
    if (_player == player::k_x) {
        return player_x_control_;
    } else if (_player == player::k_o) {
        return player_o_control_;
    }
    return player_control::k_human;
}

bool game::make_move(size_t _row, size_t _col, player _player) {
    if (_row >= BOARD_SIZE || _col >= BOARD_SIZE) {
        return false;
    }
    
    if (board_[_row][_col] != player::k_none) {
        return false;
    }
    
    if (_player == player::k_none) {
        return false;
    }
    
    board_[_row][_col] = _player;
    move_count_++;
    return true;
}

player game::get_cell(size_t _row, size_t _col) const {
    if (_row >= BOARD_SIZE || _col >= BOARD_SIZE) {
        return player::k_none;
    }
    return board_[_row][_col];
}

game_state game::get_state() const {
    return check_winner();
}

player game::get_current_player() const {
    return (move_count_ % 2 == 0) ? player::k_x : player::k_o;
}

bool game::is_game_over() const {
    game_state state = get_state();
    return state != game_state::k_ongoing;
}

std::string game::get_board_string() const {
    std::stringstream ss;
    ss << "\n";
    ss << "   0   1   2\n";
    ss << " ┌───┬───┬───┐\n";
    
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        ss << i << "│ ";
        for (size_t j = 0; j < BOARD_SIZE; ++j) {
            ss << player_to_char(board_[i][j]);
            if (j < BOARD_SIZE - 1) {
                ss << " │ ";
            }
        }
        ss << " │\n";
        if (i < BOARD_SIZE - 1) {
            ss << " ├───┼───┼───┤\n";
        }
    }
    ss << " └───┴───┴───┘\n";
    return ss.str();
}

game_state game::check_winner() const {
    // 检查每一行
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        if (board_[i][0] != player::k_none &&
            board_[i][0] == board_[i][1] &&
            board_[i][1] == board_[i][2]) {
            return (board_[i][0] == player::k_x) ? game_state::k_x_win : game_state::k_o_win;
        }
    }
    
    // 检查每一列
    for (size_t j = 0; j < BOARD_SIZE; ++j) {
        if (board_[0][j] != player::k_none &&
            board_[0][j] == board_[1][j] &&
            board_[1][j] == board_[2][j]) {
            return (board_[0][j] == player::k_x) ? game_state::k_x_win : game_state::k_o_win;
        }
    }
    
    // 检查主对角线
    if (board_[0][0] != player::k_none &&
        board_[0][0] == board_[1][1] &&
        board_[1][1] == board_[2][2]) {
        return (board_[0][0] == player::k_x) ? game_state::k_x_win : game_state::k_o_win;
    }
    
    // 检查副对角线
    if (board_[0][2] != player::k_none &&
        board_[0][2] == board_[1][1] &&
        board_[1][1] == board_[2][0]) {
        return (board_[0][2] == player::k_x) ? game_state::k_x_win : game_state::k_o_win;
    }
    
    // 检查是否平局
    if (move_count_ == BOARD_SIZE * BOARD_SIZE) {
        return game_state::k_draw;
    }
    
    return game_state::k_ongoing;
}

bool game::check_line(size_t _start_row, size_t _start_col, 
                     int _delta_row, int _delta_col, player _player) const {
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        size_t row = _start_row + i * _delta_row;
        size_t col = _start_col + i * _delta_col;
        if (row >= BOARD_SIZE || col >= BOARD_SIZE) {
            return false;
        }
        if (board_[row][col] != _player) {
            return false;
        }
    }
    return true;
}

char game::player_to_char(player _player) const {
    switch (_player) {
        case player::k_x:
            return 'X';
        case player::k_o:
            return 'O';
        default:
            return ' ';
    }
}

void game::print_board() const {
    std::cout << get_board_string();
}

bool game::get_user_input(size_t& _row, size_t& _col) {
    std::cout << "请输入行和列 (0-2)，用空格分隔，或输入 'quit' 退出: ";
    
    std::string input;
    if (!(std::cin >> input)) {
        // 输入流错误，可能用户输入了 Ctrl+D 或类似操作
        return false;
    }
    
    // 检查是否是退出命令（支持多种格式）
    std::string input_lower = input;
    std::transform(input_lower.begin(), input_lower.end(), input_lower.begin(), ::tolower);
    
    if (input_lower == "quit" || input_lower == "q" || input_lower == "exit") {
        return false;  // 返回 false 表示用户想要退出
    }
    
    // 尝试将输入解析为数字
    try {
        _row = std::stoul(input);
        if (!(std::cin >> _col)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        return true;
    } catch (const std::exception&) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
}

void game::run() {
    std::cout << "========================================\n";
    std::cout << "        井字棋游戏 (Tic-Tac-Toe)       \n";
    std::cout << "========================================\n";
    
    // 询问游戏模式
    std::cout << "请选择游戏模式：\n";
    std::cout << "1. 人机对战\n";
    std::cout << "2. 人人对战 (玩家 X vs 玩家 O)\n";
    std::cout << "请输入选项 (1 或 2): ";
    
    int mode;
    if (!(std::cin >> mode) || (mode != 1 && mode != 2)) {
        mode = 2;  // 默认人人对战
        std::cout << "使用默认模式：人人对战\n";
    }
    
    // 设置玩家控制类型
    if (mode == 1) {
        // 人机对战：随机决定先后手
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);
        bool human_first = dis(gen) == 0;
        
        if (human_first) {
            set_player_control(player::k_x, player_control::k_human);
            set_player_control(player::k_o, player_control::k_computer);
            std::cout << "\n游戏模式：人机对战\n";
            std::cout << "🎲 随机结果：你先手！\n";
            std::cout << "你是玩家 X（先手），电脑是玩家 O（后手）\n";
        } else {
            set_player_control(player::k_x, player_control::k_computer);
            set_player_control(player::k_o, player_control::k_human);
            std::cout << "\n游戏模式：人机对战\n";
            std::cout << "🎲 随机结果：电脑先手！\n";
            std::cout << "电脑是玩家 X（先手），你是玩家 O（后手）\n";
        }
    } else {
        set_player_control(player::k_x, player_control::k_human);
        set_player_control(player::k_o, player_control::k_human);
        std::cout << "\n游戏模式：人人对战\n";
    }
    
    std::cout << "输入行和列（0-2）来下棋\n";
    std::cout << "输入 'quit' 可以随时退出游戏\n\n";
    
    reset();
    
    while (!is_game_over()) {
        player current = get_current_player();
        player_control control = get_player_control(current);
        
        print_board();
        std::cout << "\n当前玩家: " << player_to_char(current);
        if (control == player_control::k_computer) {
            std::cout << " (电脑)";
        } else {
            std::cout << " (人类)";
        }
        std::cout << "\n";
        
        size_t row, col;
        bool move_valid = false;
        
        if (control == player_control::k_computer) {
            // 电脑玩家自动下棋
            std::cout << "电脑正在思考...\n";
            if (get_computer_move(current, row, col)) {
                move_valid = true;
                std::cout << "电脑选择了位置: (" << row << ", " << col << ")\n";
            }
        } else {
            // 人类玩家输入
            if (get_user_input(row, col)) {
                if (row >= BOARD_SIZE || col >= BOARD_SIZE) {
                    std::cout << "位置超出范围！请输入 0-2。\n\n";
                    continue;
                }
                move_valid = true;
            } else {
                // 检查是否用户想要退出（通过检查 cin 状态或重新读取）
                // 由于 get_user_input 返回 false 可能是退出或输入无效
                // 我们需要更明确地检测退出命令
                std::cout << "\n游戏已退出！\n";
                return;  // 直接退出游戏循环
            }
        }
        
        if (move_valid) {
            if (!make_move(row, col, current)) {
                if (control == player_control::k_human) {
                    std::cout << "该位置已被占用！请选择其他位置。\n\n";
                } else {
                    std::cout << "错误：电脑选择了已被占用的位置。\n\n";
                }
                continue;
            }
        }
        
        std::cout << "\n";
    }
    
    // 游戏结束，显示最终棋盘和结果
    print_board();
    
    game_state final_state = get_state();
    switch (final_state) {
        case game_state::k_x_win:
            std::cout << "\n🎉 玩家 X 获胜！\n";
            break;
        case game_state::k_o_win:
            std::cout << "\n🎉 玩家 O 获胜！\n";
            break;
        case game_state::k_draw:
            std::cout << "\n🤝 平局！\n";
            break;
        default:
            break;
    }
    
    std::cout << "\n游戏结束！\n";
}

bool game::get_computer_move(player _player, size_t& _row, size_t& _col) {
    // 使用 AI 类进行决策
    return tic_tac_toe_ai::get_move(board_, _player, _row, _col);
}

// C 接口实现
extern "C" {
    void* create_game() {
        return new game();
    }
    
    void destroy_game(void* _game) {
        if (_game) {
            delete static_cast<game*>(_game);
        }
    }
    
    void run_game(void* _game) {
        if (_game) {
            static_cast<game*>(_game)->run();
        }
    }
}

} // namespace TicTacToe

