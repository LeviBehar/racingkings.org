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
    int src = move & six_bits;
    int dest = (move >> 6) & six_bits;

    Piece moving_piece = board->Grid[src];
    Bitboard dest_mask = (1ULL << dest);
    Bitboard src_mask = (1ULL << src);
    Bitboard move_mask = (1ULL << src) | (1ULL << dest);

    if (board->Occupancy[!board->Side] & dest_mask) {
        Piece captured_piece = board->Grid[dest];
        board->Pieces[!board->Side][captured_piece] ^= dest_mask;
    }
    if (!board->Occupancy[ALL_COLORS] & dest_mask) {
        board->Occupancy[board->Side] ^= src_mask;
    }
    board->Occupancy[!board->Side] ^= dest_mask;
    board->Occupancy[ALL_COLORS] ^= move_mask;
    board->Grid[dest] = moving_piece;
    board->Grid[src] = EMPTY;
}
