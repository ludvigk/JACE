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

Color operator!(Color& cl);

int rank(square_t sq);
int file(square_t sq);
square_t square(int rank, int file);
bitboard_t bb(square_t sq);

#endif //JACE_TYPES_H
