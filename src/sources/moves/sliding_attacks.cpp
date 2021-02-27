//
// Created by ludvig on 27.02.2021.
//

#include "move.h"

bitboard_t sliding_rook_attacks(const square_t sq, const bitboard_t occ) {
    auto rank_ = rank(sq);
    auto file_ = file(sq);
    bitboard_t moves = 0;
    for (int i = 0; i < 4; i++) {
        auto to_rank = rank_;
        auto to_file = file_;
        while (to_rank < 8 && to_rank >= 0 and to_file < 8 && to_file >= 0) {
            switch (i) {
                case 0:
                    to_rank++;
                    break;
                case 1:
                    to_rank--;
                    break;
                case 2:
                    to_file++;
                    break;
                case 3:
                    to_file--;
                    break;
            }
            bitboard_t move_pos = 1ULL << square(rank_, file_);
            if (move_pos & occ) {
                break;
            }
            moves |= move_pos;
        }
    }
    return moves;
}

bitboard_t sliding_bishop_attacks(const square_t sq, const bitboard_t occ) {
    auto rank_ = rank(sq);
    auto file_ = file(sq);
    bitboard_t moves = 0;
    for (int i = 0; i < 4; i++) {
        auto to_rank = rank_;
        auto to_file = file_;
        while (to_rank < 8 && to_rank >= 0 and to_file < 8 && to_file >= 0) {
            switch (i) {
                case 0:
                    to_rank++;
                    to_file++;
                    break;
                case 1:
                    to_rank--;
                    to_file++;
                    break;
                case 2:
                    to_rank++;
                    to_file--;
                    break;
                case 3:
                    to_file--;
                    to_file--;
                    break;
            }
            bitboard_t move_pos = 1ULL << square(rank_, file_);
            if (move_pos & occ) {
                break;
            }
            moves |= move_pos;
        }
    }
    return moves;
}