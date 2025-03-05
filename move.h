#pragma once
#include <string>
#include "chess.h"

/**
 * @brief Contains key information about a specific move
 * 
 */
class Move {
private:

  /** Which rank the move starts from */
  int _start_rank; 
  
  /** Which file the move starts from */
  int _start_file; 

  /** Which rank the move ends on */
  int _end_rank; 
  
  /** Which file the move ends on */
  int _end_file; 

  /** Allows the Board class to see the start and end variables */
  friend class Board; 
  
  /** A cout override. Prints the move's string to the console. ('a2a4') */
  friend std::ostream & operator << (std::ostream &out, const Move &m); 
  
  // friend std::istream & operator >> (std::istream &in,  Move &m);

public:

  /** Whether this move is an en passant move */
  bool _en_passant = false; 

  /** Whether this move has a pawn promotion */
  bool _promotion = false;  
  
  /** Which piece the pawn should be promoted to */
  int _promotion_piece = NA; 
  
  /** The move in standard format. Easier to read. ('a2a4') */
  std::string move_string;  
  
  
  Move()
  {}

  Move(int start_rank, int start_file, int end_rank, int end_file) :
  _start_rank(start_rank), _start_file(start_file), _end_rank(end_rank), _end_file(end_file)
  {
    _move_to_string(start_rank, start_file, end_rank, end_file);
  }

  /**
   * @brief Construct a new Move object from a string
   * 
   * @param s The string to be converted into a move
   */
  Move(const std::string& s)
  {
    move_string = s;
    if (s == "undo") {
      return;
    }
    _start_rank = 8 - (s.at(1) - '0');
    _start_file = s.at(0) - 'a';
    _end_rank = 8 - (s.at(3) - '0');
    _end_file = s.at(2) - 'a';
  }

/**
 * @brief Converts a move from ints into a string (e.g. (6,4,4,4) -> ('e2e4'))
 * 
 * @param start_rank The rank the move starts from
 * @param start_file The file the move starts from
 * @param end_rank The rank the move ends on
 * @param end_file The file the move ends on
 */
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
  
/**
 * @brief Converts the move into a string. Does not transfer any special information, such as promotion or en passant
 */
  operator std::string() const { 
    return move_string; 
  };

//  bool operator==(const Move& other); // somethin shrimply aint right. im messing something up im sure
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

// bool Move::operator==(const Move& other) {
//  return move_string == other.move_string;
//}