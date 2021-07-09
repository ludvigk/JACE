#ifndef JACE_MOVE_H
#define JACE_MOVE_H

#include <array>
#include "types.h"
#include "bitboard.h"

extern bitboard_t SquareM[64];
extern bitboard_t RookM[64];
extern bitboard_t BishopM[64];
extern bitboard_t KnightM[64];
extern bitboard_t KingM[64];
extern bitboard_t PawnA[2][64];
extern bitboard_t PawnM[2][64];
extern bitboard_t RookA[64][1 << 12];
extern bitboard_t BishopA[64][1 << 9];

constexpr bitboard_t Up(const bitboard_t s) { return (s & ~Rank8M) << 8; }

constexpr bitboard_t Down(const bitboard_t s) { return (s & ~Rank1M) >> 8; }

constexpr bitboard_t Left(const bitboard_t s) { return (s & ~FileAM) >> 1; }

constexpr bitboard_t Right(const bitboard_t s) { return (s & ~FileHM) << 1; }

constexpr bitboard_t UpLeft(const bitboard_t s) { return Up(Left(s)); }

constexpr bitboard_t UpRight(const bitboard_t s) { return Up(Right(s)); }

constexpr bitboard_t DownLeft(const bitboard_t s) { return Down(Left(s)); }

constexpr bitboard_t DownRight(const bitboard_t s) { return Down(Right(s)); }

constexpr bitboard_t Forward(const bitboard_t s, const Color cl) { return cl == WHITE ? Up(s) : Down(s); }

constexpr bitboard_t Backward(const bitboard_t s, const Color cl) { return Forward(s, !cl); }

namespace Masks {
    void init();
}

struct Move {
    square_t from_;
    square_t to_;
    bool enpassent_;
    char promote_;
    char capture_;
    bitboard_t pawns;
    std::array<bool,2> castle_oo_;
    std::array<bool,2> castle_ooo_;
};

bitboard_t sliding_rook_attacks(const int sq, const bitboard_t occ);

bitboard_t sliding_bishop_attacks(const int sq, const bitboard_t occ);

bitboard_t get_rook_moves(const int sq, const bitboard_t occ);

bitboard_t get_bishop_moves(const int sq, const bitboard_t occ);

#endif //JACE_MOVE_H
