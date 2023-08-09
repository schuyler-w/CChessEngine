//
// Created by Schuyler Wang on 7/31/23.
//

#include "stdio.h"
#include "defs.h"

void UpdateListsMaterial(S_BOARD *pos) {

    int piece;
    int sq;
    int color;

    for(int i = 0; i < BRD_SQ_NUM; ++i) {
        sq = i;
        piece = pos->pieces[i];
        //assert(PceValidEmptyOffbrd(piece));
        if(piece!=OFFBOARD && piece!= EMPTY) {
            color = PieceColor[piece];
            //assert(SideValid(color));

            if( PieceBig[piece]   == TRUE) pos->bigPce[color]++;
            if( PieceMinor[piece] == TRUE) pos->minPce[color]++;
            if( PieceMajor[piece] == TRUE) pos->majPce[color]++;

            pos->material[color] += PieceValue[piece];

            assert(pos->pceNum[piece] < 10 && pos->pceNum[piece] >= 0);

            pos->pList[piece][pos->pceNum[piece]] = sq;
            pos->pceNum[piece]++;

            if (piece==wK) pos->KingSq[WHITE] = sq;
            if (piece==bK) pos->KingSq[BLACK] = sq;

            if (piece==wP) { // if piece is white pawn
                SETBIT(pos->pawns[WHITE], SQ64(sq)); // set bit on bitboard for white pawn position
                SETBIT(pos->pawns[BOTH], SQ64(sq)); // set bit on bitboard for both pawn pos
            } else if (piece==bP) { // else black
                SETBIT(pos->pawns[BLACK], SQ64(sq));
                SETBIT(pos->pawns[BOTH], SQ64(sq));
            }
        }
    }
}

int CheckBoard(const S_BOARD *pos) { // checks if board in pos and then compare if they're == temp variable positions
    // set up temp variables
    int t_pceNum[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int t_bigPce[2] = {0, 0};
    int t_majPce[2] = {0, 0};
    int t_minPce[2] = {0, 0};
    int t_material[2] = {0, 0};

    int sq64,t_piece,t_pce_num,sq120,color,pcount;

    U64 t_pawns[3] = {0ULL, 0ULL, 0ULL};

    t_pawns[WHITE] = pos->pawns[WHITE];
    t_pawns[BLACK] = pos->pawns[BLACK];
    t_pawns[BOTH] = pos->pawns[BOTH];

    // check piece lists
    for(t_piece = wP; t_piece <= bK; ++t_piece) { // loops through unique pieces
        for(t_pce_num = 0; t_pce_num < pos->pceNum[t_piece]; ++t_pce_num) { // loops through members of a piece
            sq120 = pos->pList[t_piece][t_pce_num];
            assert(pos->pieces[sq120]==t_piece);
        }
    }

    // check piece count and other counters
    for(int i = 0; i < 64; ++i) {
        sq120 = SQ120(i);
        t_piece = pos->pieces[sq120];
        t_pceNum[t_piece]++;
        color = PieceColor[t_piece];
        if(PieceBig[t_piece] == TRUE) t_bigPce[color]++;
        if(PieceMinor[t_piece] == TRUE) t_minPce[color]++;
        if(PieceMajor[t_piece] == TRUE) t_majPce[color]++;

        t_material[color] += PieceValue[t_piece];
    }

    for(t_piece = wP; t_piece <= bK; ++t_piece) {
        assert(t_pceNum[t_piece]==pos->pceNum[t_piece]);
    }

    // check bitboards count
    pcount = CNT(t_pawns[WHITE]);
    assert(pcount == pos->pceNum[wP]);
    pcount = CNT(t_pawns[BLACK]);
    assert(pcount == pos->pceNum[bP]);
    pcount = CNT(t_pawns[BOTH]);
    assert(pcount == (pos->pceNum[bP] + pos->pceNum[wP]));

    // check bitboards squares
    while(t_pawns[WHITE]) {
        sq64 = POP(&t_pawns[WHITE]);
        assert(pos->pieces[SQ120(sq64)] == wP);
    }

    while(t_pawns[BLACK]) {
        sq64 = POP(&t_pawns[BLACK]);
        assert(pos->pieces[SQ120(sq64)] == bP);
    }

    while(t_pawns[BOTH]) {
        sq64 = POP(&t_pawns[BOTH]);
        assert( (pos->pieces[SQ120(sq64)] == bP) || (pos->pieces[SQ120(sq64)] == wP) );
    }

    assert(t_material[WHITE]==pos->material[WHITE] && t_material[BLACK]==pos->material[BLACK]);
    assert(t_minPce[WHITE]==pos->minPce[WHITE] && t_minPce[BLACK]==pos->minPce[BLACK]);
    assert(t_majPce[WHITE]==pos->majPce[WHITE] && t_majPce[BLACK]==pos->majPce[BLACK]);
    assert(t_bigPce[WHITE]==pos->bigPce[WHITE] && t_bigPce[BLACK]==pos->bigPce[BLACK]);

    assert(pos->side==WHITE || pos->side==BLACK);
    assert(GeneratePosKey(pos)==pos->posKey);

    assert(pos->enPas==NO_SQUARE || ( RanksBrd[pos->enPas]==RANK_6 && pos->side == WHITE)
           || ( RanksBrd[pos->enPas]==RANK_3 && pos->side == BLACK));

    assert(pos->pieces[pos->KingSq[WHITE]] == wK);
    assert(pos->pieces[pos->KingSq[BLACK]] == bK);

    assert(pos->castlePerm >= 0 && pos->castlePerm <= 15);

    return TRUE;
}

int ParseFen(char *fen, S_BOARD *pos) {

    assert(fen!=NULL);
    assert(pos!=NULL);

    int  rank = RANK_8;
    int  file = FILE_A;
    int  piece = 0;
    int  count = 0;
    int  sq64 = 0;
    int  sq120 = 0;

    ResetBoard(pos);

    while ((rank >= RANK_1) && *fen) {
        count = 1;
        switch (*fen) {
            case 'p': piece = bP; break;
            case 'r': piece = bR; break;
            case 'n': piece = bN; break;
            case 'b': piece = bB; break;
            case 'k': piece = bK; break;
            case 'q': piece = bQ; break;
            case 'P': piece = wP; break;
            case 'R': piece = wR; break;
            case 'N': piece = wN; break;
            case 'B': piece = wB; break;
            case 'K': piece = wK; break;
            case 'Q': piece = wQ; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                piece = EMPTY;
                count = *fen - '0';
                break;

            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                fen++;
                continue;

            default:
                printf("FEN error \n");
                return -1;
        }

        for (int i = 0; i < count; i++) {
            sq64 = rank * 8 + file;
            sq120 = SQ120(sq64);
            if (piece != EMPTY) {
                pos->pieces[sq120] = piece;
            }
            file++;
        }
        fen++;
    }

    assert(*fen == 'w' || *fen == 'b');

    pos->side = (*fen == 'w') ? WHITE : BLACK;
    fen += 2;

    for (int i = 0; i < 4; i++) {
        if (*fen == ' ') {
            break;
        }
        switch(*fen) {
            case 'K': pos->castlePerm |= WKCA; break;
            case 'Q': pos->castlePerm |= WQCA; break;
            case 'k': pos->castlePerm |= BKCA; break;
            case 'q': pos->castlePerm |= BQCA; break;
            default:	     break;
        }
        fen++;
    }
    fen++;

    assert(pos->castlePerm>=0 && pos->castlePerm <= 15);

    if (*fen != '-') {
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        assert(file>=FILE_A && file <= FILE_H);
        assert(rank>=RANK_1 && rank <= RANK_8);

        pos->enPas = FR2SQ(file,rank);
    }

    pos->posKey = GeneratePosKey(pos);

    UpdateListsMaterial(pos);

    return 0;
}

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

void PrintBoard(const S_BOARD *pos) {

    int sq;
    int file;
    int rank;
    int piece;

    printf("\nGame Board:\n\n");

    for(rank = RANK_8; rank >= RANK_1; rank--) {
        printf("%d  ",rank+1);
        for(file = FILE_A; file <= FILE_H; file++) {
            sq = FR2SQ(file,rank);
            piece = pos->pieces[sq];
            printf("%3c",PieceChar[piece]);
        }
        printf("\n");
    }

    printf("\n   ");
    for(file = FILE_A; file <= FILE_H; file++) {
        printf("%3c",'a'+file);
    }
    printf("\n");
    printf("side:%c\n",SideChar[pos->side]);
    printf("enPas:%d\n",pos->enPas);
    printf("castle:%c%c%c%c\n",
           pos->castlePerm & WKCA ? 'K' : '-',
           pos->castlePerm & WQCA ? 'Q' : '-',
           pos->castlePerm & BKCA ? 'k' : '-',
           pos->castlePerm & BQCA ? 'q' : '-'
    );
    printf("PosKey:%llX\n",pos->posKey);
}