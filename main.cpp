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
    // std::cout << "\n\n" ;
    // std::cout << " WHITE             BLACK \n" ;
    // for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
    //   for (int file = FILE_A ; file <= FILE_H ; file++) {
    //     std::cout << main_board._white_sees_squares[rank][file];
    //   }
    //     std::cout << "          ";
    //   for (int file = FILE_A ; file <= FILE_H ; file++) {
    //     std::cout << main_board._black_sees_squares[rank][file];
    //   }
    //   std::cout << std::endl;
    // }
/////////////////////////////////////// END OF DEBUGGING STUFF //////////////////////////////////////

    // for the player. the cpu has a different list of moves. 
    //  (mandatory since each promotion result is a different move to the cpu)
    prev_move = help[0];
    std::cout << "\n";
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


    MinimaxValue recommended;
    recommended = main_board.alphabeta(4, -9000000, 9000000);

    // alpha beta plays weird chess. 
    // gave up a Queen Rook fork in favour of a check
    // something wrong in eval...?
     
    if (main_board._turn == BLACK) {
      main_board.make_move(recommended._move);
    } else {
      std::cout << "\n\n" << "recommended move: ";
      std::cout << recommended._move.move_string;
      if (recommended._move._promotion) {
        std::string piece_name;
        switch (recommended._move._promotion_piece)
        {
          case wQ:
          piece_name = "(Q)ueen";
          break;
          case bQ:
          piece_name = "(Q)ueen";
          break;
          case wN:
          piece_name = "(K)night";
          break;
          case bN:
          piece_name = "(K)night";
          break;
          case wR:
          piece_name = "(R)ook";
          break;
          case bR:
          piece_name = "(R)ook";
          break;
          case wB:
          piece_name = "(B)ishop";
          break;
          case bB:
          piece_name = "(B)ishop";
          break;
          
          
          default:
          break;
        }
        std::cout << "\n promote to " << piece_name;
      }
      std::cout << "\n\n";
      // std::cout << "total ab ends: " << end_of_minimax << "\n\ntotal stale/checkmates: " << no_more_moves;
      // std::cout << "\n\nturns played: " << turns_played << "\n\n";
      
      std::cout << "enter a move from above: \n";
      std::cin  >> m;
      main_board.player_move(m);
    }
  }

  return 0;
};