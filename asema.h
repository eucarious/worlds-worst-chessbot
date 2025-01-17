#pragma once
#include "shakki.h"
#include <iostream>

// Pelin tilan kuvaaminen ja siihen liittyv�t operaatiot.
class Asema
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

	// LÄKSY
	// Tulosta lauta ascii-grafiikkana (mahdollisesti flagit
	// voisi myös tulostaa jotenkin siististi).
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
				case NA:
					std::cout << "    ";
					break;

				case wP:
					std::cout << " wP ";
					break;

				case bP:
					std::cout << " bP ";
					break;

				case wR:
					std::cout << " wR ";
					break;
				
				case wN:
					std::cout << " wN ";
					break;
				
				case wB:
					std::cout << " wB ";
					break;
				
				case wQ:
					std::cout << " wQ ";
					break;
				
				case wK:
					std::cout << " wK ";
					break;
				
				case bR:
					std::cout << " bR ";
					break;
				
				case bN:
					std::cout << " bN ";
					break;

				case bB:
					std::cout << " bB ";
					break;

				case bQ:
					std::cout << " bQ ";
					break;
				
				case bK:
					std::cout << " bK ";
					break;

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

	// LÄKSY
	// etsii annetun kuninkaan (wK tai bK) 4 / 10 rivin ja linjan
	void find_king(int piece, int& rank, int& file) const { 
		if (!(piece == int(wK) || piece == int(bK))) {
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
