#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "chess.h"
#include "move.h"

class Board {
public:

  int _wK_rank, _wK_file, _bK_rank, _bK_file;
  int _turn = WHITE;

  bool _wKK_castle_allowed = true;
  bool _wKQ_castle_allowed = true;
  bool _bKK_castle_allowed = true;
  bool _bKQ_castle_allowed = true;

  int _doublestep_on_file = -1;



  //* don't forget Threefold Repetition (same check 3 times)
  //  Dead Position
  //  int _50_move_rule = 0;
  //  we have an arbiter. we'll be fine if we dont hardcode draw rules (except stalemate)

///////////////////////////////////////////////////////////////////////////////////////////////////////
// BOARD REPRESENTATION AND VARIOUS METHODS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////


  int _board[8][8] = {
		{ bR, bN, bB, bQ, bK, bB, bN, bR },
		{ bP, bP, bP, bP, bP, bP, bP, bP },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ NA, NA, wR, NA, NA, NA, NA, NA },
		{ NA, NA, NA, NA, NA, NA, bB, NA },
		{ wP, wP, wP, wP, wP, wP, wP, wP },
		{ wR, wN, wB, wQ, wK, wB, wN, wR }
	};


	//  UNEDITED BOARD FOR U <3
	//  { bR, bN, bB, bQ, bK, bB, bN, bR },
	// 	{ bP, bP, bP, bP, bP, bP, bP, bP },
	// 	{ NA, NA, NA, NA, NA, NA, NA, NA },
	// 	{ NA, NA, NA, NA, NA, NA, NA, NA },
	// 	{ NA, NA, NA, NA, NA, NA, NA, NA },
	// 	{ NA, NA, NA, NA, NA, NA, NA, NA },
	// 	{ wP, wP, wP, wP, wP, wP, wP, wP },
	// 	{ wR, wN, wB, wQ, wK, wB, wN, wR }


  void clear_board() {
    for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
			for (int file = FILE_A ; file <= FILE_H ; file++) { 
				_board[rank][file] = NA;
			}
		}
    _wK_rank, _wK_file, _bK_rank, _bK_file = -1;
  }

  void set_up_board() {
    clear_board();
    //* call  AD map clears here

    _board[RANK_8][FILE_A] = bR;
    _board[RANK_8][FILE_B] = bN;
    _board[RANK_8][FILE_C] = bB;
    _board[RANK_8][FILE_D] = bQ;
    _board[RANK_8][FILE_E] = bK;
    _board[RANK_8][FILE_F] = bB;
    _board[RANK_8][FILE_G] = bN;
    _board[RANK_8][FILE_H] = bR;
    for (int i = FILE_A; i <= FILE_H; i++) {
      _board[RANK_7][i] = bP;
    }

    _bK_rank = RANK_8;
    _bK_file = FILE_E;

    _board[RANK_1][FILE_A] = wR;
    _board[RANK_1][FILE_B] = wN;
    _board[RANK_1][FILE_C] = wB;
    _board[RANK_1][FILE_D] = wQ;
    _board[RANK_1][FILE_E] = wK;
    _board[RANK_1][FILE_F] = wB;
    _board[RANK_1][FILE_G] = wN;
    _board[RANK_1][FILE_H] = wR;
    for (int i = FILE_A; i <= FILE_H; i++) {
      _board[RANK_2][i] = wP;
    }
    _wK_rank = RANK_1;
    _wK_file = FILE_E;
  }

  void print() const { 
	   std::cout << "\n";
		// remember: rank 1 is value 7 and rank 8 is 0. because array schtuff
    	for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) {  

			std::cout << "+----+----+----+----+----+----+----+----+\n";

			for (int file = FILE_A ; file <= FILE_H ; file++) { 
					
				std::cout << "|";

				int piece = _board[rank][file];
				// switch with 13 cases? hell yeah
				switch (piece)
				{
					case NA: std::cout << "    "; break;
					case wP: std::cout << " wP "; break;
					case bP: std::cout << " bP "; break;
					case wR: std::cout << " wR "; break;
					case wN: std::cout << " wN "; break;
					case wB: std::cout << " wB "; break;
					case wQ: std::cout << " wQ "; break;
					case wK: std::cout << " wK "; break;
					case bR: std::cout << " bR "; break;
					case bN: std::cout << " bN "; break;
					case bB: std::cout << " bB "; break;
					case bQ: std::cout << " bQ "; break;
					case bK: std::cout << " bK "; break;

				default:
					std::cout << "SOMETHING'S WRONG IN PRINT!!";
					break;
				}
			}
			std::cout << "|\n";
    	}
    	std::cout << "+----+----+----+----+----+----+----+----+\n";
	}




///////////////////////////////////////////////////////////////////////////////////////////////////////
// ATTACK / DEFEND MAPS (KIND OF) (NOT REALLY) ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

	int _white_sees_squares[8][8] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	int _wP_sees_squares[8][8] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	int _wR_sees_squares[8][8] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	int _wN_sees_squares[8][8] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	int _wB_sees_squares[8][8] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	int _wK_sees_squares[8][8] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};


  int _black_sees_squares[8][8] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	int _bP_sees_squares[8][8] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	int _bR_sees_squares[8][8] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	int _bN_sees_squares[8][8] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	int _bB_sees_squares[8][8] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	int _bK_sees_squares[8][8] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};

  void stack_white_ad() {
    for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
			for (int file = FILE_A ; file <= FILE_H ; file++) { 
				_white_sees_squares[rank][file] += _wP_sees_squares[rank][file];
				_white_sees_squares[rank][file] += _wR_sees_squares[rank][file];
				_white_sees_squares[rank][file] += _wN_sees_squares[rank][file];
				_white_sees_squares[rank][file] += _wB_sees_squares[rank][file];
				_white_sees_squares[rank][file] += _wK_sees_squares[rank][file];
			}
		}
  }

  void stack_black_ad() {
		for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
			for (int file = FILE_A ; file <= FILE_H ; file++) { 
				_black_sees_squares[rank][file] += _bP_sees_squares[rank][file];
				_black_sees_squares[rank][file] += _bR_sees_squares[rank][file];
				_black_sees_squares[rank][file] += _bN_sees_squares[rank][file];
				_black_sees_squares[rank][file] += _bB_sees_squares[rank][file];
				_black_sees_squares[rank][file] += _bK_sees_squares[rank][file];
			}
		}
	}

  void clear_white_ad() { 
		for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
			for (int file = FILE_A ; file <= FILE_H ; file++) { 
				_white_sees_squares[rank][file] = 0;
				_wP_sees_squares[rank][file] = 0;
				_wR_sees_squares[rank][file] = 0;
				_wN_sees_squares[rank][file] = 0;
				_wB_sees_squares[rank][file] = 0;
				_wK_sees_squares[rank][file] = 0;
			}
		}
	};

	void clear_black_ad() { 
		for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
			for (int file = FILE_A ; file <= FILE_H ; file++) { 
				_black_sees_squares[rank][file] = 0;
				_bP_sees_squares[rank][file] = 0;
				_bR_sees_squares[rank][file] = 0;
				_bN_sees_squares[rank][file] = 0;
				_bB_sees_squares[rank][file] = 0;
				_bK_sees_squares[rank][file] = 0;
			}
		}
	};

///////////////////////////////////////////////////////////////////////////////////////////////////////
// MISCELLANEOUS METHODS AND STUFF I HAVEN'T GROUPED //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

  std::string int_to_file(int file) {
		std::string return_value;
		switch (file)
		{
			case FILE_A: return_value = "a"; break;
			case FILE_B: return_value = "b"; break;
			case FILE_C: return_value = "c"; break;
			case FILE_D: return_value = "d"; break;
			case FILE_E: return_value = "e"; break;
			case FILE_F: return_value = "f"; break;
			case FILE_G: return_value = "g"; break;
			case FILE_H: return_value = "h"; break;
			
			default: break;
		}
		return return_value;
	};

  std::string int_to_rank(int rank) {
		return std::to_string(8 - rank);
	};







///////////////////////////////////////////////////////////////////////////////////////////////////////
// MOVE RELATED METHODS SUCH AS PROMOTION OR FINDING ALL LEGAL MOVES //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////


  



// stick this at the bottom because it is so damn long
///////////////////////////////////////////////////////////////////////////////////////////////////////
// LET'S MOVE TONIGHT! SHARE THE SPICE OF LIFE!! //////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
// MOVES ARE IN THE FOLLOWING ORDER: QUEEN, ROOK, BISHOP, KING, KNIGHT, PAWN

  void queen_moves(int rank, int file, std::vector<Move>& moves) {
    rook_moves(rank, file, moves);
    bishop_moves(rank, file, moves);
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////

  void rook_moves(int rank, int file, std::vector<Move>& moves) {
    int player = (_board[rank][file] < 6) ? WHITE : BLACK;
    if (player == WHITE) {
      for (int i = file + 1; i <= FILE_H; i++) {
        _wR_sees_squares[rank][i] += 1;
        if (_board[rank][i] == NA) {
          Move pseudo(rank, file, rank, i);
					moves.push_back(pseudo);
					continue;
        } else if (_board[rank][i] > 6) {
          Move pseudo(rank, file, rank, i);
					moves.push_back(pseudo);
        }
        break;
      }

      for (int i = file - 1; i >= FILE_A; i--) {
        _wR_sees_squares[rank][i] += 1;
        if (_board[rank][i] == NA) {
          Move pseudo(rank, file, rank, i);
					moves.push_back(pseudo);
					continue;
        } else if (_board[rank][i] > 6) {
          Move pseudo(rank, file, rank, i);
					moves.push_back(pseudo);
        }
        break;
      }

      for (int i = rank + 1; i <= RANK_1; i++) {
        _wR_sees_squares[i][file] += 1;
        if (_board[i][file] == NA) {
          Move pseudo(rank, file, i, file);
					moves.push_back(pseudo);
					continue;
        } else if (_board[i][file] > 6) {
          Move pseudo(rank, file, i, file);
					moves.push_back(pseudo);
        }
        break;
      }

      for (int i = rank - 1; i >= RANK_8; i--) {
        _wR_sees_squares[i][file] += 1;
        if (_board[i][file] == NA) {
          Move pseudo(rank, file, i, file);
					moves.push_back(pseudo);
					continue;
        } else if (_board[i][file] > 6) {
          Move pseudo(rank, file, i, file);
					moves.push_back(pseudo);
        }
        break;
      }

    } else {
      for (int i = file + 1; i <= FILE_H; i++) {
        _bR_sees_squares[rank][i] += 1;
        if (_board[rank][i] == NA) {
          Move pseudo(rank, file, rank, i);
					moves.push_back(pseudo);
					continue;
        } else if (_board[rank][i] < 6) {
          Move pseudo(rank, file, rank, i);
					moves.push_back(pseudo);
        }
        break;
      }

      for (int i = file - 1; i >= FILE_A; i--) {
        _bR_sees_squares[rank][i] += 1;
        if (_board[rank][i] == NA) {
          Move pseudo(rank, file, rank, i);
					moves.push_back(pseudo);
					continue;
        } else if (_board[rank][i] < 6) {
          Move pseudo(rank, file, rank, i);
					moves.push_back(pseudo);
        }
        break;
      }

      for (int i = rank + 1; i <= RANK_1; i++) {
        _bR_sees_squares[i][file] += 1;
        if (_board[i][file] == NA) {
          Move pseudo(rank, file, i, file);
					moves.push_back(pseudo);
					continue;
        } else if (_board[i][file] < 6) {
          Move pseudo(rank, file, i, file);
					moves.push_back(pseudo);
        }
        break;
      }

      for (int i = rank - 1; i >= RANK_8; i--) {
        _bR_sees_squares[i][file] += 1;
        if (_board[i][file] == NA) {
          Move pseudo(rank, file, i, file);
					moves.push_back(pseudo);
					continue;
        } else if (_board[i][file] < 6) {
          Move pseudo(rank, file, i, file);
					moves.push_back(pseudo);
        }
        break;
      }
    }
  };

///////////////////////////////////////////////////////////////////////////////////////////////////////

  void bishop_moves(int rank, int file, std::vector<Move>& moves) {

    int player = (_board[rank][file] < 6) ? WHITE : BLACK;
		if (player == WHITE) {

			// southeast
			for (int i = 1 ; i < 8; i++){
				if (rank + i > RANK_1 || file + i > FILE_H) break;
				
				_wB_sees_squares[rank + i][file + i] += 1;
				if (_board[rank + i][file + i] == NA) {
					Move pseudolegal_move(rank, file, rank + i, file + i);
					moves.push_back(pseudolegal_move);
					continue;
				} else if (_board[rank + i][file + i] > 6) {
					Move pseudolegal_move(rank, file, rank + i, file + i);
					moves.push_back(pseudolegal_move);
				}
				break;
			}


			// northeast
			for (int i = 1 ; i < 8; i++) {
				if (rank - i < RANK_8 || file + i > FILE_H) break;
				
				_wB_sees_squares[rank - i][file + i] += 1;
				if (_board[rank - i][file + i] == NA) {
					Move pseudolegal_move(rank, file, rank - i, file + i);
					moves.push_back(pseudolegal_move);
					continue;
				} else if (_board[rank - i][file + i] > 6) {
					Move pseudolegal_move(rank, file, rank - i, file + i);
					moves.push_back(pseudolegal_move);
				}
				break;
				
			}

			// northwest
			for (int i = 1 ; i < 8; i++) {
				if (rank - i < RANK_8 || file - i < FILE_A) break;
				
				_wB_sees_squares[rank - i][file - i] += 1;
				if (_board[rank - i][file - i] == NA) {
					Move pseudolegal_move(rank, file, rank - i, file - i);
					moves.push_back(pseudolegal_move);
					continue;
				} else if (_board[rank - i][file -i] > 6) {
					Move pseudolegal_move(rank, file, rank - i, file - i);
					moves.push_back(pseudolegal_move);
				}
				break;
			}

			// southwest
			for (int i = 1 ; i < 8; i++)
			{
				if (rank + i > RANK_1 || file - i < FILE_A) break;
				
				_wB_sees_squares[rank + i][file - i] += 1;
				if (_board[rank + i][file - i] == NA) {
					Move pseudolegal_move(rank, file, rank + i, file - i);
					moves.push_back(pseudolegal_move);
					continue;
				} else if (_board[rank + i][file - i] > 6) {
					Move pseudolegal_move(rank, file, rank + i, file - i);
					moves.push_back(pseudolegal_move);
				}
				break;
				
			}

		} else {
			// southeast
			for (int i = 1 ; i < 8; i++){
				if (rank + i > RANK_1 || file + i > FILE_H) break;
				
				_bB_sees_squares[rank + i][file + i] += 1;
				if (_board[rank + i][file + i] == NA) {
					Move pseudolegal_move(rank, file, rank + i, file + i);
					moves.push_back(pseudolegal_move);
					continue;
				} else if (_board[rank + i][file + i] < 6) {
					Move pseudolegal_move(rank, file, rank + i, file + i);
					moves.push_back(pseudolegal_move);
				}
				break;
			}


			// northeast
			for (int i = 1 ; i < 8; i++) {
				if (rank - i < RANK_8 || file + i > FILE_H) break;
				
				_bB_sees_squares[rank - i][file + i] += 1;
				if (_board[rank - i][file + i] == NA) {
					Move pseudolegal_move(rank, file, rank - i, file + i);
					moves.push_back(pseudolegal_move);
					continue;
				} else if (_board[rank - i][file + i] < 6) {
					Move pseudolegal_move(rank, file, rank - i, file + i);
					moves.push_back(pseudolegal_move);
				}
				break;
				
			}

			// northwest
			for (int i = 1 ; i < 8; i++) {
				if (rank - i < RANK_8 || file - i < FILE_A) break;
				
				_bB_sees_squares[rank - i][file - i] += 1;
				if (_board[rank - i][file - i] == NA) {
					Move pseudolegal_move(rank, file, rank - i, file - i);
					moves.push_back(pseudolegal_move);
					continue;
				} else if (_board[rank - i][file -i] < 6) {
					Move pseudolegal_move(rank, file, rank - i, file - i);
					moves.push_back(pseudolegal_move);
				}
				break;
			}

			// southwest
			for (int i = 1 ; i < 8; i++)
			{
				if (rank + i > RANK_1 || file - i < FILE_A) break;
				
				_bB_sees_squares[rank + i][file - i] += 1;
				if (_board[rank + i][file - i] == NA) {
					Move pseudolegal_move(rank, file, rank + i, file - i);
					moves.push_back(pseudolegal_move);
					continue;
				} else if (_board[rank + i][file - i] < 6) {
					Move pseudolegal_move(rank, file, rank + i, file - i);
					moves.push_back(pseudolegal_move);
				}
				break;
			}
    }
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////



};