//
// Created by Schuyler Wang on 7/31/23.
//

#include "defs.h"

void InitSq120To64() {

    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;
    for(index = 0; index < BRD_SQ_NUM; ++index) {
        Sq120ToSq64[index] = 65; // setting values of board to invalid value
    }

    for(index = 0; index < 64; ++index) {
        Sq64ToSq120[index] = 120; // impossible value as above
    }

    for(rank = RANK_1; rank <= RANK_8; ++rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq = FR2SQ(file,rank);
            ASSERT(SqOnBoard(sq));
            Sq64ToSq120[sq64] = sq;
            Sq120ToSq64[sq] = sq64;
            sq64++;
        }
    }
}

void AllInit() {

}