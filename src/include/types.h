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

constexpr Color operator!(const Color cl) {
    return cl == WHITE ? BLACK : WHITE;
}

constexpr int rank(const square_t sq) {
    return sq / 8;
}

constexpr int file(const square_t sq) {
    return sq % 8;
}

constexpr square_t square(const int rank, const int file) {
    return rank * 8 + file;
}
constexpr bitboard_t bb(const square_t sq) {
    return 1ULL << sq;
}

#endif //JACE_TYPES_H
