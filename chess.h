#pragma once

// Pelaajat.
enum { WHITE, BLACK };

// Vakioarvot eri nappululoille (NA = tyhjä ruutu).
enum { wR, wN, wB, wQ, wK, wP, bR, bN, bB, bQ, bK, bP, NA};
//     0   1   2   3   4   5   6   7   8   9   10  11  12

// Palauttaa annetun nappulan värin (VALKEA, MUSTA).
int piece_color(int piece);

// Palauttaa pelaajan vastustajan.
int opponent(int player);

struct Piece {
  // maybe?
  int _identity;
  int _color;
  int _rank;
  int _file;

};