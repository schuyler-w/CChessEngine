//
// Created by Schuyler Wang on 7/31/23.
//

#include "stdio.h"
#include "defs.h"

void ResetBoard(S_BOARD *pos) {
    for (int i = 0; i < BRD_SQ_NUM; ++i)
        pos->pieces[i] = OFFBOARD;

    for (int i = 0; i < 64; ++i)
        pos->pieces[SQ120(i)] = EMPTY;

    for (int i = 0; i < 2; ++i) {
        pos->bigPce[i] = 0;
        pos->majPce[i] = 0;
        pos->minPce[i] = 0;
    }

    for (int i = 0; i < 2; ++i)
        pos->pawns[i] = 0ULL;

    for(int i = 0; i < 13; ++i) {
        pos->pceNum[i] = 0;
    }

    pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQUARE;

    pos->side = BOTH;
    pos->enPas = NO_SQUARE;

    pos->FiftyMove = 0;
    pos->play = 0;
    pos->hisPlay = 0;
    pos->castlePerm = 0;

    pos->posKey = 0ULL;

}