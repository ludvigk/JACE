//
// Created by ludvig on 27.02.2021.
//

#include "move.h"

bitboard_t get_rook_moves(square_t sq, bitboard_t occ) {
    auto att_idx = pext(occ, RookM[sq]);
    return RookA[sq][att_idx];
}

bitboard_t get_bishop_moves(square_t sq, bitboard_t occ) {
    auto att_idx = pext(occ, BishopM[sq]);
    return BishopA[sq][att_idx];
}