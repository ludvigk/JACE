//
// Created by ludvig on 27.02.2021.
//

#include "types.h"

int rank(square_t sq) { return sq / 8; }
int file(square_t sq) { return sq % 8; }
square_t square(int rank, int file) { return rank * 8 + file; }
bitboard_t bb(square_t sq) { return 1ULL << sq; }