//
// Created by ludvig on 27.02.2021.
//

#include "move.h"

bitboard_t SquareM[64];
bitboard_t RookM[64];
bitboard_t BishopM[64];
bitboard_t KnightM[64];
bitboard_t KingM[64];
bitboard_t PawnA[2][64];
bitboard_t PawnM[2][64];
bitboard_t RookA[64][1 << 12];
bitboard_t BishopA[64][1 << 9];

void Masks::init() {
    for (square_t sq = A1; sq <= H8; sq++) { SquareM[sq] = 1ULL << sq; }
    for (square_t sq = A1; sq <= H8; sq++) {
        auto rank_ = rank(sq);
        auto file_ = file(sq);
        bitboard_t sqBB = SquareM[sq];
        KnightM[sq] = Up(UpRight(sqBB)      | UpLeft(sqBB))   |
                      Down(DownRight(sqBB)  | DownLeft(sqBB)) |
                      Left(DownLeft(sqBB)   | UpLeft(sqBB))   |
                      Right(DownRight(sqBB) | UpRight(sqBB));
        KingM[sq] = Up(sqBB)        | Down(sqBB)    |
                    Left(sqBB)      | Right(sqBB)   |
                    UpLeft(sqBB)    | UpRight(sqBB) |
                    DownRight(sqBB) | DownLeft(sqBB);
        PawnA[WHITE][sq] = Up(Left(sqBB) | Right(sqBB));
        PawnA[BLACK][sq] = Down(Left(sqBB) | Right(sqBB));
        PawnM[WHITE][sq] = Up(sqBB) | Up(Up(sqBB & Rank2M));
        PawnM[BLACK][sq] = Down(sqBB) | Down(Down(sqBB & Rank7M));

        bitboard_t edge = ((Rank1M | Rank8M) & ~RankMM[rank_]) |
                        ((FileAM | FileHM) & ~FileMM[file_]);

        RookM[sq] = sliding_rook_attacks(sq, 0ULL) & ~edge;
        BishopM[sq] = sliding_bishop_attacks(sq, 0ULL) & ~edge;

        uint8_t nsr = __builtin_popcountll(RookM[sq]);
        for (int i = 0; i < (1ULL << nsr); i++){
            bitboard_t occ = pdep(i, RookM[sq]);
            RookA[sq][i] = sliding_rook_attacks(sq, occ);
        }
        uint8_t nsb = __builtin_popcountll(BishopM[sq]);
        for (int i = 0; i < (1ULL << nsb); i++){
            bitboard_t occ = pdep(i, BishopM[sq]);
            BishopA[sq][i] = sliding_bishop_attacks(sq, occ);
        }
    }
}
