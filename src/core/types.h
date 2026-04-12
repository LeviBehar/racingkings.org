// Copyright (C) 2026 Levi Behar
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

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
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, PIECE_NB = 6
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
