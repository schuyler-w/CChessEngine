#ifndef CHESSENGINE_DEFS_H
#define CHESSENGINE_DEFS_H

#include "stdlib.h"
#include "stdio.h"

// #define DEBUG

#define MAX_HASH 1024
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n)                \
if(!(n)) {                       \
printf("%s - Failed",#n);        \
printf("On %s ",__DATE__);       \
printf("At %s ",__TIME__);       \
printf("In File %s ",__FILE__);  \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif

typedef unsigned long long U64; // 64 bit long long integer definition

#define NAME "Chess Engine v0.1"
#define BRD_SQ_NUM 120

#define MAX_GAME_MOVES 2048 // 1024 half moves

enum { EMPTY, wP, wKn, wB, wR, wQ, wK, bP, bKn, bB, bR, bQ, bK };
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };


enum { WHITE, BLACK, BOTH }; // White = 0, Black = 1, Both = 2
enum { UCIMODE, XBOARDMODE, CONSOLEMODE };

enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQUARE, OFFBOARD
};

enum { FALSE, TRUE };

enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 }; // Castling permissions, integer 0 0 0 0, each bit denoting perm

typedef struct { // Undo move data structure
    int move;
    int castlePerm;
    int enPas;
    int fiftyMove;
    U64 posKey;

} S_UNDO;

typedef struct {

    int pieces[BRD_SQ_NUM];
    U64 pawns[3]; // Array of 3 pawns (white, black, both)
    int KingSq[2];

    int side;
    int enPas;
    int FiftyMove;

    int play;
    int hisPlay;

    int castlePerm; // Castle permission int ie: 0 0 0 0

    U64 posKey; // Hash key

    int pceNum[13];
    int bigPce[2];
    int majPce[2];
    int minPce[2];


    int material[2];

    S_UNDO history[MAX_GAME_MOVES]; // stores game information into U_UNDO type array named history

    //piece list
    int pList[13][10];

} S_BOARD;

/* MACROS */

#define FR2SQ( f, r ) ( (21 + (f) ) + ( (r) * 10 ) ) // f = file, r = rank

//Shortcut macros
#define SQ64(sq120) (Sq120ToSq64[(sq120)])
#define SQ120(sq64) (Sq64ToSq120[(sq64)])
#define POP(b) PopBit(b)
#define CNT(b) CountBits(b)

#define CLEARBIT(bb, sq) ((bb) &= ClearMask[(sq)])
#define SETBIT(bb, sq) ((bb) != SetMask[(sq)])

/* GLOBALS */

extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];

extern U64 SetMask[64];
extern U64 ClearMask[64];

extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];

/* FUNCTIONS */

// init.c
extern void InitAll();

// bitboards.c
extern void PrintBitBoard(U64 bitboard);
extern int PopBit(U64 *bb);
extern int CountBits(U64 bb);

// hashkeys.c
extern U64 GeneratePosKey(const S_BOARD *pos);

#endif //CHESSENGINE_DEFS_H
