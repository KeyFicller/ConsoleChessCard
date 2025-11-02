#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "repository_export.h"
#include <cstddef>
#include <string>

// 前向声明
namespace TicTacToe {
    class tic_tac_toe_ai;
}

namespace TicTacToe {

// 棋盘大小
constexpr size_t BOARD_SIZE = 3;

// 玩家类型
enum class player {
    k_none = 0,
    k_x = 1,
    k_o = 2
};

// 游戏状态
enum class game_state {
    k_ongoing,
    k_x_win,
    k_o_win,
    k_draw
};

// 玩家控制类型
enum class player_control {
    k_human,
    k_computer
};

// 游戏类
class REPOSITORY_API game {
public:
    game();
    
    // 重置游戏
    void reset();
    
    // 在指定位置下棋
    bool make_move(size_t _row, size_t _col, player _player);
    
    // 获取当前位置的玩家
    player get_cell(size_t _row, size_t _col) const;
    
    // 获取当前游戏状态
    game_state get_state() const;
    
    // 获取当前玩家（根据回合数）
    player get_current_player() const;
    
    // 设置玩家控制类型
    void set_player_control(player _player, player_control _control);
    
    // 获取玩家控制类型
    player_control get_player_control(player _player) const;
    
    // 检查是否游戏结束
    bool is_game_over() const;
    
    // 打印棋盘（返回字符串）
    std::string get_board_string() const;
    
    // 运行游戏主循环
    void run();

private:
    player board_[BOARD_SIZE][BOARD_SIZE];
    size_t move_count_;
    player_control player_x_control_;
    player_control player_o_control_;
    
    // 检查是否有玩家获胜
    game_state check_winner() const;
    
    // 检查行、列、对角线是否被同一玩家占据
    bool check_line(size_t _start_row, size_t _start_col, 
                   int _delta_row, int _delta_col, player _player) const;
    
    // 转换玩家为字符
    char player_to_char(player _player) const;
    
    // 打印棋盘
    void print_board() const;
    
    // 获取用户输入
    // 返回值：true 表示有效输入，false 表示退出游戏
    bool get_user_input(size_t& _row, size_t& _col);
    
    // AI决策：计算电脑玩家的下一步棋
    bool get_computer_move(player _player, size_t& _row, size_t& _col);
};

// C 接口函数
extern "C" {
    REPOSITORY_API void* create_game();
    REPOSITORY_API void destroy_game(void* _game);
    REPOSITORY_API void run_game(void* _game);
}

} // namespace TicTacToe

#endif // TIC_TAC_TOE_H

