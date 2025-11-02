#ifndef TIC_TAC_TOE_AI_H
#define TIC_TAC_TOE_AI_H

#include "repository_export.h"
#include "tic_tac_toe.h"
#include <cstddef>

namespace TicTacToe {

// AI 决策类
class REPOSITORY_API tic_tac_toe_ai {
public:
    // 计算电脑玩家的下一步棋
    // 参数：
    //   _board: 当前棋盘状态 (BOARD_SIZE x BOARD_SIZE)
    //   _player: 当前玩家 (k_x 或 k_o)
    //   _row, _col: 输出参数，返回选中的位置
    // 返回: 如果找到有效移动返回 true，否则返回 false
    static bool get_move(const player _board[BOARD_SIZE][BOARD_SIZE], 
                        player _player, 
                        size_t& _row, 
                        size_t& _col);

private:
    // 检查玩家是否能在指定位置获胜
    static bool can_win_at(const player _board[BOARD_SIZE][BOARD_SIZE],
                         player _player, 
                         size_t _row, 
                         size_t _col);
    
    // 寻找最佳移动位置（简单策略）
    static bool find_best_move(const player _board[BOARD_SIZE][BOARD_SIZE],
                              player _player,
                              size_t& _row, 
                              size_t& _col);
};

} // namespace TicTacToe

#endif // TIC_TAC_TOE_AI_H

