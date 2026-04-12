// Copyright (c) 2026 Levi Behar.
// Project: Racing King Chess Variant Platform RacingKings.org 
// This project is Open Source under the MIT License.
// Note: Attack tables in this file were precomputed for performance.

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

enum {
    WHITE, BLACK, COLOR_NB = 2
};

enum States {
    NONE, DRAW, WHITE_WIN, BLACK_WIN = 3
};

enum PieceType {
    KNIGHT, BISHOP, ROOK, QUEEN, KING, PIECE_NB = 5
};

typedef uint64_t Bitboard;
typedef uint8_t Color;
typedef uint8_t Square;
typedef uint8_t Piece;

typedef struct {
    Bitboard ByColorBB[COLOR_NB];
    Bitboard ByTypeBB[PIECE_NB];

    Color Side;

    uint8_t WhiteR8;
} Board;

#endif
