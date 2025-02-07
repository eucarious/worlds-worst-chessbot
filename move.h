#pragma once
#include <string>
#include "chess.h"
#include <iostream>


// Kuvaa aseman muutosta.
class Move
{
public:

  // Oletuskonstruktori (ei tee oikeastaan mitään).

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
			case 'a': start = FILE_A; break;
			case 'b': start = FILE_B; break;
			case 'c': start = FILE_C; break;
			case 'd': start = FILE_D; break;
			case 'e': start = FILE_E; break;
			case 'f': start = FILE_F; break;
			case 'g': start = FILE_G; break;
			case 'h': start = FILE_H; break;
		
			default: break;

		}

		switch (s.at(2))
		{
			case 'a': end = FILE_A; break;
			case 'b': end = FILE_B; break;
			case 'c': end = FILE_C; break;
			case 'd': end = FILE_D; break;
			case 'e': end = FILE_E; break;
			case 'f': end = FILE_F; break;
			case 'g': end = FILE_G; break;
			case 'h': end = FILE_H; break;
			
			default: break;
		}
		//* add move verifier 
    	_start_rank = s.at(1) - '0';
			_start_rank = 8 - _start_rank;
			_start_file = start;

			
			_end_rank = s.at(3) - '0';
			_end_rank = 8 - _end_rank;
			_end_file = end;

    	move_string = s;
	}

	void move_to_string(int start_rank, int start_file, int end_rank, int end_file) {

		move_string = "";

		switch (start_file)
		{
			case FILE_A: move_string += 'a'; break;
			case FILE_B: move_string += 'b'; break;
			case FILE_C: move_string += 'c'; break;
			case FILE_D: move_string += 'd'; break;
			case FILE_E: move_string += 'e'; break;
			case FILE_F: move_string += 'f'; break;
			case FILE_G: move_string += 'g'; break;
			case FILE_H: move_string += 'h'; break;
			
			default: std::cout << "error in move_to_string. start file"; break;
		}

		move_string += std::to_string(8 - start_rank);

		switch (end_file)
		{
			case FILE_A: move_string += 'a'; break;
			case FILE_B: move_string += 'b'; break;
			case FILE_C: move_string += 'c'; break;
			case FILE_D: move_string += 'd'; break;
			case FILE_E: move_string += 'e'; break;
			case FILE_F: move_string += 'f'; break;
			case FILE_G: move_string += 'g'; break;
			case FILE_H: move_string += 'h'; break;
			
			default: std::cout << "error in move_to_string. end file"; break;
		}

		move_string += std::to_string(8 - end_rank);
    
	};


	operator std::string() const { 
		return move_string; 
	};

private:

	int _start_rank;
	int _start_file;

	int _end_rank;
	int _end_file;


	std::string move_string;
	
	int _promotion_piece = NA; // esim. wQ, wR, bN jne.
	bool _en_passant = false;
	

	friend class Board;
	friend std::ostream & operator << (std::ostream &out, const Move &m);
  	// friend std::istream & operator >> (std::istream &in,  Move &m);
};





// cout and cin operator overiders

std::ostream& operator << (std::ostream& out, const Move& m) {
  out << m.move_string;
  return out;
};


// for testing
std::istream & operator >> (std::istream &in, Move &m) {
     std::cout << "submit a move in 'a2a4' format: ";
     std::string move_test;
     in >> move_test;
     m = Move(move_test);

     return in;
};


