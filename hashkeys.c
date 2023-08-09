//
// Generates unique 64 bit hash key for posKey variable
//
#include "defs.h"
#include "stdio.h"

U64 GeneratePosKey(const S_BOARD *pos) {

    int sq = 0;
    U64 finalKey = 0;
    int piece = EMPTY;

    // pieces
    for(sq = 0; sq < BRD_SQ_NUM; ++sq) {
        piece = pos->pieces[sq];
        if(piece!=NO_SQUARE && piece!=EMPTY && piece != OFFBOARD) {
            assert(piece>=wP && piece<=bK);
            finalKey ^= PieceKeys[piece][sq];
        }
    }

    if(pos->side == WHITE) {
        finalKey ^= SideKey;
    }

    if(pos->enPas != NO_SQUARE) {
        assert(pos->enPas>=0 && pos->enPas<BRD_SQ_NUM);
        //assert(SqOnBoard(pos->enPas));
        assert(RanksBrd[pos->enPas] == RANK_3 || RanksBrd[pos->enPas] == RANK_6);
        finalKey ^= PieceKeys[EMPTY][pos->enPas];
    }

    assert(pos->castlePerm>=0 && pos->castlePerm<=15);

    finalKey ^= CastleKeys[pos->castlePerm];

    return finalKey;
}