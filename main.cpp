#include "chess.h"
#include "board.h"
#include <iostream>
#include <vector>


int main() {

    Board board;
    int a, b;

    std::vector<Move> help = {};
	std::vector<std::string> pins = {};

   while (true) { //* actually give this a break condition. and actually make it work work instead of working if both players strictly follow the move rules.
        board.print();
        board.get_moves(help);
        for (int i = 0 ; i < help.size(); i++) {
            std::cout << help[i] << ", ";
        }
        std::cout <<  std::endl << help.size() << std::endl;

/////////////////////////////////////////////////// THIS IS FOR DEBUGGING ///////////////////////////////////////////////////
        std::cout << " WHITE             BLACK \n" ;
        for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
            for (int file = FILE_A ; file <= FILE_H ; file++) {
                std::cout << board._white_sees_squares[rank][file];
            }
            std::cout << "          ";
            for (int file = FILE_A ; file <= FILE_H ; file++) {
                std::cout << board._black_sees_squares[rank][file];
            }
            std::cout << std::endl;
        }
    
/////////////////////////////////////////////////// THIS IS FOR DEBUGGING ///////////////////////////////////////////////////

        Move m;
        // * go into the 'in' override and give it verification.
        std::cin >> m;
        board.player_move(board._turn, m);
        help.clear();

        std::cout << std::endl;

        
        
    }

   
   

    return 0;

};