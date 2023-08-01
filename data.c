//
// Created by Schuyler Wang on 7/31/23.
//
#include "defs.h"

char PieceChar[] = ".PNBRQKpnbrqk"; // . = empty
char SideChar[] = "wb-"; // white, black, both
char RankChar[] = "12345678";
char FileChar[] = "abcdefgh";

// Empty = False, White Pawn = False, Black Pawn = False
int PieceBig[13] = { FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE };
int PieceMajor[13] = { FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE };
int PieceMinor[13] = { FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE };

// King = 50000 (because win)
int PieceValue[13]= { 0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000  };
int PieceColor[13] = { BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
                     BLACK, BLACK, BLACK, BLACK, BLACK, BLACK };

int PiecePawn[13] = { FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE };