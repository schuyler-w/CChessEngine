//
// Created by Schuyler Wang on 7/31/23.
//

#include "defs.h"
#include "stdlib.h"

#define RAND_64 	((U64)rand() | \
					(U64)rand() << 15 | \
					(U64)rand() << 30 | \
					(U64)rand() << 45 | \
					((U64)rand() & 0xf) << 60 )

int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

U64 SetMask[64];
U64 ClearMask[64];

U64 PieceKeys[13][120];
U64 SideKey;
U64 CastleKeys[16];

int FilesBrd[BRD_SQ_NUM];
int RanksBrd[BRD_SQ_NUM];

void InitHashKeys() {
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 120; ++j)
            PieceKeys[i][j] = RAND_64;
    }
    SideKey = RAND_64;
    for (int i = 0; i < 16; ++i)
        CastleKeys[i] = RAND_64;
}

void InitBitMasks() {
    for (int i = 0; i < 64; i++) {
        SetMask[i] = 0ULL;
        ClearMask[i] = 0ULL;
    }

    for (int i = 0; i < 64; i++) {
        SetMask[i] |= (1ULL << i);
        ClearMask[i] = ~SetMask[i];
    }
}

void InitSq120To64() {

    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;
    for(index = 0; index < BRD_SQ_NUM; ++index) {
        Sq120ToSq64[index] = 99; // setting values of board to invalid value
    }

    for(index = 0; index < 64; ++index) {
        Sq64ToSq120[index] = 120; // impossible value as above
    }

    for(rank = RANK_1; rank <= RANK_8; ++rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq = FR2SQ(file,rank);
            //ASSERT(SqOnBoard(sq));
            Sq64ToSq120[sq64] = sq;
            Sq120ToSq64[sq] = sq64;
            sq64++;
        }
    }
}

void InitFilesRanksBrd() {

    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;

    for(int i = 0; i < BRD_SQ_NUM; ++i) {
        FilesBrd[i] = OFFBOARD;
        RanksBrd[i] = OFFBOARD;
    }

    for(rank = RANK_1; rank <= RANK_8; ++rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq = FR2SQ(file, rank);
            FilesBrd[sq] = file;
            RanksBrd[sq] = rank;
        }
    }

/*
    printf("FilesBrd\n");
    for (int i =0; i < BRD_SQ_NUM; ++i) {
        if (i%10==0 && i != 0)
            printf("\n");
        printf("%4d", FilesBrd[i]);
    }
    printf("\n");
    printf("RanksBrd\n");
    for (int i =0; i < BRD_SQ_NUM; ++i) {
        if (i%10==0 && i != 0)
            printf("\n");
        printf("%4d", RanksBrd[i]);
    }
    printf("\n");
*/

}


void InitAll() {
    InitSq120To64();
    InitBitMasks();
    InitHashKeys();
    InitFilesRanksBrd();
}