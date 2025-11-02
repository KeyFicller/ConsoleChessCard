#include "tic_tac_toe.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>

namespace TicTacToe {

game::game() : move_count_(0) {
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
    std::cout << "请输入行和列 (0-2)，用空格分隔: ";
    
    if (!(std::cin >> _row >> _col)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    
    return true;
}

void game::run() {
    std::cout << "========================================\n";
    std::cout << "        井字棋游戏 (Tic-Tac-Toe)       \n";
    std::cout << "========================================\n";
    std::cout << "玩家 X 先手，玩家 O 后手\n";
    std::cout << "输入行和列（0-2）来下棋\n";
    std::cout << "输入 'q' 退出游戏\n\n";
    
    reset();
    
    while (!is_game_over()) {
        player current = get_current_player();
        print_board();
        std::cout << "\n当前玩家: " << player_to_char(current) << "\n";
        
        size_t row, col;
        if (!get_user_input(row, col)) {
            std::cout << "输入无效！请输入数字 0-2。\n\n";
            continue;
        }
        
        if (row >= BOARD_SIZE || col >= BOARD_SIZE) {
            std::cout << "位置超出范围！请输入 0-2。\n\n";
            continue;
        }
        
        if (!make_move(row, col, current)) {
            std::cout << "该位置已被占用！请选择其他位置。\n\n";
            continue;
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

