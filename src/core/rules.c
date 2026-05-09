// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdio.h>
#include "types.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "./attacksDB/slidingDB.h"
#include "./attacksDB/non_slidingDB.h"

#define RANK_8 0xff00000000000000ULL
#define SET_BB(sq) (1ULL << (sq))

int six_bits = 0x3F;
int three_bits = 0x7;


// Prints visual bitboard for debugging purposes.
void pretty(Bitboard b) {
    printf("+---+---+---+---+---+---+---+---+\n");

    for (int r = 7; r >= 0; --r)
    {
        for (int f = 0; f <= 7; ++f)
        {
            printf(b & (1ULL << (r * 8 + f)) ? "| X " : "|   ");
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
bool validate_move(Board *board, int move) {
    Bitboard occ_all = (board->Occ[WHITE] | board->Occ[BLACK]);
    // TODO: Dedive this function to smaller sub-functions each other responsibility
    Square from = move & six_bits;
    Square to = (move >> 6) & six_bits;
    Piece pc = (move >> 12) & three_bits;

    Bitboard stm = board->Side;
    Bitboard opp = (stm ^ 1);
    
    if (!(board->Occ[stm] & SET_BB(from))) return false;

    if (!(get_attacks(from, pc, occ_all) & SET_BB(to)) || (SET_BB(to) & board->Occ[stm])) return false;

}


bool is_sq_attacked(Board *board, Square sq, Color attack_color) {
    Bitboard occ_all = (board->Occ[WHITE] | board->Occ[BLACK]);

    Bitboard stm = (attack_color ^ 1);
    Bitboard opp = attack_color;
    
    if (get_king_attacks(sq) & board->Pieces[opp][KING]) return true;
    if (get_knight_attacks(sq) & board->Pieces[opp][KNIGHT]) return true;
    if (get_diagonal_attacks(sq, occ_all) & (board->Pieces[opp][BISHOP] | board->Pieces[opp][QUEEN])) return true;
    if (get_straight_attacks(sq, occ_all) & (board->Pieces[opp][ROOK] | board->Pieces[opp][QUEEN])) return true;

    return false;
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


Bitboard get_attacks(Square sq, Piece pc, Bitboard occ_all) {
    switch (pc) {
        case (KNIGHT):
            return get_knight_attacks(sq);
        case (KING):
            return get_king_attacks(sq);
        case (ROOK):
            return get_straight_attacks(sq, occ_all);
        case (BISHOP):
            return get_diagonal_attacks(sq, occ_all);
        case (QUEEN):
            return (get_diagonal_attacks(sq, occ_all) | get_straight_attacks(sq, occ_all));
        default:
            return 0ULL;
    }
}


// NOTE: main function is for testing purpose only
int main(void) {
    Board *board = malloc(sizeof(Board));
    memset(board, 0, sizeof(Board));

    board->Pieces[WHITE][ROOK]   |= (1ULL << A1);
    board->Pieces[BLACK][KNIGHT] |= (1ULL << C1);

    board->Occ[WHITE] |= (1ULL << A1);
    board->Occ[BLACK] |= (1ULL << C1);

    board->Grid[A1] = ROOK;
    board->Grid[C1] = KNIGHT;

    Bitboard occ_all = (board->Occ[WHITE] | board->Occ[BLACK]);
    Bitboard occ_white = (board->Occ[WHITE]);
    Bitboard occ_black = (board->Occ[BLACK]);

    board->Side = BLACK;

    Bitboard bb = get_straight_attacks(A1, occ_all);

    pretty(bb);
}
