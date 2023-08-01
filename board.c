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
        ASSERT(PceValidEmptyOffbrd(piece))
        if(piece!=OFFBOARD && piece!= EMPTY) {
            color = PieceColor[piece];
            ASSERT(SideValid(color))

            if( PieceBig[piece]   == TRUE) pos->bigPce[color]++;
            if( PieceMinor[piece] == TRUE) pos->minPce[color]++;
            if( PieceMajor[piece] == TRUE) pos->majPce[color]++;

            pos->material[color] += PieceValue[piece];

            ASSERT(pos->pceNum[piece] < 10 && pos->pceNum[piece] >= 0)

            pos->pList[piece][pos->pceNum[piece]] = sq;
            pos->pceNum[piece]++;

            if (piece==wK) pos->KingSq[WHITE] = sq;
            if (piece==bK) pos->KingSq[BLACK] = sq;

            if (piece==wP) {
                SETBIT(pos->pawns[WHITE], SQ64(sq));
                SETBIT(pos->pawns[BOTH], SQ64(sq));
            } else if (piece==bP) {
                SETBIT(pos->pawns[BLACK], SQ64(sq));
                SETBIT(pos->pawns[BOTH], SQ64(sq));
            }
        }
    }
}

int ParseFen(char *fen, S_BOARD *pos) {

    ASSERT(fen!=NULL)
    ASSERT(pos!=NULL)

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

    ASSERT(*fen == 'w' || *fen == 'b')

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

    ASSERT(pos->castlePerm>=0 && pos->castlePerm <= 15)

    if (*fen != '-') {
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        ASSERT(file>=FILE_A && file <= FILE_H)
        ASSERT(rank>=RANK_1 && rank <= RANK_8)

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