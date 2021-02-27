//
// Created by ludvig on 27.02.2021.
//

#ifndef JACE_BITBOARDS_H
#define JACE_BITBOARDS_H

#include "types.h"

constexpr bitboard_t FileAM = 0x0101010101010101ULL;
constexpr bitboard_t FileBM = FileAM << 1;
constexpr bitboard_t FileCM = FileAM << 2;
constexpr bitboard_t FileDM = FileAM << 3;
constexpr bitboard_t FileEM = FileAM << 4;
constexpr bitboard_t FileFM = FileAM << 5;
constexpr bitboard_t FileGM = FileAM << 6;
constexpr bitboard_t FileHM = FileAM << 7;
constexpr bitboard_t FileMM[8] = {FileAM, FileBM, FileCM, FileDM, FileEM, FileFM, FileGM, FileHM};

constexpr bitboard_t Rank1M = 0xFF;
constexpr bitboard_t Rank2M = Rank1M << (8 * 1);
constexpr bitboard_t Rank3M = Rank1M << (8 * 2);
constexpr bitboard_t Rank4M = Rank1M << (8 * 3);
constexpr bitboard_t Rank5M = Rank1M << (8 * 4);
constexpr bitboard_t Rank6M = Rank1M << (8 * 5);
constexpr bitboard_t Rank7M = Rank1M << (8 * 6);
constexpr bitboard_t Rank8M = Rank1M << (8 * 7);
constexpr bitboard_t RankMM[8] = {Rank1M, Rank2M, Rank3M, Rank4M, Rank5M, Rank6M, Rank7M, Rank8M};

constexpr bitboard_t EdgeM = FileAM | FileHM | Rank1M | Rank8M;

enum Squares : square_t {A1, B1, C1, D1, E1, F1, G1, H1,
                         A2, B2, C2, D2, E2, F2, G2, H2,
                         A3, B3, C3, D3, E3, F3, G3, H3,
                         A4, B4, C4, D4, E4, F4, G4, H4,
                         A5, B5, C5, D5, E5, F5, G5, H5,
                         A6, B6, C6, D6, E6, F6, G6, H6,
                         A7, B7, C7, D7, E7, F7, G7, H7,
                         A8, B8, C8, D8, E8, F8, G8, H8};

#endif //JACE_BITBOARDS_H
