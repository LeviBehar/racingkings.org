// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdio.h>
#include "types.h"
#include "./attacksDB/slidingDB.c"
#include "./attacksDB/non_slidingDB.c"

#define RANK_8 0xff00000000000000ULL
#define OCC_ALL (board->Occ[WHITE] | board->Occ[BLACK])
#define OCC_WHITE (board->Occ[WHITE])
#define OCC_BLACK (board->Occ[BLACK])


int six_bits = 0x3f;

int game_state(Board *board) {
    // TODO: Need to check If it's stalemate that also covers reverse stalemate's
    if (board->Pieces[BLACK][KING] & RANK_8) {
        return (board->WhiteR8) ? DRAW : BLACK_WIN;
    } else if (board->Pieces[WHITE][KING] & RANK_8) {
        return (board->Side == WHITE) ? NONE : WHITE_WIN;
    }
    if (board->Pieces[!board->Side][KING] & KingAttacks) 
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

    Bitboard stm = board->Side;
    Bitboard opp = !stm;
    
    Piece pc = board->Grid[from];
    Piece cap = board->Grid[to];

    Bitboard move_bb = (1ULL << from) | (1ULL << to);
    Bitboard to_bb = (1ULL << from);

    if (cap != EMPTY) {
        board->Pieces[opp][cap] ^= dest_mask;
        board->Occ[opp] ^= dest_mask;
    }

    board->Pieces[stm][pc] ^= move_mask;

    board->Occ[stm] ^= move_mask;

    board->Grid[to] = pc;
    board->Grid[from] = EMPTY;
}
