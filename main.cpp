#include <iostream>
#include <vector>
#include "chess.h"
#include "board.h"
#include "move.h"

int main() {
    Board main_board;
    main_board.test_board();
    std::vector<Move> help = {};

    while(main_board.playing) {
        Move m;
        main_board.get_moves(help);
        main_board.print();
        if (help.empty()) {break;}

////////////////////////////////////////// DEBUGGING STUFF //////////////////////////////////////////
        std::cout << "\n\n" ;
        std::cout << " WHITE             BLACK \n" ;
        for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
            for (int file = FILE_A ; file <= FILE_H ; file++) {
                std::cout << main_board._white_sees_squares[rank][file];
            }
            std::cout << "          ";
            for (int file = FILE_A ; file <= FILE_H ; file++) {
                std::cout << main_board._black_sees_squares[rank][file];
            }
            std::cout << std::endl;
        }
/////////////////////////////////////// END OF DEBUGGING STUFF //////////////////////////////////////

        for (int i = 0 ; i < main_board.legal_moves.size(); i++) {
            std::cout << main_board.legal_moves[i] << ", ";
        }
        std::cout <<  std::endl << main_board.legal_moves.size() << std::endl;

        std::cout << "where we moving, chief?";
        std::cin >>  m;
        main_board.make_move(m);

        
    }

    

    return 0;
};