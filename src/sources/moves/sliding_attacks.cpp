#include "move.h"

bitboard_t sliding_rook_attacks(const square_t sq, const bitboard_t occ) {
    auto rank_ = rank(sq);
    auto file_ = file(sq);
    bitboard_t moves = 0ULL;
    for (int i = 0; i < 4; i++) {
        int to_rank = rank_;
        int to_file = file_;
        while (true) {
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
            if (to_rank >= 8 || to_rank < 0 || to_file >= 8 || to_file < 0) {
                break;
            }
            bitboard_t move_pos = 1ULL << square(to_rank, to_file);
            moves |= move_pos;
            if (move_pos & occ) {
                break;
            }
        }
    }
    return moves;
}

bitboard_t sliding_bishop_attacks(const square_t sq, const bitboard_t occ) {
    auto rank_ = rank(sq);
    auto file_ = file(sq);
    bitboard_t moves = 0;
    for (int i = 0; i < 4; i++) {
        int to_rank = rank_;
        int to_file = file_;
        while (true) {
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
                    to_rank--;
                    break;
            }
            if (to_rank >= 8 || to_rank < 0 || to_file >= 8 || to_file < 0) {
                break;
            }
            bitboard_t move_pos = 1ULL << square(to_rank, to_file);
            moves |= move_pos;
            if (move_pos & occ) {
                break;
            }
        }
    }
    return moves;
}
