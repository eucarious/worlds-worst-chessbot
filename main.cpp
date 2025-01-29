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
    board.knight_raw_moves(0, 2, 1, help);

    std::cout << "\n\n";


    return 0;

};