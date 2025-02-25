// sotilas 1
// ratsu 3
// lähetti 3
// torni 5
// daami 9

// in centipawns 
#define PAWN_VAL    100
#define KNIGHT_VAL  300
#define BISHOP_VAL  320
#define ROOK_VAL    500
#define QUEEN_VAL   900

// following piece square tables are pretty much taken directly from the Chess Programming Wiki
// from either the 'Simplified evaluation' page or that page mixed with PeSTO / TSCP pcsqs

//* note to self: since these table values are mixed and matched, there might be some issues
//                with 'square in-/deflation'.

int wP_pcsq[8][8]  = {
    {  0,  0,  0,  0,  0,  0,  0,  0 },
    { 50, 50, 50, 50, 50, 50, 50, 50 },
    { 10, 10, 20, 30, 30, 20, 10, 10 },
    {  5,  5, 10, 25, 25, 10,  5,  5 },
    {  0,  0,  0, 25, 25,  0,  0,  0 },
    {  5, -5,-10,  0,  0,-10, -5,  5 },
    {  5, 10, 10,-20,-20, 10, 10,  5 },
    {  0,  0,  0,  0,  0,  0,  0,  0 }
};

int bP_pcsq[8][8]  = {
    {  0,  0,  0,  0,  0,  0,  0,  0 },
    {  5, 10, 10,-20,-20, 10, 10,  5 },
    {  5, -5,-10,  0,  0,-10, -5,  5 },
    {  0,  0,  0, 25, 25,  0,  0,  0 },
    {  5,  5, 10, 25, 25, 10,  5,  5 },
    { 10, 10, 20, 30, 30, 20, 10, 10 },
    { 50, 50, 50, 50, 50, 50, 50, 50 },
    {  0,  0,  0,  0,  0,  0,  0,  0 }
};

// applies to both knights
int N_pcsq[8][8]  = {
    {-50,-40,-30,-30,-30,-30,-40,-50 },
    {-40,-20,  0,  0,  0,  0,-20,-40 },
    {-30,  0,  5, 15, 15,  5,  0,-30 },
    {-30,  0, 15, 20, 20, 15,  0,-30 },
    {-30,  0, 15, 20, 20, 15,  0,-30 },
    {-30,  0,  5, 15, 15,  5,  0,-30 },
    {-40,-20,  0,  0,  0,  0,-20,-40 },
    {-50,-40,-30,-30,-30,-30,-40,-50 }
};

// only difference in bishop piecesquares are the starting position negatives 
//    -> to move out of the way so that the king can castle
int wB_pcsq[8][8]  = {
    {-20,-10,-10,-10,-10,-10,-10,-20 },
    {-10,  0,  0,  0,  0,  0,  0,-10 },
    {-10,  0,  5,  5,  5,  5,  0,-10 },
    {-10,  0,  5, 10, 10,  5,  0,-10 },
    {-10,  0,  5, 10, 10,  5,  0,-10 },
    {-10,  0,  5,  5,  5,  5,  0,-10 },
    {-10,  0,  0,  0,  0,  0,  0,-10 },
    {-20,-10,-20,-10,-10,-20,-10,-20 }
};

int bB_pcsq[8][8]  = {
    {-20,-10,-20,-10,-10,-20,-10,-20 },
    {-10,  0,  0,  0,  0,  0,  0,-10 },
    {-10,  0,  5,  5,  5,  5,  0,-10 },
    {-10,  0,  5, 10, 10,  5,  0,-10 },
    {-10,  0,  5, 10, 10,  5,  0,-10 },
    {-10,  0,  5,  5,  5,  5,  0,-10 },
    {-10,  0,  0,  0,  0,  0,  0,-10 },
    {-20,-10,-10,-10,-10,-10,-10,-20 }
};

// rook n queen can figure it out themselves

// while both queens are still in play
// or piece val total is above 1400
int wK_pcsq[8][8]  = {
    {-40,-40,-40,-40,-40,-40,-40,-40 },
    {-40,-40,-40,-40,-40,-40,-40,-40 },
    {-40,-40,-40,-40,-40,-40,-40,-40 },
    {-40,-40,-40,-40,-40,-40,-40,-40 },
    {-40,-40,-40,-40,-40,-40,-40,-40 },
    {-40,-40,-40,-40,-40,-40,-40,-40 },
    {-20,-20,-20,-20,-20,-20,-20,-20 },
    {  0, 20, 40,-20,  0,-20, 40, 20 }
}; // inner 40s are to encourage castling

int bK_pcsq[8][8]  = {
    {  0, 20, 40,-20,  0,-20, 40, 20 },
    {-20,-20,-20,-20,-20,-20,-20,-20 },
    {-40,-40,-40,-40,-40,-40,-40,-40 },
    {-40,-40,-40,-40,-40,-40,-40,-40 },
    {-40,-40,-40,-40,-40,-40,-40,-40 },
    {-40,-40,-40,-40,-40,-40,-40,-40 },
    {-40,-40,-40,-40,-40,-40,-40,-40 },
    {-40,-40,-40,-40,-40,-40,-40,-40 }
};

// when both queens are no longer in play 
// or piece val is below 1400-ish. i'll figure out the specifics sometime
// same for both
int end_K_pscq[8][8]  = {
    {-10, 10, 20, 30, 30, 20, 10,-10 },
    { 10, 20, 30, 40, 40, 30, 20, 10 },
    { 20, 30, 40, 50, 50, 40, 30, 20 },
    { 30, 40, 50, 60, 60, 50, 40, 30 },
    { 30, 40, 50, 60, 60, 50, 40, 30 },
    { 20, 30, 40, 50, 50, 40, 30, 20 },
    { 10, 20, 30, 40, 40, 30, 20, 10 },
    {-10, 10, 20, 30, 30, 20, 10,-10 }
};// encourages the kings to be in the middle and discourages from going into corners