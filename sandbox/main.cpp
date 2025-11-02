#include <iostream>
#include "tic_tac_toe.h"

int main(int argc, char* argv[])
{
    using namespace TicTacToe;
    
    // 创建井字棋游戏并运行
    game tic_tac_toe_game;
    tic_tac_toe_game.run();
    
    return 0;
}

