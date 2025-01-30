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

	int _turn = WHITE;

	bool _white_short_castle_allowed 	= true;
	bool _white_long_castle_allowed 	= true;
	bool _black_short_castle_allowed 	= true;
	bool _black_long_castle_allowed 	= true;

	int _doublestep_on_file = -1;

	void clear() { 
		for (int rank = RANK_8 ; rank < RANK_1 ; rank++) { 
			for (int file = FILE_A ; file < FILE_H ; file++) { 
				_board[rank][file] = NA;
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

		if (_turn == 0) {
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

	void get_raw_moves( int player, std::vector<Move>& moves ) {
		for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
			for (int file = FILE_A ; file <= FILE_H ; file++) { 
				int piece = _board[rank][file];
				if ( player == 0 ) {
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
				} else {
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
		}
	};

//* fix. every, darn, move.
//* especially the knight. holy shit man 
	void knight_raw_moves ( int rank, int file, int player, std::vector<Move>& moves ) {
		// up
		if ( 8 > rank - 2 && rank - 2 >= 0 && 8 > file - 1 && file - 1 >= 0) {

				if (_board[rank - 2][file - 1] == NA ) {
					Move pseudolegal_move(index_to_string(rank, file, rank - 2, file - 1));
					moves.push_back(pseudolegal_move);
				} 
				else if ((player == 1 && _board[rank - 2][file - 1] < 6) || 
								 (player == 0 && _board[rank - 2][file - 1] >= 6) ) 
				{
					Move pseudolegal_move(index_to_string(rank, file, rank - 2, file - 1));
					moves.push_back(pseudolegal_move);
				}

			}

		if ( 8 > rank - 2 && rank - 2 >= 0 && 8 > file + 1 && file + 1 >= 0) {

			if (_board[rank - 2][file + 1] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank - 2, file + 1));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank - 2][file + 1] < 6) || 
							 (player == 0 && _board[rank - 2][file + 1] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank - 2, file + 1));
				moves.push_back(pseudolegal_move);
			}

		}


		// down
		if (8 > rank + 2 && rank + 2 >= 0 && 8 > file - 1 && file - 1 >= 0) {

			if (_board[rank + 2][file - 1] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank + 2, file - 1));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank + 2][file - 1] < 6) || 
								(player == 0 && _board[rank + 2][file - 1] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank + 2, file - 1));
				moves.push_back(pseudolegal_move);
			}

		}

		if (8 > rank + 2 && rank + 2 >= 0 && 8 > file + 1 && file + 1 >= 0) {

			if (_board[rank + 2][file + 1] == NA ) {
				Move pseudolegal_move(index_to_string(rank, file, rank + 2, file + 1));
				moves.push_back(pseudolegal_move);
			} 
			else if ((player == 1 && _board[rank + 2][file + 1] < 6) || 
								(player == 0 && _board[rank + 2][file + 1] >= 6) ) 
			{
				Move pseudolegal_move(index_to_string(rank, file, rank + 2, file + 1));
				moves.push_back(pseudolegal_move);
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
		if (player == 0) {
			check_up(rank, file, player, moves);
			check_up_diagonal(rank, file, player, moves);
		} else {
			check_down(rank, file, player, moves);
			check_down_diagonal(rank, file, player, moves);
		}
	}
	
	void promote_pawn() {

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
			}
		}
	};

	// for White pawns
	void check_up_diagonal ( int rank, int file, int player, std::vector<Move>& moves ) {
		if (rank - 1 < 0 ) return;

		if ( 8 > file + 1 && file + 1 >= 0 ) { 
			// right up
			if (_board[rank - 1][file + 1] != NA) {
				if ((player == 1 && _board[rank - 1][file + 1] < 6) || 
						(player == 0 && _board[rank - 1][file + 1] >= 6 ) ) 
				{
					Move pseudolegal_move(index_to_string(rank, file, rank - 1, file + 1));
					moves.push_back(pseudolegal_move);
				}
			}
		}

		if (file - 1 > 0 ) { 
		// left up
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
	  if ( RANK_1 < rank + 1 ) {
			return;
			}
		
		if (_board[rank + 1][file] == NA) {
			Move pseudolegal_move(index_to_string(rank, file, rank + 1, file));
			moves.push_back(pseudolegal_move);

			if (_board[rank + 2][file] == NA && rank == RANK_7) {
			Move pseudolegal_move(index_to_string(rank, file, rank + 2, file));
			moves.push_back(pseudolegal_move);
			}
		}
	};

	// for Black pawns
	void check_down_diagonal ( int rank, int file, int player, std::vector<Move>& moves ) {
		if (rank + 1 && rank + 1 >= 8 ) return;
		if ( 8 > file + 1 && file + 1 >= 0 ) { 
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

		if ( 8 > file - 1 && file - 1 >= 0) { 
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

	void check_vertical_moves( int rank, int file, int player, std::vector<Move>& moves ) {

		for (int i = rank + 1 ; i < 8; i++)
		{
			if (_board[i][file] == NA)
			{
				if (i == rank) {continue;}
				
				Move pseudolegal_move(index_to_string(rank, file, i, file));
				moves.push_back(pseudolegal_move);
			} else {
				if (player == 1 && _board[i][file] < 6) 
				{
					Move pseudolegal_move(index_to_string(rank, file, i, file));
					moves.push_back(pseudolegal_move);
				} else if (player == 0 && _board[i][file] >= 6) 
				{
					Move pseudolegal_move(index_to_string(rank, file, i, file));
					moves.push_back(pseudolegal_move);
				}
				break;
			}
		}
		
		for (int i = rank-1 ; i >= 0; i--)
		{
			if (_board[i][file] == NA)
			{
				if (i == rank) {continue;}
				
				Move pseudolegal_move(index_to_string(rank, file, i, file));
				moves.push_back(pseudolegal_move);
			} else {
				if (player == 1 && _board[i][file] < 6) 
				{
					Move pseudolegal_move(index_to_string(rank, file, i, file));
					moves.push_back(pseudolegal_move);
				} else if (player == 0 && _board[i][file] >= 6) 
				{
					Move pseudolegal_move(index_to_string(rank, file, i, file));
					moves.push_back(pseudolegal_move);
				}
				break;
			}
		}

	};

	void check_horizontal_moves( int rank, int file, int player, std::vector<Move>& moves ) {

		for (int i = file ; i < 8; i++)
		{
			if (_board[rank][i] == NA)
			{
				if (i == file) {continue;}
				
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
		
		for (int i = file-1 ; i >= 0; i--)
		{
			if (_board[rank][i] == NA)
			{
				if (i == file) {continue;}
				
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

	void check_diagonal_moves( int rank, int file, int player, std::vector<Move>& moves )
	{
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
};
