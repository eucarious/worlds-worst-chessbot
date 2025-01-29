#include "chess.h"
#include "board.h"
#include <iostream>
#include <vector>


int main() {

    Board board;

    int a;
    int b;

    board.print();
    board.find_king(wK, a, b);

    std::cout << a << ", " << b;


	std::cout << "\n\n";

    std::vector<Move> help = {};
    board.knight_raw_moves(RANK_3, FILE_D, WHITE, help);
    for (int i = 0 ; i < help.size() ; i++) {
        std::cout << help.at(i) << std::endl;
    }

    return 0;

};