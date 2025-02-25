#pragma once

enum PLAYER { WHITE, BLACK };

enum PIECES { wR, wN, wB, wQ, wK, wP, NA, bR, bN, bB, bQ, bK, bP};
//            0   1   2   3   4   5   6   7   8   9   10  11  12

enum _RANK { RANK_8, RANK_7, RANK_6, RANK_5, RANK_4, RANK_3, RANK_2, RANK_1 };
enum _FILE { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H };

int opponent(int player) {
  if (player == WHITE) return BLACK;
  return WHITE;
};

