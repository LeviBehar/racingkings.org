// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdio.h>

#include "types.h"
#include "attack_tables.h"

#define RANK_8 0xff00000000000000ULL

int six_bits = 0x3f;

int game_state(Board *board) {
    // TODO: Need to check If it's stalemate that also covers reverse stalemate's
    if (board->Pieces[BLACK][KING] & RANK_8) {
        return (board->WhiteR8) ? DRAW : BLACK_WIN;
    } else if (board->Pieces[WHITE][KING] & RANK_8) {
        return (board->Side == WHITE) ? NONE : WHITE_WIN;
    }
    if (board->Pieces[!board->Side][KING] & KingAttack) 
    return NONE;
}

void validate_move(void) {
    
}

void make_move(Board *board, int move) {
    int from = move & six_bits;
    int to = (move >> 6) & six_bits;

    int stm = board->Side;
    int opp = !stm;

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
    board->Occ[ALL_COLORS] = (board->Occ[WHITE] | board->Occ[BLACK]);

    board->Grid[to] = pc;
    board->Grid[from] = EMPTY;
}
