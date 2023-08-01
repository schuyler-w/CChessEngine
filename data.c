//
// Created by Schuyler Wang on 7/31/23.
//
#include "defs.h"

char PieceChar[] = ".PNBRQKpnbrqk"; // . = empty
char SideChar[] = "wb-"; // white, black, both
char RankChar[] = "12345678";
char FileChar[] = "abcdefgh";

int PieceBig[13] = { FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE };
int PieceMajor[13] = { FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE };
int PieceMin[13] = { FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE };
int PieceValue[13]= { 0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000  };
int PieceColor[13] = { BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
                     BLACK, BLACK, BLACK, BLACK, BLACK, BLACK };
