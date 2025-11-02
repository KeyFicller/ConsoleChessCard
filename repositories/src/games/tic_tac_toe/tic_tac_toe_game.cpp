#include "games/tic_tac_toe/tic_tac_toe_game.h"
#include "games/tic_tac_toe/tic_tac_toe.h"
#include <memory>
#include <iostream>

namespace Games {

tic_tac_toe_game::tic_tac_toe_game() 
    : game_impl_(std::make_unique<TicTacToe::game>()), 
      status_(game_status::k_not_started) {
}

tic_tac_toe_game::~tic_tac_toe_game() = default;

std::string tic_tac_toe_game::get_name() const {
    return "井字棋 (Tic-Tac-Toe)";
}

std::string tic_tac_toe_game::get_description() const {
    return "经典的3x3棋盘游戏，三个连成一线即获胜";
}

void tic_tac_toe_game::initialize() {
    reset();
}

void tic_tac_toe_game::reset() {
    if (game_impl_) {
        game_impl_->reset();
    }
    status_ = game_status::k_not_started;
}

void tic_tac_toe_game::run() {
    status_ = game_status::k_playing;
    
    if (game_impl_) {
        game_impl_->run();
    }
    
    if (status_ != game_status::k_quit) {
        status_ = game_status::k_finished;
    }
}

game_status tic_tac_toe_game::get_status() const {
    return status_;
}

bool tic_tac_toe_game::is_finished() const {
    if (game_impl_) {
        return game_impl_->is_game_over();
    }
    return status_ == game_status::k_finished || status_ == game_status::k_quit;
}

} // namespace Games

