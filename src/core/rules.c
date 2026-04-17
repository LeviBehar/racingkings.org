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

void validate_move(Board *board, int move) {
    // TODO: Dedive this function to smaller sub-functions each other responsibility
    unpack_move(int move);

    switch (KnightsAttacks[board->Pieces] & )
}


void is_sq_attacked(Board *board, int sq) {
}


void make_move(Board *board, int move) {
    unpack_move(int move);
    name_sides&occ[Board *board];

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
    occ_all = (occ_white | occ_black);

    board->Grid[to] = pc;
    board->Grid[from] = EMPTY;
}

void unpack_move(int move) {
    Square from = move & six_bits;
    Square to = (move >> 6) & six_bits;
}

void name_sides&occ[Board *board] {
    Bitboard stm = board->Side;
    Bitboard opp = !stm;

    Bitboard occ_all = board->Occ[ALL_COLORS];
    Bitboard occ_white = board->Occ[WHITE];
    Bitboard occ_black = board->Occ[BLACK];
}
