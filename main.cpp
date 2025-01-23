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
    board.knight_raw_moves(2,2, 0, help);

    std::vector<Move> help2 = {};
    board.king_raw_moves(5,7, 0, help2);

    

    return 0;

};