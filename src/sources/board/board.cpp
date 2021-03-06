#include "board.h"

#include <ctype.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void Board::print() {
    cerr << endl << "--------" << endl;
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            char out = ' ';
            uint64_t k = 1ULL << (i * 8 + j);

            if (pieceBB_[nPawn] & ~Rank1M & ~Rank8M & k & (pieceBB_[nWhite] | pieceBB_[nBlack])) {
                out = 'P';
            } else if (pieceBB_[nKnight] & k) {
                out = 'N';
            } else if (pieceBB_[nKing] & k) {
                out = 'K';
            } else if (pieceBB_[nBishop] & ~pieceBB_[nRook] & k) {
                out = 'B';
            } else if (~pieceBB_[nBishop] & pieceBB_[nRook] & k) {
                out = 'R';
            } else if (pieceBB_[nBishop] & pieceBB_[nRook] & k) {
                out = 'Q';
            }

            if (pieceBB_[nBlack] & k) {
                out = tolower(out);
            }

            cerr << out;
        }
        cerr << endl;
    }
    cerr << "--------" << endl << endl;
}

Board::Board(string fen) {
    zobristHash_ = 0;  // TODO FIX

    cerr << "FEN: " << fen << endl;

    istringstream ss(fen);

    string tmp;

    ss >> tmp;

    pieceBB_[nWhite] = 0;
    pieceBB_[nBlack] = 0;
    pieceBB_[nPawn] = 0;
    pieceBB_[nKnight] = 0;
    pieceBB_[nBishop] = 0;
    pieceBB_[nRook] = 0;
    pieceBB_[nKing] = 0;

    int rank = 7;
    int file = 0;
    int idx;

    for (auto i = 0; i < tmp.size(); i++) {
        auto c = tolower(tmp[i]);

        if (c == '/') {
            rank -= 1;
            file = 0;
            continue;
        } else if (isdigit(c)) {
            file += c - '0';
            continue;
        }

        idx = rank * 8 + file;

        pieceBB_[(c != tmp[i]) ? nWhite : nBlack] |= 1ULL << idx;

        if (c == 'r') {
            pieceBB_[nRook] |= 1ULL << idx;
        } else if (c == 'n') {
            pieceBB_[nKnight] |= 1ULL << idx;
        } else if (c == 'b') {
            pieceBB_[nBishop] |= 1ULL << idx;
        } else if (c == 'q') {
            pieceBB_[nRook] |= 1ULL << idx;
            pieceBB_[nBishop] |= 1ULL << idx;
        } else if (c == 'k') {
            pieceBB_[nKing] |= 1ULL << idx;
        } else if (c == 'p') {
            pieceBB_[nPawn] |= 1ULL << idx;
        } else {
            cerr << "Unknown piece: " << tmp[i] << endl << flush;
            abort();
        }

        file += 1;
    }

    ss >> tmp;
    if (tmp == "w") {
        color_ = WHITE;
    } else if (tmp == "b") {
        color_ = BLACK;
    } else {
        cerr << "Invalid color: " << tmp << endl << flush;
        abort();
    }

    castle_oo_[WHITE] = false;
    castle_oo_[BLACK] = false;
    castle_ooo_[WHITE] = false;
    castle_ooo_[BLACK] = false;

    ss >> tmp;
    if (tmp == "-") {
        // do nothing
    } else {
        for (auto i = 0; i < tmp.size(); i++) {
            auto c = tmp[i];
            if (c == 'K') {
                castle_oo_[WHITE] = true;
            } else if (c == 'Q') {
                castle_ooo_[WHITE] = true;
            } else if (c == 'k') {
                castle_oo_[BLACK] = true;
            } else if (c == 'q') {
                castle_ooo_[BLACK] = true;
            } else {
                cerr << "Invalid castling: " << tmp << endl << flush;
                abort();
            }
        }
    }

    ss >> tmp;
    if (tmp != "-") {
        const char column = tmp[0];
        const char row = tmp[1];

        file = column - 'a';
        rank = row - '3';
        if (rank != 0) {
            rank = 7;
        }
        idx = rank * 8 + file;
        pieceBB_[nPawn] |= 1ULL << idx;
    }

    ss >> half_moves_;
    ss >> full_moves_;
}
