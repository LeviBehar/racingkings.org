// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdio.h>
#include "types.h"
#include <stdlib.h>
#include <stdbool.h>
#include "./attacksDB/slidingDB.h"
#include "./attacksDB/non_slidingDB.h"

#define RANK_8 0xff00000000000000ULL

int six_bits = 0x3F;


void pretty(Bitboard bb) {
    printf("+---+---+---+---+---+---+---+---+\n");

    for (int r = 7; r >= 0; --r)
    {
        for (int f = 0; f <= 7; ++f)
        {
            printf(bb & (1ULL << (r * 8 + f)) ? "| X " : "|   ");
        }

        printf("| %d\n+---+---+---+---+---+---+---+---+\n", 1 + r);
    }
    printf("  a   b   c   d   e   f   g   h\n");
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

// function dev in progress
void validate_move(Board *board, int move) {
    Bitboard OCC_ALL = (board->Occ[WHITE] | board->Occ[BLACK]);
    Bitboard OCC_WHITE = (board->Occ[WHITE]);
    Bitboard OCC_BLACK = (board->Occ[BLACK]);
    // TODO: Dedive this function to smaller sub-functions each other responsibility
    Square from = move & six_bits;
    Square to = (move >> 6) & six_bits;
}

// function dev in progress
bool is_sq_attacked(Board *board, int sq) {
    Bitboard stm = board->Side;
    Bitboard opp = (stm ^ 1);
    
    switch (sq) {
        case (): return true;
        case (): return true;
        case (): return true;
        case (): return true;
    }
}


void make_move(Board *board, int move) {
    Square from = move & six_bits;
    Square to = (move >> 6) & six_bits;

    Bitboard stm = board->Side;
    Bitboard opp = (stm ^ 1);
    
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


void switch_side(Board *board) {
    board->Side ^= 1;
}
