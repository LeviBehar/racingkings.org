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

#include <stdio.h>

#include "types.h"

#define RANK_8 0xff00000000000000ULL

int game_state(Board *board) {
    if ((board->ByColorBB[BLACK] & board->ByTypeBB[KING]) & RANK_8) {
        switch (board->WhiteR8) {
            case (1):
                return DRAW;
            case (0):
                return BLACK_WIN;
        }
    } else if ((board->ByColorBB[WHITE] & board->ByTypeBB[KING]) & RANK_8) {
        switch (board->Side) {
            case (WHITE):
                return WHITE_WIN;
            case (BLACK):
                return NONE;
        }
    }

    return NONE;
}

void validate_move(void) {

}

void apply_move(void) {

}
