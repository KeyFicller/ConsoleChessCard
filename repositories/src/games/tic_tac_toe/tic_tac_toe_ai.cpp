#include "games/tic_tac_toe/tic_tac_toe_ai.h"

namespace TicTacToe {

bool tic_tac_toe_ai::can_win_at(const player _board[BOARD_SIZE][BOARD_SIZE],
                                player _player, 
                                size_t _row, 
                                size_t _col) {
    // 临时测试：如果在此位置下棋，是否能获胜
    if (_board[_row][_col] != player::k_none) {
        return false;
    }
    
    // 创建临时棋盘测试
    player temp_board[BOARD_SIZE][BOARD_SIZE];
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        for (size_t j = 0; j < BOARD_SIZE; ++j) {
            temp_board[i][j] = _board[i][j];
        }
    }
    temp_board[_row][_col] = _player;
    
    // 检查是否能获胜（行、列、对角线）
    // 检查行
    if (temp_board[_row][0] == _player && 
        temp_board[_row][1] == _player && 
        temp_board[_row][2] == _player) {
        return true;
    }
    
    // 检查列
    if (temp_board[0][_col] == _player && 
        temp_board[1][_col] == _player && 
        temp_board[2][_col] == _player) {
        return true;
    }
    
    // 检查主对角线
    if (_row == _col) {
        if (temp_board[0][0] == _player && 
            temp_board[1][1] == _player && 
            temp_board[2][2] == _player) {
            return true;
        }
    }
    
    // 检查副对角线
    if (_row + _col == 2) {
        if (temp_board[0][2] == _player && 
            temp_board[1][1] == _player && 
            temp_board[2][0] == _player) {
            return true;
        }
    }
    
    return false;
}

bool tic_tac_toe_ai::find_best_move(const player _board[BOARD_SIZE][BOARD_SIZE],
                                    player _player,
                                    size_t& _row, 
                                    size_t& _col) {
    // 策略优先级：
    // 1. 优先选择中心 (1, 1)
    // 2. 选择角落 (0,0), (0,2), (2,0), (2,2)
    // 3. 选择边缘 (0,1), (1,0), (1,2), (2,1)
    
    // 1. 尝试中心
    if (_board[1][1] == player::k_none) {
        _row = 1;
        _col = 1;
        return true;
    }
    
    // 2. 尝试角落
    const size_t corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (size_t i = 0; i < 4; ++i) {
        if (_board[corners[i][0]][corners[i][1]] == player::k_none) {
            _row = corners[i][0];
            _col = corners[i][1];
            return true;
        }
    }
    
    // 3. 尝试边缘
    const size_t edges[4][2] = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};
    for (size_t i = 0; i < 4; ++i) {
        if (_board[edges[i][0]][edges[i][1]] == player::k_none) {
            _row = edges[i][0];
            _col = edges[i][1];
            return true;
        }
    }
    
    return false;
}

bool tic_tac_toe_ai::get_move(const player _board[BOARD_SIZE][BOARD_SIZE],
                              player _player, 
                              size_t& _row, 
                              size_t& _col) {
    // 策略优先级：
    // 1. 如果自己能赢，下那一步
    // 2. 如果对方能赢，阻止对方
    // 3. 选择最佳位置（中心、角落、边缘）
    
    player opponent = (_player == player::k_x) ? player::k_o : player::k_x;
    
    // 1. 检查自己是否能获胜
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        for (size_t j = 0; j < BOARD_SIZE; ++j) {
            if (can_win_at(_board, _player, i, j)) {
                _row = i;
                _col = j;
                return true;
            }
        }
    }
    
    // 2. 检查是否需要阻止对手获胜
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        for (size_t j = 0; j < BOARD_SIZE; ++j) {
            if (can_win_at(_board, opponent, i, j)) {
                _row = i;
                _col = j;
                return true;
            }
        }
    }
    
    // 3. 选择最佳位置
    return find_best_move(_board, _player, _row, _col);
}

} // namespace TicTacToe

