#include "chess.h"
#include "board.h"
#include <iostream>
#include <vector>


int main() {

    Board board;

    std::vector<Move> help = {};

    while (true) { //* actually give this a break condition. and actually make it work work instead of working if both players strictly follow the move rules.
        board.print();
        board.get_raw_moves(board._turn, help);
        for (int i = 0 ; i < help.size(); i++) {
            std::cout << help[i] << ", ";
        }
        std::cout << std::endl;
        Move m;
        //* go into the 'in' override and give it verification.
        std::cin >> m;
        board.player_move(board._turn, m);
        help.clear();
    }

    return 0;

};