// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdio.h>
#include "types.h"
#include "./attacksDB/slidingDB.h"
#include "./attacksDB/non_slidingDB.h"
#include <stdlib.h>

#define RANK_8 0xff00000000000000ULL

int six_bits = 0x3F;


void print_bb(Bitboard bb, char *label) {
    printf("-- %s --\n", label);
    for (int rank = 7; rank >= 0; rank--) {
        printf("%d  ", rank + 1);
        for (int file = 0; file < 8; file++) {
            int sq = rank * 8 + file;
            if ((bb >> sq) & 1ULL)
                printf("1 ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("   a b c d e f g h\n\n");
}

int main(void) {
    // הקצאת זיכרון ללוח ואיפוס (חשוב כדי למנוע Garbage values)
    Board *board = calloc(1, sizeof(Board));
    
    // נגדיר OCC לדוגמה
    board->Occ[WHITE] = (1ULL << 11); // d2
    board->Occ[BLACK] = (1ULL << 43); // d6
    
    Bitboard OCC_ALL = (board->Occ[WHITE] | board->Occ[BLACK]);
    
    // שימוש במשתנה six_bits כדי לחלץ משבצת (למשל d4)
    int move_example = 27; // d4
    Square sq = move_example & six_bits;

    // קריאה לפונקציות מה-DB
    Bitboard rook_attacks = get_straight_attacks(sq, OCC_ALL);
    Bitboard bishop_attacks = get_diagonal_attacks(sq, OCC_ALL);

    printf("DEBUGGING CHESS CORE - LEVI\n");
    printf("==========================\n\n");
    
    print_bb(OCC_ALL, "OCCUPANCY (d2, d6)");
    print_bb(rook_attacks, "ROOK ATTACKS from d4");
    print_bb(bishop_attacks, "BISHOP ATTACKS from d4");

    // הדפסת הכתובת של הלוח (מה שניסית לעשות קודם)
    printf("Board pointer address: %p\n", (void*)board);

    free(board);
    return 0;
}


int game_state(Board *board) {
    // TODO: Need to check If it's stalemate that also covers reverse stalemate's
    if (board->Pieces[BLACK][KING] & RANK_8) {
        return (board->WhiteR8) ? DRAW : BLACK_WIN;
    } else if (board->Pieces[WHITE][KING] & RANK_8) {
        return (board->Side == WHITE) ? NONE : WHITE_WIN;
    }
    return NONE;
}


void validate_move(Board *board, int move) {
    // TODO: Dedive this function to smaller sub-functions each other responsibility
    Square from = move & six_bits;
    Square to = (move >> 6) & six_bits;

    // switch (KnightAttacks[board->Pieces] & )
}


void is_sq_attacked(Board *board, int sq) {
}


void make_move(Board *board, int move) {
    Square from = move & six_bits;
    Square to = (move >> 6) & six_bits;

    Bitboard OCC_ALL = (board->Occ[WHITE] | board->Occ[BLACK]);
    Bitboard OCC_WHITE = (board->Occ[WHITE]);
    Bitboard OCC_BLACK = (board->Occ[BLACK]);

    Bitboard stm = board->Side;
    Bitboard opp = !stm;
    
    Piece pc = board->Grid[from];
    Piece cap = board->Grid[to];

    Bitboard move_bb = (1ULL << from) | (1ULL << to);
    Bitboard to_bb = (1ULL << to);

    if (cap != EMPTY) {
        board->Pieces[opp][cap] ^= to_bb;
        board->Occ[opp] ^= to_bb;
    }

    board->Pieces[stm][pc] ^= move_bb;

    board->Occ[stm] ^= move_bb;

    board->Grid[to] = pc;
    board->Grid[from] = EMPTY;
}
