#pragma once
#include <string>
#include "chess.h"

class Move {
private:

  int _start_rank;
  int _start_file;

  int _end_rank;
  int _end_file;

  friend class Board;
  friend std::ostream & operator << (std::ostream &out, const Move &m);
  // friend std::istream & operator >> (std::istream &in,  Move &m);

public:

  bool _en_passant = false;
  bool _promotion = false;
  int _promotion_piece = NA;
  std::string move_string;
  
  
  Move()
  {}

  Move(int start_rank, int start_file, int end_rank, int end_file) :
  _start_rank(start_rank), _start_file(start_file), _end_rank(end_rank), _end_file(end_file)
  {
    _move_to_string(start_rank, start_file, end_rank, end_file);
  }

  Move(const std::string& s)
  {
    move_string = s;
    _start_rank = 8 - (s.at(1) - '0');
    _start_file = s.at(0) - 'a';
    _end_rank = 8 - (s.at(3) - '0');
    _end_file = s.at(2) - 'a';
  }

  void _move_to_string(int start_rank, int start_file, int end_rank, int end_file) {
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
    }
    move_string += std::to_string(8 - end_rank);
  }
  
  operator std::string() const { 
    return move_string; 
  };

  bool operator==(const Move& other); // somethin shrimply aint right. im messing something up im sure
};


std::ostream& operator << (std::ostream& out, const Move& m) {
  out << m.move_string;
  return out;
};

std::istream & operator >> (std::istream &in, Move &m) {
  std::string move_test;
  in >> move_test;
  m = Move(move_test);

  return in;
};

bool Move::operator==(const Move& other) {
  return move_string == other.move_string;
}