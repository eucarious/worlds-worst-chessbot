#pragma once
#include "chess.h"
#include "move.h"
#include <iostream>
#include <string>
#include <vector>



class Board
{
public:

	int _board[8][8] = {
		{ bR, bN, bB, bQ, bK, bB, bN, bR },
		{ bP, bP, bP, bP, bP, bP, bP, bP },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ wP, wP, wP, wP, wP, wP, wP, wP },
		{ wR, wN, wB, wQ, wK, wB, wN, wR }
	};

	// char for less storage individually since i really only need a yes or no. 
	// char doesnt print easy so change to ints for printing

	//* make an 8x8 of attacked squares per piece type AND a general one. that's 14 boards.
	// hey it's almost like i'm almost working with bitboards 
	// (i am absolutely not working with bitboards)
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
	// includes bQ's axis moves
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
	// includes bQ's diagonal moves
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
	// includes wR's axis moves
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
	// includes wQ's diagonal moves
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

	// for checking if king is under attack, keep a copy of every threatened tile for each color?
	// like just a list of all moves, and if the king's position is in the second half (like: a2**b1**)
	// the king will be in check.
	// the threatened tile list needs to be created AFTER a potential move
	// and i'll need to keep track of the kings' positions

	

	int _turn = WHITE;

	bool _white_short_castle_allowed 	= true;
	bool _white_long_castle_allowed 	= true;
	bool _black_short_castle_allowed 	= true;
	bool _black_long_castle_allowed 	= true;

	int _doublestep_on_file = -1;

	// STACK MATRICES

	void stack_white_attacks() {
		for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
			for (int file = FILE_A ; file <= FILE_H ; file++) { 
				_white_sees_squares[rank][file] += _wP_sees_squares[rank][file];
				_white_sees_squares[rank][file] += _wR_sees_squares[rank][file];
				_white_sees_squares[rank][file] += _wN_sees_squares[rank][file];
				_white_sees_squares[rank][file] += _wB_sees_squares[rank][file];
				_white_sees_squares[rank][file] += _wK_sees_squares[rank][file];
			}
		}
	};

	void stack_black_attacks() {
		for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
			for (int file = FILE_A ; file <= FILE_H ; file++) { 
				_black_sees_squares[rank][file] += _bP_sees_squares[rank][file];
				_black_sees_squares[rank][file] += _bR_sees_squares[rank][file];
				_black_sees_squares[rank][file] += _bN_sees_squares[rank][file];
				_black_sees_squares[rank][file] += _bB_sees_squares[rank][file];
				_black_sees_squares[rank][file] += _bK_sees_squares[rank][file];
			}
		}
	};


	// VARIOUS CLEARS

	void clear_board() { 
		for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
			for (int file = FILE_A ; file <= FILE_H ; file++) { 
				_board[rank][file] = NA;
			}
		}
	};

	void clear_white() { 
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

	void clear_black() { 
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

	// Tekee annetun siirron laudalla. Voidaan olettaa, että
	// siirto on laillinen.
	void move_piece(const Move& s) {

		int piece = _board[s._start_rank][s._start_file];
	
		_board[s._start_rank][s._start_file] = NA;
		_board[s._end_rank][s._end_file] = piece;
	
	};


	void player_move(int player, const Move& s) {

		int piece = _board[s._start_rank][s._start_file];
	
		_board[s._start_rank][s._start_file] = NA;
		_board[s._end_rank][s._end_file] = piece;

		if (_turn == WHITE) {
			_turn = BLACK;
		} else {
			_turn = WHITE;
		} 
	
	};

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




	std::string index_to_string( int start_rank, int start_file, int end_rank, int end_file) {

		std::string move = "";

		switch (start_file)
		{
			case FILE_A: move += 'a'; break;
			case FILE_B: move += 'b'; break;
			case FILE_C: move += 'c'; break;
			case FILE_D: move += 'd'; break;
			case FILE_E: move += 'e'; break;
			case FILE_F: move += 'f'; break;
			case FILE_G: move += 'g'; break;
			case FILE_H: move += 'h'; break;
			
			default: break;
		}

		move += std::to_string(8 - start_rank);


		switch (end_file)
		{
			case FILE_A: move += 'a'; break;
			case FILE_B: move += 'b'; break;
			case FILE_C: move += 'c'; break;
			case FILE_D: move += 'd'; break;
			case FILE_E: move += 'e'; break;
			case FILE_F: move += 'f'; break;
			case FILE_G: move += 'g'; break;
			case FILE_H: move += 'h'; break;
			
			default: break;
		}

		move += std::to_string(8 - end_rank);


		return move;
	};

	void find_king(int piece, int& rank, int& file) const { 
		if (!(piece == wK || piece == bK)) {
			std::cout << "hey... that's not a king... :(";
			return;
		} 

		
		for (int _rank = 0 ; _rank < 8 ; _rank++) { 
			for (int _file = 0 ; _file < 8 ; _file++) { 
				if (_board[_rank][_file] == piece) {
					rank = _rank;
					file = _file;
					return;
				}
			}
		}

		rank = -1;
		file = -1;
	};




// PAWN PROMOTION

	void promote_pawn() {

	};

// SQUARE CHECKING

	bool is_square_threatened( int rank, int file, int player, std::vector<Move>& moves ) const {

		return false;
	};

// MOVES


//* WRITE legal moves list

	void get_moves(	std::vector<Move>& moves ) {

	};


//* fix all moves to update their own "attacked squares" matrix and for the get raw moves to compile them(?)

	void get_raw_moves( int player, std::vector<Move>& moves ) {
		
		if ( player == WHITE ) {
			clear_white();
			for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
				for (int file = FILE_A ; file <= FILE_H ; file++) { 
					int piece = _board[rank][file];
					switch (piece)
					{
						case NA: break;
						case wP: 
							pawn_raw_moves(rank, file, player, moves);
							break;
						case wR:
							rook_raw_moves(rank, file, player, moves);
							break;
						case wN:
							knight_raw_moves(rank, file, player, moves);
							break;
						case wB:
							bishop_raw_moves(rank, file, player, moves);
							break;
						case wQ:
							queen_raw_moves(rank, file, player, moves);
							break;
						case wK:
							king_raw_moves(rank, file, player, moves);
							break;
						default: break;
					}
				}
			}
			stack_white_attacks();
		} else {
			clear_black();
			for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
				for (int file = FILE_A ; file <= FILE_H ; file++) { 
					int piece = _board[rank][file];
					switch (piece)
					{
						case NA: break;
						case bP: 
							pawn_raw_moves(rank, file, player, moves);
							break;
						case bR:
							rook_raw_moves(rank, file, player, moves);
							break;
						case bN:
							knight_raw_moves(rank, file, player, moves);
							break;
						case bB:
							bishop_raw_moves(rank, file, player, moves);
							break;
						case bQ:
							queen_raw_moves(rank, file, player, moves);
							break;
						case bK:
							king_raw_moves(rank, file, player, moves);
							break;
						default: break;
					}
				}
			}
			stack_white_attacks();
		}
	};

//* fix. every, darn, move.
//* especially the knight. holy shit man 
	void knight_raw_moves ( int rank, int file, int player, std::vector<Move>& moves ) {
		// white
		if (player == WHITE) {
			// nonowe
			if ( 8 > rank - 2 && rank - 2 >= 0 && 8 > file - 1 && file - 1 >= 0) {
				_wK_sees_squares[rank - 2][file - 1] += 1;
				if (_board[rank - 2][file - 1] == NA ) {
					Move pseudolegal_move(index_to_string(rank, file, rank - 2, file - 1));
					moves.push_back(pseudolegal_move);
				} else if (_board[rank - 2][file - 1] >= 6) {
					Move pseudolegal_move(index_to_string(rank, file, rank - 2, file - 1));
					moves.push_back(pseudolegal_move);
				}
			}
			// nonoea
			if ( 8 > rank - 2 && rank - 2 >= 0 && 8 > file + 1 && file + 1 >= 0) {
				_wK_sees_squares[rank - 2][file + 1] += 1;
				if (_board[rank - 2][file + 1] == NA ) {
					Move pseudolegal_move(index_to_string(rank, file, rank - 2, file + 1));
					moves.push_back(pseudolegal_move);
				} else if (_board[rank - 2][file + 1] >= 6) {
					Move pseudolegal_move(index_to_string(rank, file, rank - 2, file + 1));
					moves.push_back(pseudolegal_move);
				}
			}

			// sosowe
			if (8 > rank + 2 && rank + 2 >= 0 && 8 > file - 1 && file - 1 >= 0) {
				_wK_sees_squares[rank + 2][file - 1] += 1;
				if (_board[rank + 2][file - 1] == NA ) {
					Move pseudolegal_move(index_to_string(rank, file, rank + 2, file - 1));
					moves.push_back(pseudolegal_move);
				} else if (_board[rank + 2][file - 1] >= 6) {
					Move pseudolegal_move(index_to_string(rank, file, rank + 2, file - 1));
					moves.push_back(pseudolegal_move);
				}
			}
			// sosoea
			if (8 > rank + 2 && rank + 2 >= 0 && 8 > file + 1 && file + 1 >= 0) {
				_wK_sees_squares[rank + 2][file + 1] += 1;
				if (_board[rank + 2][file + 1] == NA ) {
					Move pseudolegal_move(index_to_string(rank, file, rank + 2, file + 1));
					moves.push_back(pseudolegal_move);
				} else if (_board[rank + 2][file + 1] >= 6) {
					Move pseudolegal_move(index_to_string(rank, file, rank + 2, file + 1));
					moves.push_back(pseudolegal_move);
				}
			}
		} else {
			// nonowe
			if ( 8 > rank - 2 && rank - 2 >= 0 && 8 > file - 1 && file - 1 >= 0) {
				_bK_sees_squares[rank - 2][file - 1] += 1;
				if (_board[rank - 2][file - 1] == NA ) {
					Move pseudolegal_move(index_to_string(rank, file, rank - 2, file - 1));
					moves.push_back(pseudolegal_move);
					} else if (_board[rank - 2][file - 1] < 6) {
					Move pseudolegal_move(index_to_string(rank, file, rank - 2, file - 1));
					moves.push_back(pseudolegal_move);
				}
			}
			// nonoea
			if ( 8 > rank - 2 && rank - 2 >= 0 && 8 > file + 1 && file + 1 >= 0) {
				_bK_sees_squares[rank - 2][file + 1] += 1;
				if (_board[rank - 2][file + 1] == NA ) {
					Move pseudolegal_move(index_to_string(rank, file, rank - 2, file + 1));
					moves.push_back(pseudolegal_move);
				} else if (_board[rank - 2][file + 1] < 6) {
					Move pseudolegal_move(index_to_string(rank, file, rank - 2, file + 1));
					moves.push_back(pseudolegal_move);
				}
			}

			// sosowe
			if (8 > rank + 2 && rank + 2 >= 0 && 8 > file - 1 && file - 1 >= 0) {
				_bK_sees_squares[rank + 2][file - 1] += 1;
				if (_board[rank + 2][file - 1] == NA ) {
					Move pseudolegal_move(index_to_string(rank, file, rank + 2, file - 1));
					moves.push_back(pseudolegal_move);
				} else if (_board[rank + 2][file - 1] < 6) {
					Move pseudolegal_move(index_to_string(rank, file, rank + 2, file - 1));
					moves.push_back(pseudolegal_move);
				}
			}
			// sosoea
			if (8 > rank + 2 && rank + 2 >= 0 && 8 > file + 1 && file + 1 >= 0) {
				_bK_sees_squares[rank + 2][file + 1] += 1;
				if (_board[rank + 2][file + 1] == NA ) {
					Move pseudolegal_move(index_to_string(rank, file, rank + 2, file + 1));
					moves.push_back(pseudolegal_move);
				} else if ((_board[rank + 2][file + 1] < 6)) {
					Move pseudolegal_move(index_to_string(rank, file, rank + 2, file + 1));
					moves.push_back(pseudolegal_move);
				}
			}
		}





		//left
		if (8 > rank + 1 && rank + 1 >= 0 && 8 > file - 2 && file - 2 >= 0) {

			if (_board[rank + 1][file - 2] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank + 1, file - 2));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank + 1][file - 2] < 6) || 
							 (player == 0 && _board[rank + 1][file - 2] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank + 1, file - 2));
				moves.push_back(pseudolegal_move);
			}

		}

		if (8 > rank - 1 && rank - 1 >= 0 && 8 > file - 2 && file - 2 >= 0) {

			if (_board[rank - 1][file - 2] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank - 1, file - 2));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank - 1][file - 2] < 6) || 
							 (player == 0 && _board[rank - 1][file - 2] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank - 1, file - 2));
				moves.push_back(pseudolegal_move);
			}

		}

		// right
		if (8 > rank + 1 && rank + 1 >= 0 && 8 > file + 2 && file + 2 >= 0) {

			if (_board[rank + 1][file + 2] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank + 1, file + 2));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank + 1][file + 2] < 6) || 
							 (player == 0 && _board[rank + 1][file + 2] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank + 1, file + 2));
				moves.push_back(pseudolegal_move);
			}

		}

		if (8 > rank - 1 && rank - 1 >= 0 && 8 > file + 2 && file + 2 >= 0) {

			if (_board[rank - 1][file + 2] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank - 1, file + 2));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank - 1][file + 2] < 6) || 
							 (player == 0 && _board[rank - 1][file + 2] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank - 1, file + 2));
				moves.push_back(pseudolegal_move);
			}

		}

	};

	void rook_raw_moves 	( int rank, int file, int player, std::vector<Move>& moves ) {
		check_vertical_moves   (rank, file, player, moves);
		check_horizontal_moves (rank, file, player, moves);

	};

	void bishop_raw_moves ( int rank, int file, int player, std::vector<Move>& moves ) {
		check_diagonal_moves	(rank, file, player, moves);
	};

	void queen_raw_moves	( int rank, int file, int player, std::vector<Move>& moves ) {
		check_vertical_moves	(rank, file, player, moves);
		check_horizontal_moves(rank, file, player, moves);
		check_diagonal_moves	(rank, file, player, moves);
	};

	void king_raw_moves 	( int rank, int file, int player, std::vector<Move>& moves ) {
		
		// down
		if (!rank + 1 >= 8) {
			if (_board[rank + 1][file] == NA ) {
			Move pseudolegal_move(index_to_string(rank, file, rank + 1, file));
			moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank + 1][file] < 6) || 
							(player == 0 && _board[rank + 1][file] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank + 1, file));
				moves.push_back(pseudolegal_move);
			}
		}
		

		// up
		if (!rank - 1 < 0) {
			if (_board[rank - 1][file] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank - 1, file));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank - 1][file] < 6) || 
							(player == 0 && _board[rank - 1][file] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank - 1, file));
				moves.push_back(pseudolegal_move);
			}
		}

		// left
		if (!file - 1 < 0) {
			if (_board[rank][file - 1] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank, file - 1));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank][file - 1] < 6) || 
							(player == 0 && _board[rank][file - 1] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank, file - 1));
				moves.push_back(pseudolegal_move);
			}
		}

		// right
		if (!file + 1 >= 8) {
			if (_board[rank][file + 1] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank, file + 1));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank][file + 1] < 6) || 
							(player == 0 && _board[rank][file + 1] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank, file + 1));
				moves.push_back(pseudolegal_move);
			}
		}

		// right up
		if (! (rank - 1 < 0 || file + 1 >= 8) ) {
			if (_board[rank - 1][file + 1] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank - 1, file + 1));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank - 1][file + 1] < 6) || 
							(player == 0 && _board[rank - 1][file + 1] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank - 1, file + 1));
				moves.push_back(pseudolegal_move);
			}
		}

		// right down
		if (! (rank + 1 >= 8 || file + 1 >= 8) ) {
			if (_board[rank + 1][file + 1] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank + 1, file + 1));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank + 1][file + 1] < 6) || 
							(player == 0 && _board[rank + 1][file + 1] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank + 1, file + 1));
				moves.push_back(pseudolegal_move);
			}
		}

		// left up
		if (! (rank - 1 < 0 || file - 1 < 0) ) {
			if (_board[rank - 1][file - 1] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank - 1, file - 1));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank - 1][file - 1] < 6) || 
							(player == 0 && _board[rank - 1][file - 1] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank - 1, file - 1));
				moves.push_back(pseudolegal_move);
			}
		}

		// left down
		if (! (rank + 1 >= 8 || file - 1 < 0) ) {
			if (_board[rank + 1][file - 1] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank + 1, file - 1));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank + 1][file - 1] < 6) || 
							(player == 0 && _board[rank + 1][file - 1] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank + 1, file - 1));
				moves.push_back(pseudolegal_move);
			}
		}

	};

	void pawn_raw_moves		( int rank, int file, int player, std::vector<Move>& moves ) {
		if (player == WHITE) {
			check_up(rank, file, player, moves);
			check_up_diagonal(rank, file, player, moves);
		} else {
			check_down(rank, file, player, moves);
			check_down_diagonal(rank, file, player, moves);
		}
	}

	// for White pawns. kings *could* use too, but need an additional check to eat
	void check_up ( int rank, int file, int player, std::vector<Move>& moves) {
	  if (rank - 1 < RANK_8 ) return;
		
		if (_board[rank - 1][file] == NA) {
			Move pseudolegal_move(index_to_string(rank, file, rank - 1, file));
			moves.push_back(pseudolegal_move);

			if (_board[rank - 2][file] == NA && rank == RANK_2) {
				Move pseudolegal_move(index_to_string(rank, file, rank - 2, file));
				moves.push_back(pseudolegal_move);
				_doublestep_on_file = file;
			}
		}
	};

	// for White pawns
	void check_up_diagonal ( int rank, int file, int player, std::vector<Move>& moves ) {
		if (rank - 1 < 0 ) return;

		if (8 > file + 1 && file + 1 >= 0) { 
			// right up
			_wP_sees_squares[rank - 1][file + 1] += 1;
			if (_board[rank - 1][file + 1] != NA) {
				if (_board[rank - 1][file + 1] >= 6 ) {
					Move pseudolegal_move(index_to_string(rank, file, rank - 1, file + 1));
					moves.push_back(pseudolegal_move);
				}
			}
		}

		if (file - 1 >= FILE_A) { 
		// left up
			_wP_sees_squares[rank - 1][file - 1] += 1;
			if (_board[rank - 1][file - 1] != NA) {
				if ((player == 1 && _board[rank - 1][file - 1] < 6) || 
						(player == 0 && _board[rank - 1][file - 1] >= 6) ) 
				{
					Move pseudolegal_move(index_to_string(rank, file, rank - 1, file - 1));
					moves.push_back(pseudolegal_move);
				}
			}
		}
	};

	// for Black pawns.
	void check_down 		( int rank, int file, int player, std::vector<Move>& moves ) {
	  if ( rank + 1 > RANK_1 ) {
			return;
			}
		
		if (_board[rank + 1][file] == NA) {
			Move pseudolegal_move(index_to_string(rank, file, rank + 1, file));
			moves.push_back(pseudolegal_move);

			if (_board[rank + 2][file] == NA && rank == RANK_7) {
				Move pseudolegal_move(index_to_string(rank, file, rank + 2, file));
				moves.push_back(pseudolegal_move);
				_doublestep_on_file = file;
			}
		}
	};

	// for Black pawns
	void check_down_diagonal ( int rank, int file, int player, std::vector<Move>& moves ) {
		if (rank + 1 >= 8) return;
		if (8 > file + 1 && file + 1 >= 0) { 
			// right down
			if (_board[rank - 1][file + 1] != NA) {
				if ((player == 1 && _board[rank + 1][file + 1] < 6) || 
						(player == 0 && _board[rank + 1][file + 1] >= 6) ) 
				{
					Move pseudolegal_move(index_to_string(rank, file, rank + 1, file + 1));
					moves.push_back(pseudolegal_move);
				}
			}
		}

		if (FILE_H >= file - 1) { 
			// left down
			if (_board[rank - 1][file - 1] != NA) {
				if ((player == 1 && _board[rank + 1][file - 1] < 6) || 
						(player == 0 && _board[rank + 1][file - 1] >= 6) ) 
				{
					Move pseudolegal_move(index_to_string(rank, file, rank + 1, file - 1));
					moves.push_back(pseudolegal_move);
				}	
			}
		}
	
	};

	void check_vertical_moves(int rank, int file, int player, std::vector<Move>& moves ) {

		if (player == WHITE) {
			
			for (int i = rank + 1 ; i <= RANK_1; i++) { 
				_wR_sees_squares[i][file] += 1;
				if (_board[i][file] == NA) {
					Move pseudolegal_move(index_to_string(rank, file, i, file));
					moves.push_back(pseudolegal_move);
					continue;
				} else if (_board[i][file] >= 6) {
					Move pseudolegal_move(index_to_string(rank, file, i, file));
					moves.push_back(pseudolegal_move);
				}
				break;
			}

			for (int i = rank - 1 ; i >= RANK_8; i--) {
				_wR_sees_squares[i][file] += 1;
				if (_board[i][file] == NA) {
					Move pseudolegal_move(index_to_string(rank, file, i, file));
					moves.push_back(pseudolegal_move);
					continue;
				} else if (_board[i][file] >= 6) {
					Move pseudolegal_move(index_to_string(rank, file, i, file));
					moves.push_back(pseudolegal_move);
				}
				break;
			}
		} else {

			for (int i = rank + 1 ; i <= RANK_1; i++)
			{
				_bP_sees_squares[i][file] += 1;
				if (_board[i][file] == NA) {
					Move pseudolegal_move(index_to_string(rank, file, i, file));
					moves.push_back(pseudolegal_move);
					continue;
				} else if (_board[i][file] >= 6) {
					Move pseudolegal_move(index_to_string(rank, file, i, file));
					moves.push_back(pseudolegal_move);
				}
				break;
			}

			for (int i = rank - 1 ; i >= RANK_8; i--)
			{
				_bP_sees_squares[i][file] += 1;
				if (_board[i][file] == NA) {
					Move pseudolegal_move(index_to_string(rank, file, i, file));
					moves.push_back(pseudolegal_move);
					continue;
				} else if (_board[i][file] >= 6) {
					Move pseudolegal_move(index_to_string(rank, file, i, file));
					moves.push_back(pseudolegal_move);
				}
				break;
			}
		}
	};

	void check_horizontal_moves( int rank, int file, int player, std::vector<Move>& moves ) {

		for (int i = file + 1 ; i < 8; i++)
		{
			if (_board[rank][i] == NA)
			{
				
				Move pseudolegal_move(index_to_string(rank, file, rank, i));
				moves.push_back(pseudolegal_move);
			} else {
				if (player == 1 && _board[rank][i] < 6) 
				{
				  Move pseudolegal_move(index_to_string(rank, file, rank, i));
					moves.push_back(pseudolegal_move);
				} else if (player == 0 && _board[rank][i] >= 6) 
				{
					Move pseudolegal_move(index_to_string(rank, file, rank, i));
					moves.push_back(pseudolegal_move);
				}
				break;
			}
		}
		
		for (int i = file - 1 ; i >= 0; i--)
		{
			if (_board[rank][i] == NA)
			{
				
				Move pseudolegal_move(index_to_string(rank, file, rank, i));
				moves.push_back(pseudolegal_move);
			} else {
				if (player == 1 && _board[rank][i] < 6) 
				{
				  Move pseudolegal_move(index_to_string(rank, file, rank, i));
					moves.push_back(pseudolegal_move);
				} else if (player == 0 && _board[rank][i] >= 6) 
				{
					Move pseudolegal_move(index_to_string(rank, file, rank, i));
					moves.push_back(pseudolegal_move);
				}
				break;
			}
		}

	};

	void check_diagonal_moves( int rank, int file, int player, std::vector<Move>& moves ) {
			// right side, down
		for (int i = 1 ; i < 8; i++)
		{
			if (rank + i >= 8 || file + i >= 8) {break;}
			
			if (_board[rank + i][file + i] == NA)
			{
				Move pseudolegal_move(index_to_string(rank, file, rank + i, file + i));
				moves.push_back(pseudolegal_move);
			} else {
				if (player == 1 && _board[rank + i][file + i] < 6) 
				{
				  Move pseudolegal_move(index_to_string(rank, file, rank + i, file + i));
					moves.push_back(pseudolegal_move);
				} else if (player == 0 && _board[rank + i][file + i] >= 6) 
				{
					Move pseudolegal_move(index_to_string(rank, file, rank + i, file + i));
					moves.push_back(pseudolegal_move);
				}
				break;
			}
		}


			// right side, up
		for (int i = 1 ; i < 8; i++)
		{
			if (rank - i < 0 || file + i >= 8) {break;}
			
			if (_board[rank - i][file + i] == NA)
			{
				
				Move pseudolegal_move(index_to_string(rank, file, rank - i, file + i));
				moves.push_back(pseudolegal_move);
			} else {
				if (player == 1 && _board[rank - i][file + i] < 6) 
				{
				  Move pseudolegal_move(index_to_string(rank, file, rank - i, file + i));
					moves.push_back(pseudolegal_move);
				} else if (player == 0 && _board[rank - i][file + i] >= 6) 
				{
					Move pseudolegal_move(index_to_string(rank, file, rank - i, file + i));
					moves.push_back(pseudolegal_move);
				}
				break;
			}
		}

			// left side, up

		for (int i = 1 ; i < 8; i++)
		{
			if (rank - i < 0 || file - i < 0) {break;}
			
			if (_board[rank - i][file - i] == NA)
			{
				
				Move pseudolegal_move(index_to_string(rank, file, rank - i, file - i));
				moves.push_back(pseudolegal_move);
			} else {
				if (player == 1 && _board[rank - i][file - i] < 6) 
				{
				  Move pseudolegal_move(index_to_string(rank, file, rank - i, file - i));
					moves.push_back(pseudolegal_move);
				} else if (player == 0 && _board[rank - i][file -i] >= 6) 
				{
					Move pseudolegal_move(index_to_string(rank, file, rank - i, file - i));
					moves.push_back(pseudolegal_move);
				}
				break;
			}
		}

			// left side, down
		for (int i = 1 ; i < 8; i++)
		{
			if (rank + i >= 8 || file - i < 0) {break;}
			
			if (_board[rank + i][file - i] == NA)
			{
				
				Move pseudolegal_move(index_to_string(rank, file, rank + i, file - i));
				moves.push_back(pseudolegal_move);
			} else {
				if (player == 1 && _board[rank + i][file - i] < 6) 
				{
				  Move pseudolegal_move(index_to_string(rank, file, rank + i, file - i));
					moves.push_back(pseudolegal_move);
				} else if (player == 0 && _board[rank + i][file - i] >= 6) 
				{
					Move pseudolegal_move(index_to_string(rank, file, rank + i, file - i));
					moves.push_back(pseudolegal_move);
				}
				break;
			}
		}


	};

};
