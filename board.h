#pragma once
#include "chess.h"
#include "move.h"
#include <iostream>
#include <vector>

// Pelin tilan kuvaaminen ja siihen liittyv�t operaatiot.
class Board
{
public:

	// Laudan nappulat. Indeksointi [rivi][linja], esim.
	//
	// [0][0] : vasen yl�nurkka ("a8")
	// [7][0] : vasen alanurkka ("a1")
	// [7][7] : oikea alanurkka ("h1")
	//
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

	// Kumman pelaajan siirtovuoro?
	int _turn = WHITE;

	// Kirjanpito siitä, onko kuningas tai torni liikkunut.
	// Asetetaan tarpeen mukaan falseksi.
	bool _white_short_castle_allowed 	= true;
	bool _white_long_castle_allowed 	= true;
	bool _black_short_castle_allowed 	= true;
	bool _black_long_castle_allowed 	= true;

	// Ohestaly�ntiin tarvittava info. en passant
	int _doublestep_on_file = -1;


	// LÄKSY
	// Tyhjentää laudan.
	void clear() { 
		for (int rank = 0 ; rank < 8 ; rank++) { 
			for (int file = 0 ; file < 8 ; file++) { 
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

	void knight_raw_moves ( int rank, int file, int player, std::vector<Move>& moves) {
		// up
		if (8 > rank - 2 >= 0 && 8 > file - 1 >= 0) {

				if (_board[rank - 2][file - 1] == NA ) {
					Move legal_move(index_to_string(rank, file, rank - 2, file - 1));
					moves.push_back(legal_move);
				} 
				else if ((player == 1 && _board[rank - 2][file - 1] < 6) || 
								 (player == 0 && _board[rank - 2][file - 1] >= 6) ) 
				{
					Move legal_move(index_to_string(rank, file, rank - 2, file - 1));
					moves.push_back(legal_move);
				}

			}

		if ( 8 > rank - 2 >= 0 && 8 > file + 1 >= 0) {

			if (_board[rank - 2][file + 1] == NA ) {
				Move legal_move(index_to_string(rank, file, rank - 2, file + 1));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank - 2][file + 1] < 6) || 
							 (player == 0 && _board[rank - 2][file + 1] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank - 2, file + 1));
				moves.push_back(legal_move);
			}

		}


		// down
		if (8 > rank + 2 >= 0 && 8 > file - 1 >= 0) {

			if (_board[rank + 2][file - 1] == NA ) {
				Move legal_move(index_to_string(rank, file, rank + 2, file - 1));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank + 2][file - 1] < 6) || 
								(player == 0 && _board[rank + 2][file - 1] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank + 2, file - 1));
				moves.push_back(legal_move);
			}

		}

		if (8 > rank + 2 >= 0 && 8 > file + 1 >= 0) {

			if (_board[rank + 2][file + 1] == NA ) {
				Move legal_move(index_to_string(rank, file, rank + 2, file + 1));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank + 2][file + 1] < 6) || 
								(player == 0 && _board[rank + 2][file + 1] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank + 2, file + 1));
				moves.push_back(legal_move);
			}

		}


		//left
		if (8 > rank + 1 >= 0 && 8 > file - 2 >= 0) {

			if (_board[rank + 1][file - 2] == NA ) {
				Move legal_move(index_to_string(rank, file, rank + 1, file - 2));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank + 1][file - 2] < 6) || 
							 (player == 0 && _board[rank + 1][file - 2] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank + 1, file - 2));
				moves.push_back(legal_move);
			}

		}

		if (8 > rank - 1 >= 0 && 8 > file - 2 >= 0) {

			if (_board[rank - 1][file - 2] == NA ) {
				Move legal_move(index_to_string(rank, file, rank - 1, file - 2));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank - 1][file - 2] < 6) || 
							 (player == 0 && _board[rank - 1][file - 2] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank - 1, file - 2));
				moves.push_back(legal_move);
			}

		}

		// right
		if (8 > rank + 1 >= 0 && 8 > file + 2 >= 0) {

			if (_board[rank + 1][file + 2] == NA ) {
				Move legal_move(index_to_string(rank, file, rank + 1, file + 2));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank + 1][file + 2] < 6) || 
							 (player == 0 && _board[rank + 1][file + 2] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank + 1, file + 2));
				moves.push_back(legal_move);
			}

		}

		if (8 > rank - 1 >= 0 && 8 > file + 2 >= 0) {

			if (_board[rank - 1][file + 2] == NA ) {
				Move legal_move(index_to_string(rank, file, rank - 1, file + 2));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank - 1][file + 2] < 6) || 
							 (player == 0 && _board[rank - 1][file + 2] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank - 1, file + 2));
				moves.push_back(legal_move);
			}

		}

	};


	void rook_raw_moves 	( int rank, int file, int player, std::vector<Move>& moves) {
		check_vertical_moves	(rank, file, player, moves);
		check_horizontal_moves(rank, file, player, moves);
	};

	void bishop_raw_moves ( int rank, int file, int player, std::vector<Move>& moves) {
		check_diagonal_moves	(rank, file, player, moves);
	};

	void queen_raw_moves	( int rank, int file, int player, std::vector<Move>& moves) {
		check_vertical_moves	(rank, file, player, moves);
		check_horizontal_moves(rank, file, player, moves);
		check_diagonal_moves	(rank, file, player, moves);
	};

	void king_raw_moves 	( int rank, int file, int player, std::vector<Move>& moves) {
		
		// down
		if (!rank + 1 >= 8) {
			if (_board[rank + 1][file] == NA ) {
			Move legal_move(index_to_string(rank, file, rank + 1, file));
			moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank + 1][file] < 6) || 
							(player == 0 && _board[rank + 1][file] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank + 1, file));
				moves.push_back(legal_move);
			}
		}
		

		// up
		if (!rank - 1 < 0) {
			if (_board[rank - 1][file] == NA ) {
				Move legal_move(index_to_string(rank, file, rank - 1, file));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank - 1][file] < 6) || 
							(player == 0 && _board[rank - 1][file] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank - 1, file));
				moves.push_back(legal_move);
			}
		}

		// left
		if (!file - 1 < 0) {
			if (_board[rank][file - 1] == NA ) {
				Move legal_move(index_to_string(rank, file, rank, file - 1));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank][file - 1] < 6) || 
							(player == 0 && _board[rank][file - 1] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank, file - 1));
				moves.push_back(legal_move);
			}
		}

		// right
		if (!file + 1 >= 8) {
			if (_board[rank][file + 1] == NA ) {
				Move legal_move(index_to_string(rank, file, rank, file + 1));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank][file + 1] < 6) || 
							(player == 0 && _board[rank][file + 1] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank, file + 1));
				moves.push_back(legal_move);
			}
		}

		// right up
		if (! (rank - 1 < 0 || file + 1 >= 8) ) {
			if (_board[rank - 1][file + 1] == NA ) {
				Move legal_move(index_to_string(rank, file, rank - 1, file + 1));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank - 1][file + 1] < 6) || 
							(player == 0 && _board[rank - 1][file + 1] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank - 1, file + 1));
				moves.push_back(legal_move);
			}
		}

		// right down
		if (! (rank + 1 >= 8 || file + 1 >= 8) ) {
			if (_board[rank + 1][file + 1] == NA ) {
				Move legal_move(index_to_string(rank, file, rank + 1, file + 1));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank + 1][file + 1] < 6) || 
							(player == 0 && _board[rank + 1][file + 1] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank + 1, file + 1));
				moves.push_back(legal_move);
			}
		}

		// left up
		if (! (rank - 1 < 0 || file - 1 < 0) ) {
			if (_board[rank - 1][file - 1] == NA ) {
				Move legal_move(index_to_string(rank, file, rank - 1, file - 1));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank - 1][file - 1] < 6) || 
							(player == 0 && _board[rank - 1][file - 1] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank - 1, file - 1));
				moves.push_back(legal_move);
			}
		}

		// left down
		if (! (rank + 1 >= 8 || file - 1 < 0) ) {
			if (_board[rank + 1][file - 1] == NA ) {
				Move legal_move(index_to_string(rank, file, rank + 1, file - 1));
				moves.push_back(legal_move);
			} 
			else if ((player == 1 && _board[rank + 1][file - 1] < 6) || 
							(player == 0 && _board[rank + 1][file - 1] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank + 1, file - 1));
				moves.push_back(legal_move);
			}
		}

	};

	// for White pawns. kings *could* use too, but need an additional check to eat
	void check_up ( int rank, int file, int player, std::vector<Move>& moves) {
	  if (rank - 1 < 0 ) return;
		if (_board[rank - 1][file] == NA) {
			Move legal_move(index_to_string(rank, file, rank - 1, file));
			moves.push_back(legal_move);
		}
	};

	// for White pawns
	void check_up_diagonal ( int rank, int file, int player, std::vector<Move>& moves) {
		if (rank - 1 < 0 ) return;

		if ( 8 > file + 1 >= 0 ) { 
			// right up
    	if ((player == 1 && _board[rank - 1][file + 1] < 6) || 
				(player == 0 && _board[rank - 1][file + 1] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank - 1, file + 1));
				moves.push_back(legal_move);
			}
		}

		if (! file - 1 < 0 ) { 
		// left up
			if ((player == 1 && _board[rank - 1][file - 1] < 6) || 
					(player == 0 && _board[rank - 1][file - 1] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank - 1, file - 1));
				moves.push_back(legal_move);
			}
		}
	};

	// for Black pawns.
	void check_down 		( int rank, int file, int player, std::vector<Move>& moves) {
	  if ( 8 > rank + 1 >= 0 ) return;
		if (_board[rank + 1][file] == NA) {
			Move legal_move(index_to_string(rank, file, rank + 1, file));
			moves.push_back(legal_move);
		}
	};

	// for Black pawns
	void check_down_diagonal ( int rank, int file, int player, std::vector<Move>& moves) {
		if (rank + 1 >= 8 ) return;

		if ( 8 > file + 1 >= 0 ) { 
			// right down
			if ((player == 1 && _board[rank + 1][file + 1] < 6) || 
					(player == 0 && _board[rank + 1][file + 1] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank + 1, file + 1));
				moves.push_back(legal_move);
			}
		}

		if ( 8 > file - 1 >= 0) { 
			// left down
			if ((player == 1 && _board[rank + 1][file - 1] < 6) || 
					(player == 0 && _board[rank + 1][file - 1] >= 6) ) 
			{
				Move legal_move(index_to_string(rank, file, rank + 1, file - 1));
				moves.push_back(legal_move);
			}
		}

	};


	void check_vertical_moves( int rank, int file, int player, std::vector<Move>& moves) {

		for (int i = rank ; i < 8; i++)
		{
			if (_board[i][file] == NA)
			{
				if (i == rank) {continue;}
				
				Move legal_move(index_to_string(rank, file, i, file));
				moves.push_back(legal_move);
			} else {
				if (player == 1 && _board[i][file] < 6) 
				{
					Move legal_move(index_to_string(rank, file, i, file));
					moves.push_back(legal_move);
				} else if (player == 0 && _board[i][file] >= 6) 
				{
					Move legal_move(index_to_string(rank, file, i, file));
					moves.push_back(legal_move);
				}
				break;
			}
		}
		
		for (int i = rank ; i >= 0; i--)
		{
			if (_board[i][file] == NA)
			{
				if (i == rank) {continue;}
				
				Move legal_move(index_to_string(rank, file, i, file));
				moves.push_back(legal_move);
			} else {
				if (player == 1 && _board[i][file] < 6) 
				{
					Move legal_move(index_to_string(rank, file, i, file));
					moves.push_back(legal_move);
				} else if (player == 0 && _board[i][file] >= 6) 
				{
					Move legal_move(index_to_string(rank, file, i, file));
					moves.push_back(legal_move);
				}
				break;
			}
		}

	};

	void check_horizontal_moves(int rank, int file, int player, std::vector<Move>& moves) {

		for (int i = file ; i < 8; i++)
		{
			if (_board[rank][i] == NA)
			{
				if (i == file) {continue;}
				
				Move legal_move(index_to_string(rank, file, rank, i));
				moves.push_back(legal_move);
			} else {
				if (player == 1 && _board[rank][i] < 6) 
				{
				  Move legal_move(index_to_string(rank, file, rank, i));
					moves.push_back(legal_move);
				} else if (player == 0 && _board[rank][i] >= 6) 
				{
					Move legal_move(index_to_string(rank, file, rank, i));
					moves.push_back(legal_move);
				}
				break;
			}
		}
		
		for (int i = file ; i >= 0; i--)
		{
			if (_board[rank][i] == NA)
			{
				if (i == file) {continue;}
				
				Move legal_move(index_to_string(rank, file, rank, i));
				moves.push_back(legal_move);
			} else {
				if (player == 1 && _board[rank][i] < 6) 
				{
				  Move legal_move(index_to_string(rank, file, rank, i));
					moves.push_back(legal_move);
				} else if (player == 0 && _board[rank][i] >= 6) 
				{
					Move legal_move(index_to_string(rank, file, rank, i));
					moves.push_back(legal_move);
				}
				break;
			}
		}

	};

	void check_diagonal_moves(int rank, int file, int player, std::vector<Move>& moves)
	{
			// right side, down
		for (int i = 1 ; i < 8; i++)
		{
			if (rank + i >= 8 || file + i >= 8) {break;}
			
			if (_board[rank + i][file + i] == NA)
			{
				std::cout << "diagonal 1";
				Move legal_move(index_to_string(rank, file, rank + i, file + i));
				moves.push_back(legal_move);
			} else {
				if (player == 1 && _board[rank + i][file + i] < 6) 
				{
				  Move legal_move(index_to_string(rank, file, rank + i, file + i));
					moves.push_back(legal_move);
				} else if (player == 0 && _board[rank + i][file + i] >= 6) 
				{
					Move legal_move(index_to_string(rank, file, rank + i, file + i));
					moves.push_back(legal_move);
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
				
				Move legal_move(index_to_string(rank, file, rank - i, file + i));
				moves.push_back(legal_move);
			} else {
				if (player == 1 && _board[rank - i][file + i] < 6) 
				{
				  Move legal_move(index_to_string(rank, file, rank - i, file + i));
					moves.push_back(legal_move);
				} else if (player == 0 && _board[rank - i][file + i] >= 6) 
				{
					Move legal_move(index_to_string(rank, file, rank - i, file + i));
					moves.push_back(legal_move);
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
				
				Move legal_move(index_to_string(rank, file, rank - i, file - i));
				moves.push_back(legal_move);
			} else {
				if (player == 1 && _board[rank - i][file - i] < 6) 
				{
				  Move legal_move(index_to_string(rank, file, rank - i, file - i));
					moves.push_back(legal_move);
				} else if (player == 0 && _board[rank - i][file -i] >= 6) 
				{
					Move legal_move(index_to_string(rank, file, rank - i, file - i));
					moves.push_back(legal_move);
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
				
				Move legal_move(index_to_string(rank, file, rank + i, file - i));
				moves.push_back(legal_move);
			} else {
				if (player == 1 && _board[rank + i][file - i] < 6) 
				{
				  Move legal_move(index_to_string(rank, file, rank + i, file - i));
					moves.push_back(legal_move);
				} else if (player == 0 && _board[rank + i][file - i] >= 6) 
				{
					Move legal_move(index_to_string(rank, file, rank + i, file - i));
					moves.push_back(legal_move);
				}
				break;
			}
		}


	};

	std::string index_to_string( int start_rank, int start_file, int end_rank, int end_file) {

		std::string move = "";

		switch (start_file)
		{
		case 0: move += 'a'; break;
		case 1: move += 'b'; break;
		case 2: move += 'c'; break;
		case 3: move += 'd'; break;
		case 4: move += 'e'; break;
		case 5: move += 'f'; break;
		case 6: move += 'g'; break;
		case 7: move += 'h'; break;
		
		default: break;
		}

		move += std::to_string(8 - start_rank);


		switch (end_file)
		{
		case 0: move += 'a'; break;
		case 1: move += 'b'; break;
		case 2: move += 'c'; break;
		case 3: move += 'd'; break;
		case 4: move += 'e'; break;
		case 5: move += 'f'; break;
		case 6: move += 'g'; break;
		case 7: move += 'h'; break;
		
		default: break;
		}

		move += std::to_string(8 - end_rank);


		return move;
	};

	void print() const { 
		std::cout << "\n";

		for (int rank = 0 ; rank < 8 ; rank++) { 

			for (size_t i = 0; i < 8; i++)
			{
				std::cout << "+----";
			}
			std::cout << "+";

			std::cout << "\n";

			for (int file = 0 ; file < 8 ; file++) { 
				
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

		for (int i = 0; i < 8; i++)
			{
				std::cout << "+----";
			}
		std::cout << "+";

		std::cout << "\n";
	};;

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
