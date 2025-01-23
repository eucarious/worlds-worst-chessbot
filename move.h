#pragma once
#include <string>
#include "chess.h"
#include <iostream>


// Kuvaa aseman muutosta.
class Move
{
public:

  // Oletuskonstruktori (ei tee oikeastaan mit��n).
	Move()
	{}

  // Alustaa siirron koordinaateista. (a_r, a_l) => (l_r, l_l)
	Move(int start_rank, int start_file, int end_rank, int end_file) :
	_start_rank(start_rank), _start_file(start_file), _end_rank(end_rank), _end_file(end_file)
	{}

	// Konstruktori, jonka avulla siirto-olio alustetaan
	// annetusta merkkijonosta, esim. "e2e4" tai "g8f6".
	Move(const std::string& s)
  {
		int start;
		int end;
		
		switch (s.at(0))
		{
		case 'a': start = 0; break;
		case 'b': start = 1; break;
		case 'c': start = 2; break;
		case 'd': start = 3; break;
		case 'e': start = 4; break;
		case 'f': start = 5; break;
		case 'g': start = 6; break;
		case 'h': start = 7; break;
		
		default: break;
		}

		switch (s.at(2))
		{
		case 'a': end = 0; break;
		case 'b': end = 1; break;
		case 'c': end = 2; break;
		case 'd': end = 3; break;
		case 'e': end = 4; break;
		case 'f': end = 5; break;
		case 'g': end = 6; break;
		case 'h': end = 7; break;
		
		default: break;
		}
		_start_rank = s.at(1) - '0';
		_start_rank = 8 - _start_rank;
		_start_file = start;
		
		_end_rank = s.at(3) - '0';
		_end_rank = 8 - _end_rank;
		_end_file = end;

	}


private:

	int _start_rank; // siirron alkuruudun rivi
	int _start_file; // siirron alkuruudu linja (eli sarake)

	int _end_rank; // siirron loppuruudun rivi
	int _end_file; // siirron loppuruudun linja

	int _promotion_piece = NA; // esim. wQ, wR, bN jne.
	bool _en_passant = false;

	friend class Board;
};
