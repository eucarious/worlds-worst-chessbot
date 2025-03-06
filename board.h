#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <limits>

#include "chess.h"
#include "move.h"
#include "evaluation.h"

// int end_of_minimax = 0; // a debugging variable. used to see how many moves have been checked
// int no_more_moves = 0;  // a debugging variable. used to see how many win/draw/lose situations have been encountered
/** Total amount of turns played during this game. Currently only updated during a player's move */
int turns_played = 0;      

/** Keepsrack of all the moves made in the game. */
std::vector<Move> moves;   

/**
 * @brief Keeps track of what move is made and the value of the board after the move. Used in move generation. 
 * 
 */
class MinimaxValue
{
public:
  MinimaxValue(float value, Move move) :
    _value(value), _move(move)
  {};
  
  MinimaxValue()
  {};

  /** The value of the position after the move */
  float _value; 
  
  /** The move that was made */
  Move  _move;  
};

/**
 * @brief The chessboard itself. Keeps track of nearly everything.
 * 
 */
class Board {
public:
  // king related variables
  /** Stores the position of the kings' ranks and files */
  int _wK_rank, _wK_file, _bK_rank, _bK_file; 
  
  /** Keeps track of whether the (current player's) king is in check or not. */
  bool _in_check = false; 

  // game control
  /** Keeps track of the current player */
  int _turn = WHITE; 
  
  /** Determines if the program keeps running. Changed to false upon win/draw/lose */ 
  bool playing = true; 
  //* if i ever get the energy to, get in here and make it so that the player can decide whether to play again or not

  // castling variables
  /** Determines whether castling is allowed at all for White */
  bool _white_castling_allowed = true; 
  
  /** Checks whether White's Rook on file A has been moved. 
   *  If true, Queenside Castling is unavailable for the rest of the game (White) */
  bool _wRA_moved = false; 

  /** Checks whether White's Rook on file H has been moved. 
   *  If true, Kingside Castling is unavailable for the rest of the game (White) */
  bool _wRH_moved = false; 

  /** Determines whether Kingside castling is allowed for White on this turn*/
  bool _wKK_castle_allowed = false; 

  /** Determines whether Queenside castling is allowed for White on this turn*/
  bool _wKQ_castle_allowed = false; 


  /** Determines whether castling is allowed at all for Black */
  bool _black_castling_allowed = true; 

  /** Checks whether Black's Rook on file A has been moved. 
   * If true, Queenside Castling is unavailable for the rest of the game (Black) */
  bool _bRA_moved = false; 

  /** Checks whether Black's Rook on file H has been moved. 
   * If true, Kingside Castling is unavailable for the rest of the game (Black) */
  bool _bRH_moved = false; 

  /** Determines whether Kingside castling is allowed for Black on this turn*/
  bool _bKK_castle_allowed = false; 

  /** Determines whether Queenside castling is allowed for Black on this turn*/
  bool _bKQ_castle_allowed = false; 

  // en passant //* 
  /** Which file a pawn has moved two steps on. See the FILE enum to see which file the int is */
  int _doublestep_on_file = -1; 
  
  /** If en passant can be played this turn. Only valid on the turn immediately after a doublestep */
  bool passantable = false; 

//  Move _last_move; 
/** Keeps track of all legal moves this turn. */
  std::vector<Move> legal_moves; 



  //* don't forget Threefold Repetition (same check 3 times)
  //  Dead Position (probably not possible to do)
  //  int _50_move_rule = 0;
  //  we have an arbiter. we'll be fine if we dont hardcode draw rules (except stalemate)

///////////////////////////////////////////////////////////////////////////////////////////////////////
// BOARD REPRESENTATION AND VARIOUS METHODS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The state of the board. 
 */
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

  //  UNEDITED BOARD FOR U <3
  //  { bR, bN, bB, bQ, bK, bB, bN, bR },
  //  { bP, bP, bP, bP, bP, bP, bP, bP },
  //  { NA, NA, NA, NA, NA, NA, NA, NA },
  //  { NA, NA, NA, NA, NA, NA, NA, NA },
  //  { NA, NA, NA, NA, NA, NA, NA, NA },
  //  { NA, NA, NA, NA, NA, NA, NA, NA },
  //  { wP, wP, wP, wP, wP, wP, wP, wP },
  //  { wR, wN, wB, wQ, wK, wB, wN, wR }

/**
 * @brief Empty every piece on the board.
 */
  void clear_board() {
    for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
      for (int file = FILE_A ; file <= FILE_H ; file++) { 
        _board[rank][file] = NA;
      }
    }
    _wK_rank, _wK_file, _bK_rank, _bK_file = -1;
  }

/**
 * @brief Set the up a debug board. Uses the _board variable's state. For debugging purposes
 */
  void set_up_boardless() { 
    update_all_ad();
    find_kings();
    playing = true;
  }

/**
 * @brief Set the up the board object for play. Clears the _board variable and sets up the standard starting board
 */
  void set_up_board() {
    clear_board();
    clear_black_ad();
    clear_white_ad();

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

    _wRA_moved, _wRH_moved, _bRA_moved, _bRH_moved = false;
    _white_castling_allowed, _black_castling_allowed = true;

    update_all_ad();
    playing = true;
  }

/**
 * @brief Print the board into the console
 */
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
// For the bot to know which squares are seen by enemy / ally pieces.

/**
 * @brief White's 'attack defense' vision map. Every tile with a value above 0 is seen by a white piece. 
 */
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

/**
 * @brief Black's 'attack defense' vision map. Every tile with a value above 0 is seen by a black piece. 
 */
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


/**
 * @brief Clears White's 'attack defense' vision map. 
 */
  void clear_white_ad() { 
    for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
      for (int file = FILE_A ; file <= FILE_H ; file++) { 
        _white_sees_squares[rank][file] = 0;
      }
    }
  };

/**
 * @brief Clears Black's 'attack defense' vision map. 
 */
  void clear_black_ad() { 
    for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
      for (int file = FILE_A ; file <= FILE_H ; file++) { 
        _black_sees_squares[rank][file] = 0;
      }
    }
  };

///////////////////////////////////////////////////////////////////////////////////////////////////////
// PLAYING THE DAMN GAME //////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////


// i cant get verification to work, haha. :,)
// fixed...? 
// not designed to handle 0-0 or 0-0-0 inputs

/** 
 * @brief Handles player made moves. 
 * @param s The move to be made
 */
  void player_move(Move& s) {

    if (s.move_string == "undo") {
      if (moves.empty()) {
        std::cout << "\n" << "No more moves to undo" << "\n";
        return;
      }
      Move undo_move = moves.back();
      int piece = _board[undo_move._end_rank][undo_move._end_file];
      _board[undo_move._start_rank][undo_move._start_file] = piece;
      _board[undo_move._end_rank][undo_move._end_file] = NA;
      moves.pop_back();
      if (_turn == WHITE) { 

        undo_move = moves.back();
        int piece = _board[undo_move._end_rank][undo_move._end_file];
        _board[undo_move._start_rank][undo_move._start_file] = piece;
        _board[undo_move._end_rank][undo_move._end_file] = NA;
        moves.pop_back();
        turns_played--; 
        turns_played--; // for vs CPU (Black)

        // _turn = BLACK;
        // turns_played--; //for player vs player. Requires additional changes in main.
      } else { 
        
        _turn = WHITE;
        turns_played--;
      }
      return;
    }

    bool legal = false;
    for (int i = 0 ; i < legal_moves.size(); i++) {
      if (legal) {break;}
      if (s.move_string == legal_moves.at(i).move_string) {
        legal = true;
        s._en_passant = legal_moves.at(i)._en_passant;
      }
    }

    if (legal) {

      passantable = false;

      int piece = _board[s._start_rank][s._start_file];
      _board[s._start_rank][s._start_file] = NA;
      _board[s._end_rank][s._end_file] = piece;

      if (piece == wK) {
        _wK_rank = s._end_rank;
        _wK_file = s._end_file;

        if (s.move_string == "e1g1") {
          std::cout << "white castled, kingside"; 
          _board[RANK_1][FILE_H] = NA;
          _board[RANK_1][FILE_F] = wR;
        }
        
        if (s.move_string == "e1c1") {
          std::cout << "white castled, queenside"; 
          _board[RANK_1][FILE_A] = NA;
          _board[RANK_1][FILE_D] = wR;
        }
      }

      if (piece == bK) {
        _bK_rank = s._end_rank;
        _bK_file = s._end_file;

        if (s.move_string == "e8g8") {
          std::cout << "black castled, kingside"; 
          _board[RANK_8][FILE_H] = NA;
          _board[RANK_8][FILE_F] = bR;
        }

        if (s.move_string == "e8c8") {
          std::cout << "black castled, queenside"; 
          _board[RANK_8][FILE_A] = NA;
        _board[RANK_8][FILE_D] = bR;
        }
      }

      if (piece == bP) {
        if (s._start_rank == RANK_7 && s._end_rank == RANK_5) {
          passantable = true;
          _doublestep_on_file = s._end_file;
        }
      }
  
      if (piece == wP) {
        if (s._start_rank == RANK_2 && s._end_rank == RANK_4) {
          passantable = true;
          _doublestep_on_file = s._end_file;
        }
      }
  
      if (s._en_passant) {
        _board[s._end_rank][s._end_file] = piece;
        _board[s._start_rank][s._end_file] = NA;
      }
  

      if (piece == wP && s._end_rank == RANK_8) {
        std::string promotion_selection;
        std::cout << "promote your piece! choose between (q)ueen, (k)night, (r)ook, or (b)ishop\n";
        std::cin >> promotion_selection;

        if (promotion_selection == "q" || promotion_selection == "Q") {
          _board[s._end_rank][s._end_file] = wQ;
        }
        if (promotion_selection == "k" || promotion_selection == "K") {
          _board[s._end_rank][s._end_file] = wN;
        }
        if (promotion_selection == "r" || promotion_selection == "R") {
          _board[s._end_rank][s._end_file] = wR;
        }
        if (promotion_selection == "b" || promotion_selection == "B") {
          _board[s._end_rank][s._end_file] = wB;
        }
      }

      if (piece == bP && s._end_rank == RANK_1) {
        std::string promotion_selection;
        std::cout << "promote your piece! choose between (q)ueen, (k)night, (r)ook, or (b)ishop\n";
        std::cin >> promotion_selection;

        if (promotion_selection == "q" || promotion_selection == "Q") {
          _board[s._end_rank][s._end_file] = bQ;
        }
        if (promotion_selection == "k" || promotion_selection == "K") {
          _board[s._end_rank][s._end_file] = bN;
        }
        if (promotion_selection == "r" || promotion_selection == "R") {
          _board[s._end_rank][s._end_file] = bR;
        }
        if (promotion_selection == "b" || promotion_selection == "B") {
          _board[s._end_rank][s._end_file] = bB;
        }
      }

      update_all_ad();

      if (_turn == WHITE) { 
        _turn = BLACK;
        turns_played++;
      } else { 
        _turn = WHITE;
        turns_played++;
      }

      moves.push_back(s);
    }
  };

// for the computer only	

/** 
 * @brief Handles computer made moves.
 * @param s The move to be made
 */
  void make_move(Move& s) {

    passantable = false;
    
    int piece = _board[s._start_rank][s._start_file];
    _board[s._start_rank][s._start_file] = NA;
    _board[s._end_rank][s._end_file] = piece;

    if (piece == wK) {
      _wK_rank = s._end_rank;
      _wK_file = s._end_file;
     
      if (s.move_string == "e1g1") { 
        _board[RANK_1][FILE_H] = NA;
        _board[RANK_1][FILE_F] = wR;
      }
     
      if (s.move_string == "e1c1") {
        _board[RANK_1][FILE_A] = NA;
        _board[RANK_1][FILE_D] = wR;
      }
    }

    if (piece == bK) {
      _bK_rank = s._end_rank;
      _bK_file = s._end_file;
      
      if (s.move_string == "e8g8") {
        _board[RANK_8][FILE_H] = NA;
        _board[RANK_8][FILE_F] = bR;
      }
      
      if (s.move_string == "e8c8") {
        _board[RANK_8][FILE_A] = NA;
        _board[RANK_8][FILE_D] = bR;
      }
    }
      
    if (piece == bP) {
      if (s._start_rank == RANK_7 && s._end_rank == RANK_5) {
        passantable = true;
        _doublestep_on_file = s._end_file;
      }
    }

    if (piece == wP) {
      if (s._start_rank == RANK_2 && s._end_rank == RANK_4) {
        passantable = true;
        _doublestep_on_file = s._end_file;
      }
    }

    if (s._en_passant) {
      _board[s._end_rank][s._end_file] = piece;
      _board[s._start_rank][s._end_file] = NA;
    }


    if (s._promotion) {
      // QUEEN
      if (s._promotion_piece == wQ) {
        _board[s._end_rank][s._end_file] = wQ;
      }
      if (s._promotion_piece == bQ) {
        _board[s._end_rank][s._end_file] = bQ;
      }

      // KNIGHT
      if (s._promotion_piece == wN) {
        _board[s._end_rank][s._end_file] = wN;
      }
      if (s._promotion_piece == bN) {
        _board[s._end_rank][s._end_file] = bN;
      }

      // ROOK
      if (s._promotion_piece == wR) {
        _board[s._end_rank][s._end_file] = wR;
      }
      if (s._promotion_piece == bR) {
        _board[s._end_rank][s._end_file] = bR;
      }

      // BISHOP
      if (s._promotion_piece == wB) {		
        _board[s._end_rank][s._end_file] = wB;
      } 
      if (s._promotion_piece == bB) {
        _board[s._end_rank][s._end_file] = bB;
      }
    }

    update_all_ad();

    if (_turn == WHITE) { 
      _turn = BLACK;
    } else { 
      _turn = WHITE;
    }
  };

///////////////////////////////////////////////////////////////////////////////////////////////////////
// MINIMAX ////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

//* DOES work lmao

  /** 
   * @brief An algorithm that through every possible move and returns the best move for the respective player (up to the depth given)
   * @param depth How many turns down the line is checked.
   * @return MinimaxValue The value of the current board position.
   */ 
  MinimaxValue minimax(int depth) 
  {
    // Generoidaan aseman siirrot.
    std::vector<Move> moves;
    get_moves(moves);

    if (moves.size() == 0)
    {
      // Rekursion kantatapaus 1:
      // peli on päättynyt (ei yhtään laillista siirtoa).
      //no_more_moves++;
      return MinimaxValue((evaluate_result() / float(depth)), Move());
    }

    if (depth == 0)
    {
      // Rekursion kantatapaus 2:
      // ollaan katkaisusyvyydessä.
      //end_of_minimax++;
      return MinimaxValue(evaluate(), Move());
    }

    // Siirtoja on jäljellä ja ei olla katkaisusyvyydessä,
    // joten kokeillaan yksitellen mahdollisia siirtoja,
    // ja kutsutaan minimax:a kullekin seuraaja-asemalle.
    // Otetaan paras minimax-arvo talteen (alustetaan
    // paras_arvo mahdollisimman huonoksi siirtovuoroisen
    // pelaajan kannalta).
    float best_value = _turn == WHITE ?
      -std::numeric_limits<float>::max() : std::numeric_limits<float>::max();
    Move best_move;
    for (Move& s : moves)
    {
      Board uusi = *this;
      uusi.make_move(s);

      // Rekursioasekel: kutsutaan minimax:ia seuraaja-asemalle.
      MinimaxValue value = uusi.minimax(depth - 1);

      // ISSUE W NUMERIC LIMIT!!! //*
      if (_turn == WHITE && (value._value > best_value))
      {
        best_value = value._value;
        best_move = s;
        
      // std::cout << "white best move gotten ";
      }
      else if (_turn == BLACK && (value._value < best_value))
      {
        best_value = value._value;
        best_move = s;
        
      // std::cout << "black best move gotten ";
      // } else {
      // best_value = 0;
      // best_move = s;
      }
    }

    // Palautetaan paras arvo.
    return MinimaxValue(best_value, best_move);
  }

  // hot damn this guy sucks //* (i fucked up the implementation)
  /**
   * @brief An algorithm that  FILL THIS
   * 
   * @param depth How many turns down the line is checked.
   * @param alpha 
   * @param beta 
   * @return MinimaxValue The value of the current board position.
   */
  MinimaxValue alphabeta(int depth, float alpha, float beta) {
    std::vector<Move> moves;
    get_moves(moves);

    if (moves.size() == 0) {
      //no_more_moves++;
      return MinimaxValue((evaluate_result() / float(depth)), Move());
    }

    if (depth == 0) {
      //end_of_minimax++;
      return MinimaxValue(evaluate(), Move());
    }
    
    //* i think i'm stupid. 
    // NEVERMIND I FIXED IT??? (to be determined)
    
    if (_turn == WHITE){
      float best_value = -9000000;
      Move best_move;
      for (Move& s : moves) {
        Board uusi = *this;
        uusi.make_move(s);
        MinimaxValue eval = uusi.alphabeta(depth-1, alpha, beta);
        if (eval._value > best_value) {
        best_value = eval._value;
        best_move = s;
        }
        alpha = std::max(alpha, eval._value);
        if (beta <= alpha) break;
      }
      return MinimaxValue(best_value, best_move);
    } else {
      float best_value = 9000000;
      Move best_move;
      for (Move& s : moves) {
        Board uusi = *this;
        uusi.make_move(s);
        MinimaxValue eval = uusi.alphabeta(depth-1, alpha, beta);
        if (eval._value < best_value) {
        best_value = eval._value;
        best_move = s;
        }
        beta = std::min(beta, eval._value);
        if (beta <= alpha) break;
      }
      return MinimaxValue(best_value, best_move);
    }
  }


///////////////////////////////////////////////////////////////////////////////////////////////////////
// EVALUATION FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// call when no valid moves are left
// WHITE checkmate     100000
// DRAW                0
// BLACK checkmate    -100000

/**
 * @brief Evaluates the end of a game. Called when no legal moves remain.
 * 
 * @return float Determines the outcome of the game. 0 for Draw, 100000 for White Win, -100000 for Black Win.
 */
float evaluate_result() const {
  
  if (_black_sees_squares[_wK_rank][_wK_file] >= 1) {
    return -100000;
  }
   
  if (_white_sees_squares[_bK_rank][_bK_file] >= 1) {
    return  100000;
  }
  return 0;
}

/**
 * @brief Evaluates the current position on the board.
 * 
 * @return float The value of the current position
 */
float evaluate() const {
  return (1.0f * material() + 1.0f * position());
}

/**
 * @brief Calculates the current material value of the board. Includes adjustments to the value for a piece's position on the board.
 * 
 * See piece square tables for details about board position and value adjustments
 * @return float The overall material value of the board.
 */
float material() const {
  float material_result;
  for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) {  
    for (int file = FILE_A ; file <= FILE_H ; file++) { 

      int piece = _board[rank][file];
      // switch with 13 cases? hell yeah
      switch (piece)
      {
        case NA: break;
        case wP: 
          material_result += PAWN_VAL + wP_pcsq[rank][file]; 
          break;
        case bP: 
          material_result -= (PAWN_VAL + bP_pcsq[rank][file]); 
          break;
        case wR: 
          material_result += ROOK_VAL; 
          break;
        case wN: 
          material_result += KNIGHT_VAL + N_pcsq[rank][file]; 
          break;
        case wB: 
          material_result += BISHOP_VAL + wB_pcsq[rank][file]; 
          break;
        case wQ: 
          material_result += QUEEN_VAL; 
          break;
        case wK: 
          if (turns_played >= 50) {
            material_result += end_K_pscq[rank][file]; 
          } else {
            material_result += wK_pcsq[rank][file]; 
          }
          break;
        case bR: 
          material_result -= ROOK_VAL;
          break;
        case bN: 
          material_result -= (KNIGHT_VAL + N_pcsq[rank][file]); 
          break;
        case bB: 
          material_result -= (BISHOP_VAL + bB_pcsq[rank][file]); 
          break;
        case bQ: 
          material_result -= QUEEN_VAL; 
          break;
        case bK: 
          if (turns_played >= 50) {
            material_result -= end_K_pscq[rank][file]; 
          } else {
            material_result -= bK_pcsq[rank][file]; 
          }
          break;

      default:
        std::cout << "SOMETHING'S WRONG IN MATERIAL!!";
        break;
      }
    }
  }
  return material_result;
}

// sliiightly misleading name. just checks how much vision the pieces have on the board
// (goes through both ad maps and returns the difference as one float)
//* add either a "fork checker" / attack n defending pieces checker to position or to a completely new function


//* should be updated (if i ever get the spark to touch this code again)
/**
 * @brief Rudimentary evaluation of the overall positioning on the board. Relies on 'attack defense' vision maps.
 * 
 * @return float Which player's pieces see more of the board and by how much.
 */
float position() const {
  float position_result = 0;
  for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) {  
    for (int file = FILE_A ; file <= FILE_H ; file++) { 
      position_result += (_white_sees_squares[rank][file] - _black_sees_squares[rank][file]);
    }
  }
  return position_result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// MISCELLANEOUS METHODS AND STUFF I HAVEN'T GROUPED //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

//   std::string int_to_file(int file) {
//     std::string return_value;
//     switch (file)
//     {
//       case FILE_A: return_value = "a"; break;
//       case FILE_B: return_value = "b"; break;
//       case FILE_C: return_value = "c"; break;
//       case FILE_D: return_value = "d"; break;
//       case FILE_E: return_value = "e"; break;
//       case FILE_F: return_value = "f"; break;
//       case FILE_G: return_value = "g"; break;
//       case FILE_H: return_value = "h"; break;
      
//       default: break;
//     }
//     return return_value;
//   };

//   std::string int_to_rank(int rank) {
//     return std::to_string(8 - rank);
//   };

/**
 * @brief Search for the position of the kings on the board. Updates their stored positions. Should only called on custom (debug) setups.
 * 
 */
  void find_kings() { 
    for (int _rank = 0 ; _rank < 8 ; _rank++) { 
      for (int _file = 0 ; _file < 8 ; _file++) { 
        if (_board[_rank][_file] == wK) {
          _wK_rank = _rank;
          _wK_file = _file;
        }
        if (_board[_rank][_file] == bK) {
          _bK_rank = _rank;
          _bK_file = _file;
        }
      }
    }
  };



///////////////////////////////////////////////////////////////////////////////////////////////////////
// MOVE RELATED METHODS SUCH AS PROMOTION OR FINDING ALL LEGAL MOVES //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Get all legal moves on this turn
 * 
 * @param moves The Move vector to store the moves in. The vector should not have any data. It will be cleared.
 */
  void get_moves(std::vector<Move>& moves) {
    get_raw_moves(moves);
    for (int i = 0 ; i < moves.size(); i++) {
      Board new_board = *this;
      new_board.make_move(moves[i]);
      new_board.update_all_ad();
      if (new_board.is_in_check()) {
        moves.erase(moves.begin() + i);
        i--;
      }
    }

    // castling has its own check checker
    if (_turn == WHITE) {
      if (_white_castling_allowed) {	
        white_castle_check();
        if (_wKK_castle_allowed) {
          moves.push_back(Move("e1g1"));
        }
        if (_wKQ_castle_allowed) {
          moves.push_back(Move("e1c1"));
        }
      }
    } else {
      if (_black_castling_allowed) {	
        black_castle_check();
        if (_bKK_castle_allowed) {
          moves.push_back(Move("e8g8"));
        }
        if (_bKQ_castle_allowed) {
          moves.push_back(Move("e8c8"));
        }
      }
    }

    // check for (stale)mate
    if(moves.empty()){
      playing = false;
      int result = evaluate_result();
      return;
    }
    
    legal_moves = moves;
  }

/**
 * @brief Determines whether the current player is in check or not
 * 
 * @return true King is in check
 * @return false King is not in check
 */
  bool is_in_check() {
    if (_turn == BLACK) {
      // this checks after a move, which flips the turn to the opponent
      if (_black_sees_squares[_wK_rank][_wK_file] >= 1) {
        return true;
      }
      return false;
    } else {
      if (_white_sees_squares[_bK_rank][_bK_file] >= 1) {
        return true;
      }
      return false;
    }
  }

/**
 * @brief Get all pseudo-legal moves on this turn
 * 
 * @param moves The Move vector to store the moves in. The vector should not have any data. It will be cleared.
 */
  void get_raw_moves(std::vector<Move>& moves) {
    moves.clear();
    if (_turn == WHITE) {
      clear_white_ad();
      for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
        for (int file = FILE_A ; file <= FILE_H ; file++) { 
          int piece = _board[rank][file];
          switch (piece)
          {
            case wP: 
              pawn_moves(rank, file, moves);
              break;
            case wR:
              rook_moves(rank, file, moves);
              break;
            case wN:
              knight_moves(rank, file, moves);
              break;
            case wB:
              bishop_moves(rank, file, moves);
              break;
            case wQ:
              queen_moves(rank, file, moves);
              break;
            case wK:
              king_moves(rank, file, moves);
              break;
            default: break;
          }
        }
      }
    } else {
      clear_black_ad();
      for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
        for (int file = FILE_A ; file <= FILE_H ; file++) { 
          int piece = _board[rank][file];
          switch (piece)
          {
            case bP: 
              pawn_moves(rank, file, moves);
              break;
            case bR:
              rook_moves(rank, file, moves);
              break;
            case bN:
              knight_moves(rank, file, moves);
              break;
            case bB:
              bishop_moves(rank, file, moves);
              break;
            case bQ:
              queen_moves(rank, file, moves);
              break;
            case bK:
              king_moves(rank, file, moves);
              break;
            default: break;
          }
        }
      }
    }
  };


  // castling

/**
 * @brief Checks whether White can castle this turn
 */
  void white_castle_check(){
    // early termination ilu

    // check if the pieces are in the right spots
    if (_board[RANK_1][FILE_E] != wK) {
      _white_castling_allowed = false;
      return;
    }

    if (_board[RANK_1][FILE_H] != wR) {
      _wKK_castle_allowed = false;
      _wRH_moved = true;
    }
    if (_board[RANK_1][FILE_A] != wR) {
      _wKQ_castle_allowed = false;
      _wRA_moved = true;
    }

    // check for check
    if (_black_sees_squares[RANK_1][FILE_E] >= 1) {
      _wKK_castle_allowed = false;
      _wKQ_castle_allowed = false;
      return;
    }

    // check if both rooks have been moved before
    if (_wRA_moved && _wRH_moved) {
      _white_castling_allowed = false;
      return;
    }

    // kingside
    if (_board[RANK_1][FILE_E] == wK && _board[RANK_1][FILE_H] == wR) {
      if (_board[RANK_1][FILE_F] == NA && _board[RANK_1][FILE_G] == NA 
        && _black_sees_squares[RANK_1][FILE_F] == 0 
        && _black_sees_squares[RANK_1][FILE_G] == 0 ) {
        _wKK_castle_allowed = true;
      } else {
        _wKK_castle_allowed = false;
      }
    }

    // queenside
    if (_board[RANK_1][FILE_E] == wK && _board[RANK_1][FILE_A] == wR) {
      if (_board[RANK_1][FILE_B] == NA && _board[RANK_1][FILE_C] == NA && _board[RANK_8][FILE_D] == NA 
        && _black_sees_squares[RANK_1][FILE_C] == 0 
        && _black_sees_squares[RANK_1][FILE_D] == 0 ) {
        _wKQ_castle_allowed = true;
      } else {
        _wKQ_castle_allowed = false;
      }
    }

  }


/**
 * @brief Checks whether Black can castle this turn
 */
  void black_castle_check(){
    // early termination ilu

    // check if the pieces are in the right spots
    if (_board[RANK_8][FILE_E] != bK) {
      _black_castling_allowed = false;
      return;
    }

    if (_board[RANK_8][FILE_H] != bR) {
      _bKK_castle_allowed = false;
      _bRH_moved = true;
    }
    if (_board[RANK_8][FILE_A] != bR) {
      _bKQ_castle_allowed = false;
      _bRA_moved = true;
    }

    // check for check
    if (_white_sees_squares[RANK_8][FILE_E] >= 1) {
      _bKK_castle_allowed = false;
      _bKQ_castle_allowed = false;
      return;
    }

    // check if both rooks have been moved before
    if (_bRA_moved && _bRH_moved) {
      _black_castling_allowed = false;
      return;
    }

    // kingside
    if (_board[RANK_8][FILE_E] == bK && _board[RANK_8][FILE_H] == bR) {
      if (_board[RANK_8][FILE_F] == NA && _board[RANK_8][FILE_G] == NA 
        && _white_sees_squares[RANK_8][FILE_F] == 0 
        && _white_sees_squares[RANK_8][FILE_G] == 0 ) {
        _bKK_castle_allowed = true;
      } else {
        _bKK_castle_allowed = false;
      }
    }

    // queenside
    if (_board[RANK_8][FILE_E] == bK && _board[RANK_8][FILE_A] == bR) {
      if (_board[RANK_8][FILE_B] == NA && _board[RANK_8][FILE_C] == NA && _board[RANK_8][FILE_D] == NA 
        && _white_sees_squares[RANK_8][FILE_C] == 0 
        && _white_sees_squares[RANK_8][FILE_D] == 0 ) {
        _bKQ_castle_allowed = true;
      } else {
        _bKQ_castle_allowed = false;
      }
    }

  }

  // en passant //*


// stick this at the bottom because it is so damn long
///////////////////////////////////////////////////////////////////////////////////////////////////////
// LET'S MOVE TONIGHT! SHARE THE SPICE OF LIFE!! //////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
// MOVES ARE IN THE FOLLOWING ORDER: QUEEN, ROOK, BISHOP, KING, KNIGHT, PAWN

/**
 * @brief Update both White and Black's 'attack defense' vision maps
 */
  void update_all_ad() {
    clear_white_ad();
    clear_black_ad();
    for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
      for (int file = FILE_A ; file <= FILE_H ; file++) { 
        int piece = _board[rank][file];
        switch (piece)
        {
          case wP:
            white_pawn_ad(rank, file);
            break;
          case bP:
            black_pawn_ad(rank, file);
            break;
          case wR:
          case bR:
            rook_ad(rank, file);
            break;
          case wN:
          case bN:
            knight_ad(rank, file);
            break;
          case wB:
          case bB:
            bishop_ad(rank, file);
            break;
          case wQ:
          case bQ:
            queen_ad(rank, file);
            break;
          case wK:
          case bK:
            king_ad(rank, file);
            break;
          default: break;
        }
      }
    }
  }


// individual ad map updates. likely unnecessacy? unless i wanna break move verification into two
// ad map update white

/**
 * @brief Updates White's 'attack defense' vision maps
 */
  void update_white_ad() {
    clear_white_ad();
    for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
      for (int file = FILE_A ; file <= FILE_H ; file++) { 
        int piece = _board[rank][file];
        switch (piece)
        {
          case wP:
            white_pawn_ad(rank, file);
            break;
          case wR:
            rook_ad(rank, file);
            break;
          case wN:
            knight_ad(rank, file);
            break;
          case wB:
            bishop_ad(rank, file);
            break;
          case wQ:
            queen_ad(rank, file);
            break;
          case wK:
            king_ad(rank, file);
            break;
          default: break;
        }
      }
    }
  }

// ad map update black

/**
 * @brief Updates Black's 'attack defense' vision maps
 */
  void update_black_ad() {
    clear_black_ad();
    for (int rank = RANK_8 ; rank <= RANK_1 ; rank++) { 
      for (int file = FILE_A ; file <= FILE_H ; file++) { 
        int piece = _board[rank][file];
        switch (piece)
        {
          case bP:
            black_pawn_ad(rank, file);
            break;
          case bR:
            rook_ad(rank, file);
            break;
          case bN:
            knight_ad(rank, file);
            break;
          case bB:
            bishop_ad(rank, file);
            break;
          case bQ:
            queen_ad(rank, file);
            break;
          case bK:
            king_ad(rank, file);
            break;
          default: break;
        }
      }
    }
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////

// for move generation
/**
 * @brief Generate the Queen's moves from a specific square. Player is determined based on the square given.
 * 
 * @param rank The rank the Queen is on
 * @param file The file the Queen is on
 * @param moves The Move vector the pseudo-legal moves are added to
 */
  void queen_moves(int rank, int file, std::vector<Move>& moves) {
    rook_moves(rank, file, moves);
    bishop_moves(rank, file, moves);
  }
  
// for ad map updating
/**
 * @brief Update the Queen's 'attack defense' vision maps. Player is determined based on the square given. The queen uses the Bishop and Rook's 'attack defense' maps
 * 
 * @param rank The rank the Queen is on
 * @param file The file the Queen is on
 */
  void queen_ad(int rank, int file) {
    rook_ad(rank, file);
    bishop_ad(rank, file);
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////

// for move generation
/**
 * @brief Generate the Rook's moves from a specific square. Player is determined based on the square given.
 *
 * @param rank The rank the Rook is on
 * @param file The file the Rook is on
 * @param moves The Move vector the pseudo-legal moves are added to
 */
  void rook_moves(int rank, int file, std::vector<Move>& moves) {
    rook_ad(rank, file);
    int player = (_board[rank][file] < 6) ? WHITE : BLACK;
    if (player == WHITE) {
      // east
      for (int i = file + 1; i <= FILE_H; i++) {
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
      // west
      for (int i = file - 1; i >= FILE_A; i--) {
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
      // south
      for (int i = rank + 1; i <= RANK_1; i++) {
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
      // north
      for (int i = rank - 1; i >= RANK_8; i--) {
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
      // east
      for (int i = file + 1; i <= FILE_H; i++) {
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
      // west
      for (int i = file - 1; i >= FILE_A; i--) {
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
      // south
      for (int i = rank + 1; i <= RANK_1; i++) {
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
      // north
      for (int i = rank - 1; i >= RANK_8; i--) {
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

// for ad map updating
/**
 * @brief Update the Rook's 'attack defense' vision map. Player is determined based on the square given.
 *
 * @param rank The rank the Rook is on
 * @param file The file the Rook is on
 */
  void rook_ad(int rank, int file) {
    int player = (_board[rank][file] < 6) ? WHITE : BLACK;
    if (player == WHITE) {
      for (int i = file + 1; i <= FILE_H; i++) {
        _white_sees_squares[rank][i] += 1;
        if (_board[rank][i] == NA) {
          continue;
        }
        break;
      }

      for (int i = file - 1; i >= FILE_A; i--) {
        _white_sees_squares[rank][i] += 1;
        if (_board[rank][i] == NA) {
          continue;
        }
        break;
      }

      for (int i = rank + 1; i <= RANK_1; i++) {
        _white_sees_squares[i][file] += 1;
        if (_board[i][file] == NA) {
          continue;
        }
        break;
      }

      for (int i = rank - 1; i >= RANK_8; i--) {
        _white_sees_squares[i][file] += 1;
        if (_board[i][file] == NA) {
          continue;
        }
        break;
      }

    } else {
      for (int i = file + 1; i <= FILE_H; i++) {
        _black_sees_squares[rank][i] += 1;
        if (_board[rank][i] == NA) {
          continue;
        }
        break;
      }

      for (int i = file - 1; i >= FILE_A; i--) {
        _black_sees_squares[rank][i] += 1;
        if (_board[rank][i] == NA) {
          continue;
        }
        break;
      }

      for (int i = rank + 1; i <= RANK_1; i++) {
        _black_sees_squares[i][file] += 1;
        if (_board[i][file] == NA) {
          continue;
        }
        break;
      }

      for (int i = rank - 1; i >= RANK_8; i--) {
        _black_sees_squares[i][file] += 1;
        if (_board[i][file] == NA) {
          continue;
        }
        break;
      }
    }
  };

///////////////////////////////////////////////////////////////////////////////////////////////////////

// for move generation
/**
 * @brief Generate the Bishop's moves from a specific square. Player is determined based on the square given.
 *
 * @param rank The rank the Bishop is on
 * @param file The file the Bishop is on
 * @param moves The Move vector the pseudo-legal moves are added to
 */
  void bishop_moves(int rank, int file, std::vector<Move>& moves) {
    bishop_ad(rank, file);
    int player = (_board[rank][file] < 6) ? WHITE : BLACK;
    if (player == WHITE) {

      // southeast
      for (int i = 1 ; i < 8; i++){
        if (rank + i > RANK_1 || file + i > FILE_H) break;

        if (_board[rank + i][file + i] == NA) {
          Move pseudo_move(rank, file, rank + i, file + i);
          moves.push_back(pseudo_move);
          continue;
        } else if (_board[rank + i][file + i] > 6) {
          Move pseudo_move(rank, file, rank + i, file + i);
          moves.push_back(pseudo_move);
        }
        break;
      }


      // northeast
      for (int i = 1 ; i < 8; i++) {
        if (rank - i < RANK_8 || file + i > FILE_H) break;
        
        if (_board[rank - i][file + i] == NA) {
          Move pseudo_move(rank, file, rank - i, file + i);
          moves.push_back(pseudo_move);
          continue;
        } else if (_board[rank - i][file + i] > 6) {
          Move pseudo_move(rank, file, rank - i, file + i);
          moves.push_back(pseudo_move);
        }
        break;
      }

      // northwest
      for (int i = 1 ; i < 8; i++) {
        if (rank - i < RANK_8 || file - i < FILE_A) break;
        
        if (_board[rank - i][file - i] == NA) {
          Move pseudo_move(rank, file, rank - i, file - i);
          moves.push_back(pseudo_move);
          continue;
        } else if (_board[rank - i][file -i] > 6) {
          Move pseudo_move(rank, file, rank - i, file - i);
          moves.push_back(pseudo_move);
        }
        break;
      }

      // southwest
      for (int i = 1 ; i < 8; i++)
      {
        if (rank + i > RANK_1 || file - i < FILE_A) break;
        
        if (_board[rank + i][file - i] == NA) {
          Move pseudo_move(rank, file, rank + i, file - i);
          moves.push_back(pseudo_move);
          continue;
        } else if (_board[rank + i][file - i] > 6) {
          Move pseudo_move(rank, file, rank + i, file - i);
          moves.push_back(pseudo_move);
        }
        break;
      }

    } else {
      // southeast
      for (int i = 1 ; i < 8; i++){
        if (rank + i > RANK_1 || file + i > FILE_H) break;

        if (_board[rank + i][file + i] == NA) {
          Move pseudo_move(rank, file, rank + i, file + i);
          moves.push_back(pseudo_move);
          continue;
        } else if (_board[rank + i][file + i] < 6) {
          Move pseudo_move(rank, file, rank + i, file + i);
          moves.push_back(pseudo_move);
        }
        break;
      }

      // northeast
      for (int i = 1 ; i < 8; i++) {
        if (rank - i < RANK_8 || file + i > FILE_H) break;
        
        if (_board[rank - i][file + i] == NA) {
          Move pseudo_move(rank, file, rank - i, file + i);
          moves.push_back(pseudo_move);
          continue;
        } else if (_board[rank - i][file + i] < 6) {
          Move pseudo_move(rank, file, rank - i, file + i);
          moves.push_back(pseudo_move);
        }
        break;
      }

      // northwest
      for (int i = 1 ; i < 8; i++) {
        if (rank - i < RANK_8 || file - i < FILE_A) break;
        
        if (_board[rank - i][file - i] == NA) {
          Move pseudo_move(rank, file, rank - i, file - i);
          moves.push_back(pseudo_move);
          continue;
        } else if (_board[rank - i][file -i] < 6) {
          Move pseudo_move(rank, file, rank - i, file - i);
          moves.push_back(pseudo_move);
        }
        break;
      }

      // southwest
      for (int i = 1 ; i < 8; i++) {
        if (rank + i > RANK_1 || file - i < FILE_A) break;

        if (_board[rank + i][file - i] == NA) {
          Move pseudo_move(rank, file, rank + i, file - i);
          moves.push_back(pseudo_move);
          continue;
        } else if (_board[rank + i][file - i] < 6) {
          Move pseudo_move(rank, file, rank + i, file - i);
          moves.push_back(pseudo_move);
        }
        break;
      }
    }
  }

// for ad map updating
/**
 * @brief Update the Bishop's 'attack defense' vision map. Player is determined based on the square given.
 *
 * @param rank The rank the Bishop is on
 * @param file The file the Bishop is on
 */
  void bishop_ad(int rank, int file) {

    int player = (_board[rank][file] < 6) ? WHITE : BLACK;
    if (player == WHITE) {

      // southeast
      for (int i = 1 ; i < 8; i++) {
        if (rank + i > RANK_1 || file + i > FILE_H) break;
        
        _white_sees_squares[rank + i][file + i] += 1;
        if (_board[rank + i][file + i] == NA) {
          continue;
        } 
        break;
      }

      // northeast
      for (int i = 1 ; i < 8; i++) {
        if (rank - i < RANK_8 || file + i > FILE_H) break;
        
        _white_sees_squares[rank - i][file + i] += 1;
        if (_board[rank - i][file + i] == NA) {
        	continue;
        } 
        break;
      }

      // northwest
      for (int i = 1 ; i < 8; i++) {
        if (rank - i < RANK_8 || file - i < FILE_A) break;
        
        _white_sees_squares[rank - i][file - i] += 1;
        if (_board[rank - i][file - i] == NA) {
        	continue;
        } 
        break;
      }

      // southwest
      for (int i = 1 ; i < 8; i++) {
        if (rank + i > RANK_1 || file - i < FILE_A) break;

        _white_sees_squares[rank + i][file - i] += 1;
        if (_board[rank + i][file - i] == NA) {
        	continue;
        } 
        break;
      }

    } else {
      // southeast
      for (int i = 1 ; i < 8; i++) {
        if (rank + i > RANK_1 || file + i > FILE_H) break;

        _black_sees_squares[rank + i][file + i] += 1;
        if (_board[rank + i][file + i] == NA) {
        	continue;
        } 
        break;
      }


      // northeast
      for (int i = 1 ; i < 8; i++) {
        if (rank - i < RANK_8 || file + i > FILE_H) break;

        _black_sees_squares[rank - i][file + i] += 1;
        if (_board[rank - i][file + i] == NA) {
        	continue;
        } 
        break;
      }

      // northwest
      for (int i = 1 ; i < 8; i++) {
        if (rank - i < RANK_8 || file - i < FILE_A) break;

        _black_sees_squares[rank - i][file - i] += 1;
        if (_board[rank - i][file - i] == NA) {
        	continue;
        } 
        break;
      }

      // southwest
      for (int i = 1 ; i < 8; i++) {
      	if (rank + i > RANK_1 || file - i < FILE_A) break;
      	
      	_black_sees_squares[rank + i][file - i] += 1;
      	if (_board[rank + i][file - i] == NA) {
      		continue;
      	} 
        break;
      }
    }
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////

// for move generation
/**
 * @brief Generate the King's moves from a specific square. Player is determined based on the square given.
 *
 * @param rank The rank the King is on
 * @param file The file the King is on
 * @param moves The Move vector the pseudo-legal moves are added to
 */
  void king_moves(int rank, int file, std::vector<Move>& moves) {
    king_ad(rank, file);
    int player = (_board[rank][file] < NA) ? WHITE : BLACK;
    if (player == WHITE) {
      // north
      if (rank - 1 >= RANK_8) {
        if (_board[rank - 1][file] == NA) {
          Move pseudo(rank, file, rank - 1, file);
          moves.push_back(pseudo);
        } else if (_board[rank - 1][file] > 6) {
          Move pseudo(rank, file, rank - 1, file);
          moves.push_back(pseudo);
        }
      }
      // east
      if (file + 1 <= FILE_H) {
        if (_board[rank][file + 1] == NA) {
          Move pseudo(rank, file, rank, file + 1);
          moves.push_back(pseudo);
        } else if (_board[rank][file + 1] > 6) {
          Move pseudo(rank, file, rank, file + 1);
          moves.push_back(pseudo);
        }
      }

      // south
      if (rank + 1 <= RANK_1) {
        if (_board[rank + 1][file] == NA) {
          Move pseudo(rank, file, rank + 1, file);
          moves.push_back(pseudo);
        } else if (_board[rank + 1][file] > 6) {
          Move pseudo(rank, file, rank + 1, file);
          moves.push_back(pseudo);
        }
      }

      // west
      if (file - 1 >= FILE_A) {
        if (_board[rank][file - 1] == NA) {
          Move pseudo(rank, file, rank, file - 1);
          moves.push_back(pseudo);
        } else if (_board[rank][file - 1] > 6) {
          Move pseudo(rank, file, rank, file - 1);
          moves.push_back(pseudo);
        }
      }

      // northeast
      if (rank - 1 >= RANK_8 && file + 1 <= FILE_H) {
        if (_board[rank - 1][file + 1] == NA) {
          Move pseudo_move(rank, file, rank - 1, file + 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank - 1][file + 1] > 6) {
          Move pseudo_move(rank, file, rank - 1, file + 1);
          moves.push_back(pseudo_move);
        }
      }

      // southeast
      if (rank + 1 <= RANK_1 && file + 1 <= FILE_H) {
        if (_board[rank + 1][file + 1] == NA) {
          Move pseudo_move(rank, file, rank + 1, file + 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank + 1][file + 1] > 6) {
          Move pseudo_move(rank, file, rank + 1, file + 1);
          moves.push_back(pseudo_move);
        }
      }

      // northwest
      if (rank - 1 >= RANK_8 && file - 1 >= FILE_A) {
        if (_board[rank - 1][file - 1] == NA) {
          Move pseudo_move(rank, file, rank - 1, file - 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank - 1][file - 1] > 6) {
          Move pseudo_move(rank, file, rank - 1, file - 1);
          moves.push_back(pseudo_move);
        }
      }

      // southwest
      if (rank + 1 <= RANK_1 && file - 1 >= FILE_A) {
        if (_board[rank + 1][file - 1] == NA) {
          Move pseudo_move(rank, file, rank + 1, file - 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank + 1][file - 1] > 6) {
          Move pseudo_move(rank, file, rank + 1, file - 1);
          moves.push_back(pseudo_move);
        }
      }

    } else { // black's turn
      // north
      if (rank - 1 >= RANK_8) {
        if (_board[rank - 1][file] == NA) {
          Move pseudo(rank, file, rank - 1, file);
          moves.push_back(pseudo);
        } else if (_board[rank - 1][file] < 6) {
          Move pseudo(rank, file, rank - 1, file);
          moves.push_back(pseudo);
        }
      }
      // east
      if (file + 1 <= FILE_H) {
        if (_board[rank][file + 1] == NA) {
          Move pseudo(rank, file, rank, file + 1);
          moves.push_back(pseudo);
        } else if (_board[rank][file + 1] < 6) {
          Move pseudo(rank, file, rank, file + 1);
          moves.push_back(pseudo);
        }
      }

      // south
      if (rank + 1 <= RANK_1) {
        if (_board[rank + 1][file] == NA) {
          Move pseudo(rank, file, rank + 1, file);
          moves.push_back(pseudo);
        } else if (_board[rank + 1][file] < 6) {
          Move pseudo(rank, file, rank + 1, file);
          moves.push_back(pseudo);
        }
      }

      // west
      if (file - 1 >= FILE_A) {
        if (_board[rank][file - 1] == NA) {
          Move pseudo(rank, file, rank, file - 1);
          moves.push_back(pseudo);
        } else if (_board[rank][file - 1] < 6) {
          Move pseudo(rank, file, rank, file - 1);
          moves.push_back(pseudo);
        }
      }

      // northeast
      if (rank - 1 >= RANK_8 && file + 1 <= FILE_H) {
        if (_board[rank - 1][file + 1] == NA) {
          Move pseudo_move(rank, file, rank - 1, file + 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank - 1][file + 1] < 6) {
          Move pseudo_move(rank, file, rank - 1, file + 1);
          moves.push_back(pseudo_move);
        }
      }

      // southeast
      if (rank + 1 <= RANK_1 && file + 1 <= FILE_H) {
        if (_board[rank + 1][file + 1] == NA) {
          Move pseudo_move(rank, file, rank + 1, file + 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank + 1][file + 1] < 6) {
          Move pseudo_move(rank, file, rank + 1, file + 1);
          moves.push_back(pseudo_move);
        }
      }


      // northwest
      if (rank - 1 >= RANK_8 && file - 1 >= FILE_A) {
        if (_board[rank - 1][file - 1] == NA) {
          Move pseudo_move(rank, file, rank - 1, file - 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank - 1][file - 1] < 6) {
          Move pseudo_move(rank, file, rank - 1, file - 1);
          moves.push_back(pseudo_move);
        }
      }

      // southwest
      if (rank + 1 <= RANK_1 && file - 1 >= FILE_A) {
        if (_board[rank + 1][file - 1] == NA) {
          Move pseudo_move(rank, file, rank + 1, file - 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank + 1][file - 1] < 6) {
          Move pseudo_move(rank, file, rank + 1, file - 1);
          moves.push_back(pseudo_move);
        }
      }
    }
  }

// for ad map updating
/**
 * @brief Update the King's 'attack defense' vision map. Player is determined based on the square given.
 *
 * @param rank The rank the King is on
 * @param file The file the King is on
 */
  void king_ad(int rank, int file) {
    int player = (_board[rank][file] < 6) ? WHITE : BLACK;
    if (player == WHITE) {
      // north
      if (rank - 1 >= RANK_8) {
        _white_sees_squares[rank - 1][file] += 1;
      }

      // east
      if (file + 1 <= FILE_H) {
        _white_sees_squares[rank][file + 1] += 1;
      }

      // south
      if (rank + 1 <= RANK_1) {
        _white_sees_squares[rank + 1][file] += 1;
      }

      // west
      if (file - 1 >= FILE_A) {
        _white_sees_squares[rank][file - 1] += 1;
      }

      // northeast
      if (rank - 1 >= RANK_8 && file + 1 <= FILE_H) {
        _white_sees_squares[rank - 1][file + 1] += 1;
      }

      // southeast
      if (rank + 1 <= RANK_1 && file + 1 <= FILE_H) {
        _white_sees_squares[rank + 1][file + 1] += 1;
      }

      // northwest
      if (rank - 1 >= RANK_8 && file - 1 >= FILE_A) {
        _white_sees_squares[rank - 1][file - 1] += 1;
      }

      // southwest
      if (rank + 1 <= RANK_1 && file - 1 >= FILE_A) {
        _white_sees_squares[rank + 1][file - 1] += 1;
      }

    } else { // black's turn
      // north
      if (rank - 1 >= RANK_8) {
        _black_sees_squares[rank - 1][file] += 1;
      }
      // east
      if (file + 1 <= FILE_H) {
        _black_sees_squares[rank][file + 1] += 1;
      }

      // south
      if (rank + 1 <= RANK_1) {
        _black_sees_squares[rank + 1][file] += 1;
      }

      // west
      if (file - 1 >= FILE_A) {
        _black_sees_squares[rank][file - 1] += 1;
      }

      // northeast
      if (rank - 1 >= RANK_8 && file + 1 <= FILE_H) {
        _black_sees_squares[rank - 1][file + 1] += 1;
      }

      // southeast
      if (rank + 1 <= RANK_1 && file + 1 <= FILE_H) {
        _black_sees_squares[rank + 1][file + 1] += 1;
      }

      // northwest
      if (rank - 1 >= RANK_8 && file - 1 >= FILE_A) {
        _black_sees_squares[rank - 1][file - 1] += 1;
      }

      // southwest
      if (rank + 1 <= RANK_1 && file - 1 >= FILE_A) {
        _black_sees_squares[rank + 1][file - 1] += 1;
      }
    }
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////

// for move generation
/**
 * @brief Generate the Knight's moves from a specific square. Player is determined based on the square given.
 *
 * @param rank The rank the Knight is on
 * @param file The file the Knight is on
 * @param moves The Move vector the pseudo-legal moves are added to
 */
  void knight_moves(int rank, int file, std::vector<Move>& moves) {
    knight_ad(rank, file);
    int player = (_board[rank][file] < NA) ? WHITE : BLACK;
    if (player == WHITE) {
      // nonoea
      if (RANK_1 >= rank - 2 && rank - 2 >= RANK_8 && FILE_H >= file + 1 && file + 1 >= FILE_A) {
        if (_board[rank - 2][file + 1] == NA ) {
          Move pseudo_move(rank, file, rank - 2, file + 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank - 2][file + 1] > 6) {
          Move pseudo_move(rank, file, rank - 2, file + 1);
          moves.push_back(pseudo_move);
        }
      }

      // noeaea
      if (RANK_1 >= rank - 1 && rank - 1 >= RANK_8 && FILE_H >= file + 2 && file + 2 >= FILE_A) {
        if (_board[rank - 1][file + 2] == NA ) {
          Move pseudo_move(rank, file, rank - 1, file + 2);
          moves.push_back(pseudo_move);
        } else if (_board[rank - 1][file + 2] > 6) {
          Move pseudo_move(rank, file, rank - 1, file + 2);
          moves.push_back(pseudo_move);
        }
      }

      // soeaea
      if (RANK_1 >= rank + 1 && rank + 1 >= RANK_8 && FILE_H >= file + 2 && file + 2 >= FILE_A) {
        if (_board[rank + 1][file + 2] == NA ) {
          Move pseudo_move(rank, file, rank + 1, file + 2);
          moves.push_back(pseudo_move);
        } else if (_board[rank + 1][file + 2] > 6) {
          Move pseudo_move(rank, file, rank + 1, file + 2);
          moves.push_back(pseudo_move);
        }
      }

      // sosoea
      if (RANK_1 >= rank + 2 && rank + 2 >= RANK_8 && FILE_H >= file + 1 && file + 1 >= FILE_A) {
        if (_board[rank + 2][file + 1] == NA ) {
          Move pseudo_move(rank, file, rank + 2, file + 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank + 2][file + 1] > 6) {
          Move pseudo_move(rank, file, rank + 2, file + 1);
          moves.push_back(pseudo_move);
        }
      }

      // sosowe
      if (RANK_1 >= rank + 2 && rank + 2 >= RANK_8 && FILE_H >= file - 1 && file - 1 >= FILE_A) {
        if (_board[rank + 2][file - 1] == NA ) {
          Move pseudo_move(rank, file, rank + 2, file - 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank + 2][file - 1] > 6) {
          Move pseudo_move(rank, file, rank + 2, file - 1);
          moves.push_back(pseudo_move);
        }
      }

      // sowewe
      if (RANK_1 >= rank + 1 && rank + 1 >= RANK_8 && FILE_H >= file - 2 && file - 2 >= FILE_A) {
        if (_board[rank + 1][file - 2] == NA ) {
          Move pseudo_move(rank, file, rank + 1, file - 2);
          moves.push_back(pseudo_move);
        } else if (_board[rank + 1][file - 2] > 6) {
          Move pseudo_move(rank, file, rank + 1, file - 2);
          moves.push_back(pseudo_move);
        }
      }

      // nowewe
      if (RANK_1 >= rank - 1 && rank - 1 >= RANK_8 && FILE_H >= file - 2 && file - 2 >= FILE_A) {
        if (_board[rank - 1][file - 2] == NA ) {
          Move pseudo_move(rank, file, rank - 1, file - 2);
          moves.push_back(pseudo_move);
        } else if (_board[rank - 1][file - 2] > 6) {
          Move pseudo_move(rank, file, rank - 1, file - 2);
          moves.push_back(pseudo_move);
        }
      }

      // nonowe
      if (RANK_1 >= rank - 2 && rank - 2 >= RANK_8 && FILE_H >= file - 1 && file - 1 >= FILE_A) {
        if (_board[rank - 2][file - 1] == NA ) {
          Move pseudo_move(rank, file, rank - 2, file - 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank - 2][file - 1] > 6) {
          Move pseudo_move(rank, file, rank - 2, file - 1);
          moves.push_back(pseudo_move);
        }
      }

    } else { //////////////////////////////////////////////////////////////////////////////////////////////

      // nonoea
      if (RANK_1 >= rank - 2 && rank - 2 >= RANK_8 && FILE_H >= file + 1 && file + 1 >= FILE_A) {
        if (_board[rank - 2][file + 1] == NA ) {
          Move pseudo_move(rank, file, rank - 2, file + 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank - 2][file + 1] < 6) {
          Move pseudo_move(rank, file, rank - 2, file + 1);
          moves.push_back(pseudo_move);
        }
      }

      // noeaea
      if (RANK_1 >= rank - 1 && rank - 1 >= RANK_8 && FILE_H >= file + 2 && file + 2 >= FILE_A) {
        if (_board[rank - 1][file + 2] == NA ) {
          Move pseudo_move(rank, file, rank - 1, file + 2);
          moves.push_back(pseudo_move);
        } else if (_board[rank - 1][file + 2] < 6) {
          Move pseudo_move(rank, file, rank - 1, file + 2);
          moves.push_back(pseudo_move);
        }	
      }

      // soeaea
      if (RANK_1 >= rank + 1 && rank + 1 >= RANK_8 && FILE_H >= file + 2 && file + 2 >= FILE_A) {
        if (_board[rank + 1][file + 2] == NA ) {
          Move pseudo_move(rank, file, rank + 1, file + 2);
          moves.push_back(pseudo_move);
        } else if (_board[rank + 1][file + 2] < 6) {
          Move pseudo_move(rank, file, rank + 1, file + 2);
          moves.push_back(pseudo_move);
        }
      }

      // sosoea
      if (RANK_1 >= rank + 2 && rank + 2 >= RANK_8 && FILE_H >= file + 1 && file + 1 >= FILE_A) {
        if (_board[rank + 2][file + 1] == NA ) {
          Move pseudo_move(rank, file, rank + 2, file + 1);
          moves.push_back(pseudo_move);
        } else if ((_board[rank + 2][file + 1] < 6)) {
          Move pseudo_move(rank, file, rank + 2, file + 1);
          moves.push_back(pseudo_move);
        }
      }

      // sosowe
      if (RANK_1 >= rank + 2 && rank + 2 >= RANK_8 && FILE_H >= file - 1 && file - 1 >= FILE_A) {
        if (_board[rank + 2][file - 1] == NA ) {
          Move pseudo_move(rank, file, rank + 2, file - 1);
          moves.push_back(pseudo_move);
        } else if (_board[rank + 2][file - 1] < 6) {
          Move pseudo_move(rank, file, rank + 2, file - 1);
          moves.push_back(pseudo_move);
        }
      }

      // sowewe
      if (RANK_1 >= rank + 1 && rank + 1 >= RANK_8 && FILE_H >= file - 2 && file - 2 >= FILE_A) {
        if (_board[rank + 1][file - 2] == NA ) {
          Move pseudo_move(rank, file, rank + 1, file - 2);
          moves.push_back(pseudo_move);
        } else if (_board[rank + 1][file - 2] < 6) {
          Move pseudo_move(rank, file, rank + 1, file - 2);
          moves.push_back(pseudo_move);
        }
      }

      // nowewe
      if (RANK_1 >= rank - 1 && rank - 1 >= RANK_8 && FILE_H >= file - 2 && file - 2 >= FILE_A) {
        if (_board[rank - 1][file - 2] == NA ) {
          Move pseudo_move(rank, file, rank - 1, file - 2);
          moves.push_back(pseudo_move);
        } else if (_board[rank - 1][file - 2] < 6) {
          Move pseudo_move(rank, file, rank - 1, file - 2);
          moves.push_back(pseudo_move);
        }
      }

      // nonowe
      if (RANK_1 >= rank - 2 && rank - 2 >= RANK_8 && FILE_H >= file - 1 && file - 1 >= FILE_A) {
        if (_board[rank - 2][file - 1] == NA ) {
          Move pseudo_move(rank, file, rank - 2, file - 1);
          moves.push_back(pseudo_move);
          } else if (_board[rank - 2][file - 1] < 6) {
          Move pseudo_move(rank, file, rank - 2, file - 1);
          moves.push_back(pseudo_move);
        }
      }
    }
  };

// for ad map updating
/**
 * @brief Update the Knight's 'attack defense' vision map. Player is determined based on the square given.
 *
 * @param rank The rank the Knight is on
 * @param file The file the Knight is on
 */
  void knight_ad(int rank, int file) {
    int player = (_board[rank][file] < NA) ? WHITE : BLACK;
    if (player == WHITE) {
      if (RANK_1 >= rank - 2 && rank - 2 >= RANK_8 && FILE_H >= file + 1 && file + 1 >= FILE_A) {
        _white_sees_squares[rank - 2][file + 1] += 1;
      }

      // noeaea
      if (RANK_1 >= rank - 1 && rank - 1 >= RANK_8 && FILE_H >= file + 2 && file + 2 >= FILE_A) {
        _white_sees_squares[rank - 1][file + 2] += 1;
      }

      // soeaea
      if (RANK_1 >= rank + 1 && rank + 1 >= RANK_8 && FILE_H >= file + 2 && file + 2 >= FILE_A) {
        _white_sees_squares[rank + 1][file + 2] += 1;
      }

      // sosoea
      if (RANK_1 >= rank + 2 && rank + 2 >= RANK_8 && FILE_H >= file + 1 && file + 1 >= FILE_A) {
        _white_sees_squares[rank + 2][file + 1] += 1;
      }

      // sosowe
      if (RANK_1 >= rank + 2 && rank + 2 >= RANK_8 && FILE_H >= file - 1 && file - 1 >= FILE_A) {
        _white_sees_squares[rank + 2][file - 1] += 1;
      }

      // sowewe
      if (RANK_1 >= rank + 1 && rank + 1 >= RANK_8 && FILE_H >= file - 2 && file - 2 >= FILE_A) {
        _white_sees_squares[rank + 1][file - 2] += 1;
      }

      // nowewe
      if (RANK_1 >= rank - 1 && rank - 1 >= RANK_8 && FILE_H >= file - 2 && file - 2 >= FILE_A) {
        _white_sees_squares[rank - 1][file - 2] += 1;
      }

      // nonowe
      if (RANK_1 >= rank - 2 && rank - 2 >= RANK_8 && FILE_H >= file - 1 && file - 1 >= FILE_A) {
        _white_sees_squares[rank - 2][file - 1] += 1;
      }

    } else { //////////////////////////////////////////////////////////////////////////////////////////////

      // nonoea
      if (RANK_1 >= rank - 2 && rank - 2 >= RANK_8 && FILE_H >= file + 1 && file + 1 >= FILE_A) {
        _black_sees_squares[rank - 2][file + 1] += 1;
      }

      // noeaea
      if (RANK_1 >= rank - 1 && rank - 1 >= RANK_8 && FILE_H >= file + 2 && file + 2 >= FILE_A) {
        _black_sees_squares[rank - 1][file + 2] += 1;
      }

      // soeaea
      if (RANK_1 >= rank + 1 && rank + 1 >= RANK_8 && FILE_H >= file + 2 && file + 2 >= FILE_A) {
        _black_sees_squares[rank + 1][file + 2] += 1;
      }

      // sosoea
      if (RANK_1 >= rank + 2 && rank + 2 >= RANK_8 && FILE_H >= file + 1 && file + 1 >= FILE_A) {
        _black_sees_squares[rank + 2][file + 1] += 1;
      }

      // sosowe
      if (RANK_1 >= rank + 2 && rank + 2 >= RANK_8 && FILE_H >= file - 1 && file - 1 >= FILE_A) {
        _black_sees_squares[rank + 2][file - 1] += 1;
      }

      // sowewe
      if (RANK_1 >= rank + 1 && rank + 1 >= RANK_8 && FILE_H >= file - 2 && file - 2 >= FILE_A) {
        _black_sees_squares[rank + 1][file - 2] += 1;
      }

      // nowewe
      if (RANK_1 >= rank - 1 && rank - 1 >= RANK_8 && FILE_H >= file - 2 && file - 2 >= FILE_A) {
        _black_sees_squares[rank - 1][file - 2] += 1;
      }

      // nonowe
      if (RANK_1 >= rank - 2 && rank - 2 >= RANK_8 && FILE_H >= file - 1 && file - 1 >= FILE_A) {
        _black_sees_squares[rank - 2][file - 1] += 1;
      }
    }
  };

///////////////////////////////////////////////////////////////////////////////////////////////////////

// for move generation
/**
 * @brief Generate Pawn moves from a specific square. Player is determined based on the square given.
 *
 * @param rank The rank the Pawn is on
 * @param file The file the Pawn is on
 * @param moves The Move vector the pseudo-legal moves are added to
 */
  void pawn_moves( int rank, int file, std::vector<Move>& moves) {
    int player = (_board[rank][file] < NA) ? WHITE : BLACK;
    if (player == WHITE) {
      check_up(rank, file, moves);
      check_up_diagonal(rank, file, moves);
      white_pawn_ad(rank, file);
    } else {
      check_down(rank, file, moves);
      check_down_diagonal(rank, file, moves);
      black_pawn_ad(rank, file);
    }
  }

  // for White pawns
/**
 * @brief Generate white pawn movement
 * 
 * @param rank The rank the Pawn is on
 * @param file The file the Pawn is on
 * @param moves The Move vector the pseudo-legal moves are added to
 */
  void check_up(int rank, int file, std::vector<Move>& moves) {
    if (_board[rank - 1][file] == NA) {
      Move pseudo_move(rank, file, rank - 1, file);
      if (rank - 1 == RANK_8) {
        pseudo_move._promotion = true;
        pseudo_move._promotion_piece = wQ;
        moves.push_back(pseudo_move);
        pseudo_move._promotion_piece = wN;
        moves.push_back(pseudo_move);
        pseudo_move._promotion_piece = wR;
        moves.push_back(pseudo_move);
        pseudo_move._promotion_piece = wB;
        moves.push_back(pseudo_move);
      } else {
        moves.push_back(pseudo_move);
      }

      if (_board[rank - 2][file] == NA && rank == RANK_2) {
        Move pseudo_move(rank, file, rank - 2, file);
        moves.push_back(pseudo_move);
      }
    }
  };

  // for White pawns
/**
 * @brief Generate white pawn captures
 * 
 * @param rank The rank the Pawn is on
 * @param file The file the Pawn is on
 * @param moves The Move vector the pseudo-legal moves are added to
 */
  void check_up_diagonal(int rank, int file, std::vector<Move>& moves) {
    // northeast
    if (file + 1 <= FILE_H ) {
      if (_board[rank - 1][file + 1] != NA && _board[rank - 1][file + 1] > 6 ) {
        Move pseudo_move(rank, file, rank - 1, file + 1);
        if (rank - 1 == RANK_8) {
          pseudo_move._promotion = true;
          pseudo_move._promotion_piece = wQ;
          moves.push_back(pseudo_move);
          pseudo_move._promotion_piece = wN;
          moves.push_back(pseudo_move);
          pseudo_move._promotion_piece = wR;
          moves.push_back(pseudo_move);
          pseudo_move._promotion_piece = wB;
          moves.push_back(pseudo_move);
        } else {
          moves.push_back(pseudo_move);
        }
      }

      if (passantable) {
        if (_doublestep_on_file == file + 1 && _board[rank][file + 1] == bP) {
          Move pseudo_move(rank, file, rank - 1, file + 1);
          pseudo_move._en_passant = true;
          moves.push_back(pseudo_move);
        }
      }
    }
    // northwest
    if (file - 1 >= FILE_A) { 
      if (_board[rank - 1][file - 1] != NA && _board[rank - 1][file - 1] > 6) {
        Move pseudo_move(rank, file, rank - 1, file - 1);
        if (rank - 1 == RANK_8) {
          pseudo_move._promotion = true;
          pseudo_move._promotion_piece = wQ;
          moves.push_back(pseudo_move);
          pseudo_move._promotion_piece = wN;
          moves.push_back(pseudo_move);
          pseudo_move._promotion_piece = wR;
          moves.push_back(pseudo_move);
          pseudo_move._promotion_piece = wB;
          moves.push_back(pseudo_move);
        } else {
          moves.push_back(pseudo_move);
        }
      }

      if (passantable) {
        if (_doublestep_on_file == file - 1 && _board[rank][file - 1] == bP) {
          Move pseudo_move(rank, file, rank - 1, file - 1);
          pseudo_move._en_passant = true;
          moves.push_back(pseudo_move);
        }
      }
    }
  };
  
  // for Black pawns.
/**
 * @brief Generate black pawn movement
 * 
 * @param rank The rank the Pawn is on
 * @param file The file the Pawn is on
 * @param moves The Move vector the pseudo-legal moves are added to
 */
  void check_down(int rank, int file, std::vector<Move>& moves) {

    if (_board[rank + 1][file] == NA) {
      Move pseudo_move(rank, file, rank + 1, file);
      if (rank + 1 == RANK_1) {
        pseudo_move._promotion = true;
        pseudo_move._promotion_piece = bQ;
        moves.push_back(pseudo_move);
        pseudo_move._promotion_piece = bN;
        moves.push_back(pseudo_move);
        pseudo_move._promotion_piece = bR;
        moves.push_back(pseudo_move);
        pseudo_move._promotion_piece = bB;
        moves.push_back(pseudo_move);
      } else {
        moves.push_back(pseudo_move);
      }

      if (_board[rank + 2][file] == NA && rank == RANK_7) {
        Move pseudo_move(rank, file, rank + 2, file);
        moves.push_back(pseudo_move);
      }
    }
  };

  // for Black pawns
/**
 * @brief Generate black pawn captures
 * 
 * @param rank The rank the Pawn is on
 * @param file The file the Pawn is on
 * @param moves The Move vector the pseudo-legal moves are added to
 */
  void check_down_diagonal(int rank, int file, std::vector<Move>& moves) {
    if (file + 1 <= FILE_H) { 
      // southeast
      if (_board[rank + 1][file + 1] != NA && _board[rank + 1][file + 1] < 6) {
        Move pseudo_move(rank, file, rank + 1, file + 1);
        if (rank + 1 == RANK_1) {
          pseudo_move._promotion = true;
          pseudo_move._promotion_piece = bQ;
          moves.push_back(pseudo_move);
          pseudo_move._promotion_piece = bN;
          moves.push_back(pseudo_move);
          pseudo_move._promotion_piece = bR;
          moves.push_back(pseudo_move);
          pseudo_move._promotion_piece = bB;
          moves.push_back(pseudo_move);
        } else {
          moves.push_back(pseudo_move);
        }
      }
      if (passantable) {
        if (_doublestep_on_file == file + 1 && _board[rank][file + 1] == wP) {
          Move pseudo_move(rank, file, rank + 1, file + 1);
          pseudo_move._en_passant = true;
          moves.push_back(pseudo_move);
        }
      }
    }

    if (file - 1 >= FILE_A) { 
      // southwest
      if (_board[rank + 1][file - 1] != NA && _board[rank + 1][file - 1] < 6) {
        Move pseudo_move(rank, file, rank + 1, file - 1);
        if (rank + 1 == RANK_1) {
          pseudo_move._promotion = true;
          pseudo_move._promotion_piece = bQ;
          moves.push_back(pseudo_move);
          pseudo_move._promotion_piece = bN;
          moves.push_back(pseudo_move);
          pseudo_move._promotion_piece = bR;
          moves.push_back(pseudo_move);
          pseudo_move._promotion_piece = bB;
          moves.push_back(pseudo_move);
        } else {
          moves.push_back(pseudo_move);
        }
      }
      if (passantable) {
        if (_doublestep_on_file == file - 1 && _board[rank][file - 1] == wP) {
          Move pseudo_move(rank, file, rank + 1, file - 1);
          pseudo_move._en_passant = true;
          moves.push_back(pseudo_move);
        }
      }
    }
  };

// for ad map updating
/**
 * @brief Update the Pawn's 'attack defense' vision map. White.
 *
 * @param rank The rank the Pawn is on
 * @param file The file the Pawn is on
 */
  void white_pawn_ad(int rank, int file) {
    if (rank - 1 < RANK_8 ) return; // shouldnt ever happen since pawns MUST promote

    // northeast
    if (file + 1 <= FILE_H ) {
      _white_sees_squares[rank - 1][file + 1] += 1;
    }
    // northwest
    if (file - 1 >= FILE_A) {
      _white_sees_squares[rank - 1][file - 1] += 1;
    }
  };

  /**
 * @brief Update the Pawn's 'attack defense' vision map. Black.
 *
 * @param rank The rank the Pawn is on
 * @param file The file the Pawn is on
 */
  void black_pawn_ad(int rank, int file) {
    if (rank + 1 > RANK_1) return;

    // southeast
    if (file + 1 <= FILE_H) { 
      _black_sees_squares[rank + 1][file + 1] += 1;
    }

    // southwest
    if (file - 1 >= FILE_A) { 
      _black_sees_squares[rank + 1][file - 1] += 1;
    }
  };

};