#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H

#include "game_base.h"
#include "repository_export.h"
#include <cstddef>
#include <string>

// 前向声明
namespace TicTacToe {
    class game;
}

namespace Games {

// 井字棋游戏适配器类（实现 game_base 接口）
class REPOSITORY_API tic_tac_toe_game : public game_base {
public:
    tic_tac_toe_game();
    ~tic_tac_toe_game() override;
    
    // 实现 game_base 接口
    std::string get_name() const override;
    std::string get_description() const override;
    void initialize() override;
    void reset() override;
    void run() override;
    game_status get_status() const override;
    bool is_finished() const override;

private:
    std::unique_ptr<TicTacToe::game> game_impl_;
    game_status status_;
};

} // namespace Games

#endif // TIC_TAC_TOE_GAME_H

