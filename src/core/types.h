// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

enum {
    WHITE, BLACK, ALL_COLORS = 2
};

enum States {
    NONE, DRAW, WHITE_WIN, BLACK_WIN, STALEMATE = 4
};

enum PieceType {
    KNIGHT, BISHOP, ROOK, QUEEN, KING, EMPTY = 5
};

typedef uint64_t Bitboard;
typedef uint8_t Color;
typedef uint8_t Square;
typedef uint8_t Piece;

typedef struct {
    Bitboard Pieces[ALL_COLORS][5];
    Bitboard Occ[3];

    Piece Grid[64];

    Color Side;

    uint8_t WhiteR8;
} Board;

#endif
