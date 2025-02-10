#include <iostream>
#include <vector>
#include "chess.h"
#include "board.h"
#include "move.h"

int main() {
    Board main_board;

    std::vector<Move> help = {};

    main_board.rook_moves(RANK_4,FILE_C, help);
    for (int i = 0 ; i < help.size(); i++) {
            std::cout << help[i] << ", ";
    }
    return 0;
};