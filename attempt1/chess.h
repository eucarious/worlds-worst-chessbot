#pragma once

// Pelaajat.
enum { WHITE, BLACK };

// Vakioarvot eri nappululoille (NA = tyhjä ruutu).
enum { wR, wN, wB, wQ, wK, wP, bR, bN, bB, bQ, bK, bP, NA};
//     0   1   2   3   4   5   6   7   8   9   10  11  12


enum _RANK { RANK_8, RANK_7, RANK_6, RANK_5, RANK_4, RANK_3, RANK_2, RANK_1 };
enum _FILE { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H };

// Palauttaa annetun nappulan värin (VALKEA, MUSTA).
int piece_color(int piece);


// Palauttaa pelaajan vastustajan.
int opponent(int player);

//* store stuff in a better way rather than searching Every. Single. Time. (memory usage vs performance time)
class Piece {
protected:

    int _rank;
    int _file;
    int _player;
    int _piece;

    friend class Board;
public:

    Piece () {};

    virtual void print() {}

};