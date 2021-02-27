//
// Created by ludvig on 27.02.2021.
//

#ifndef JACE_TYPES_H
#define JACE_TYPES_H

#include <cstdint>
#include <immintrin.h>

#define pext(b, m) _pext_u64(b, m)
#define pdep(b, m) _pdep_u64(b, m)

typedef uint64_t bitboard_t;
typedef uint64_t zh_t;
typedef int square_t;

enum Color {
    WHITE,
    BLACK
};

Color operator!(Color& cl) { cl == WHITE ? BLACK : WHITE; }

int rank(square_t sq) { return sq / 8; }
int file(square_t sq) { return sq % 8; }
square_t square(int rank, int file) { return rank * 8 + file; }

#endif //JACE_TYPES_H
