// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef SLIDINGDB_H
#define SLIDINGDB_H

#include "../types.h"

Bitboard get_straight_attacks(Square sq, Bitboard occ);
Bitboard get_diagonal_attacks(Square sq, Bitboard occ);

#endif
