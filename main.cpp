#include <iostream>
#include <vector>
#include "chess.h"
#include "board.h"
#include "move.h"

void print_moves(std::vector<Move>& moves) {
  Move prev_move;
  prev_move = moves[0];
  std::cout << "\n";
  std::cout << moves[0] << ", ";
  for (int i = 1 ; i < moves.size(); i++) {
    if (prev_move.move_string == moves[i].move_string) {
      moves.erase(moves.begin() + i);
      i--;
    } else {
      std::cout << moves[i] << ", ";
      prev_move = moves[i];
    }
  }
}

int main() {
  Board main_board;
  std::vector<Move> help = {};
  bool game_on = true;

  while (game_on)
  {
    main_board.playing = false;
    std::cout << "Choose the game type: (enter the number)" << "\n"
              << "1. Play as White (vs CPU)" << "\n"
              << "2. Play as Black (vs CPU)" << "\n"
              << "3. Player vs Player" << "\n"
              << "4. Watch the bot play (be prepared to ctrl+c)" << "\n"
              << "5. Quit" << "\n";
    std::cin >> game_type;
    std::cin.clear();
    std::cin.ignore(100, '\n');
    
    if (game_type == 5) {
      game_on = false;
    } else if (game_type < 5 && game_type > 0) {
      main_board.playing = true;
      main_board.set_up_board(); 
      history.clear();
    } else {
      std::cout << "Please select a valid option" << "\n\n";
    }

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

      MinimaxValue recommended;
      recommended = main_board.alphabeta(4, -9000000, 9000000);


      // alpha beta plays weird chess. 
      // gave up a Queen Rook fork in favour of a check
      // something wrong in eval...?
      
      // VS CPU (CPU plays Black)
      if (game_type == 1) {
        if (main_board._turn == BLACK) {
          main_board.make_move(recommended._move);
          history.push_back(recommended._move);
          turns_played++;
        } else {
          print_moves(help);
    
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
        
        std::cout << "enter a move from above, 'undo', or 'quit': \n";
        std::cin  >> m;
        main_board.player_move(m);
        }
      }
      // VS CPU (CPU plays White)
      if (game_type == 2) {
        if (main_board._turn == WHITE) {
          main_board.make_move(recommended._move);
          history.push_back(recommended._move);
          turns_played++;
        } else {

          print_moves(help);

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
          
          std::cout << "enter a move from above, 'undo', or 'quit': \n";
          std::cin  >> m;
          main_board.player_move(m);
        }
      }
    
      if (game_type == 3) {
        print_moves(help);

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
          
          std::cout << "enter a move from above, 'undo', or 'quit': \n";
          std::cin  >> m;
          main_board.player_move(m);
      };
      
      if (game_type == 4) {
        if (!history.empty()) {
          if (recommended._move.move_string == history[history.size()-4].move_string) {
            recommended = main_board.alphabeta(6, -9000000, 9000000);
          }
        }
        main_board.make_move(recommended._move);
        history.push_back(recommended._move);
        turns_played++;

        if (turns_played > 200) {
          main_board.playing = false;
        }
      }
    }
  }
  return 0;
};

