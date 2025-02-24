#include <iostream>
#include <vector>
#include "chess.h"
#include "board.h"
#include "move.h"

int main() {
    Board main_board;
    main_board.set_up_board();
    std::vector<Move> help = {};
    Move prev_move;

    while(main_board.playing) {

      // system("cls"); // tell the cmd to clear the terminal
        
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

        // for the player. the cpu has a different list of moves. 
        //  (mandatory since each promotion result is a different move to the cpu)
        prev_move = help[0];
        std::cout << help[0] << ", ";
        for (int i = 1 ; i < help.size(); i++) {
            if (prev_move.move_string == help[i].move_string) {
                help.erase(help.begin() + i);
				i--;
            } else {
                std::cout << help[i] << ", ";
                prev_move = help[i];
            }
        }
        
        MinimaxValue recommended = main_board.minimax(4);
        std::cout << "\n\n" << "recommended move: ";
        std::cout << recommended._move.move_string;
        if (recommended._move._promotion) {
            std::cout << "\n promote to " << recommended._move._promotion_piece;
        }
        std::cout << "\n\n";
        std::cout << "total minimax ends: " << end_of_minimax << "\n\ntotal stale/checkmates: " << no_more_moves << "\n\n";

        std::cout << "where we moving, chief? \n";
        std::cin >>  m;
        main_board.player_move(m);
    }

    

    return 0;
};