#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <string>
#include <sstream>

#include "board.h"

using namespace std;

void hello(){
    cerr << "Hello, World!" << endl;
}

Board::Board(){
    zobristHash_ = 0; // TODO FIX

    color_ = WHITE;

    half_moves_ = 0;
    full_moves_ = 1;

    castle_oo_[WHITE] = true;
    castle_oo_[BLACK] = true;
    castle_ooo_[WHITE] = true;
    castle_ooo_[BLACK] = true;

    pieceBB_[nWhite] = ((1ULL << 16) - 1) << 0;
    pieceBB_[nBlack] = ((1ULL << 16) - 1) << 48;

    pieceBB_[nPawn] = ((1ULL << 8) - 1) << 8;
    pieceBB_[nPawn] |= ((1ULL << 8) - 1) << 48;

    pieceBB_[nKnight] = (1ULL << 1) | (1ULL << 6) | (1ULL << 57) | (1ULL << 62);

    pieceBB_[nKing] = (1ULL << 4) | (1ULL << 60);

    pieceBB_[nRook] = (1ULL << 0) | (1ULL << 7) | (1ULL << 56) | (1ULL << 63);
    pieceBB_[nRook] |= (1ULL << 3) | (1ULL << 59);

    pieceBB_[nBishop] = (1ULL << 2) | (1ULL << 5) | (1ULL << 58) | (1ULL << 61);
    pieceBB_[nBishop] |= (1ULL << 3) | (1ULL << 59);
}

void Board::print(){
    cerr << endl << "--------" << endl;
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            char out = ' ';
            uint64_t k = 1ULL << (i * 8 + j);

            if (pieceBB_[nPawn] & k){
                out = 'P';
            }
            else if (pieceBB_[nKnight] & k){
                out = 'N';
            }
            else if (pieceBB_[nKing] & k){
                out = 'K';
            }
            else if (pieceBB_[nBishop] & ~pieceBB_[nRook] & k){
                out = 'B';
            }
            else if (~pieceBB_[nBishop] & pieceBB_[nRook] & k){
                out = 'R';
            }
            else if (pieceBB_[nBishop] & pieceBB_[nRook] & k){
                out = 'Q';
            }

            if (pieceBB_[nBlack] & k){
                out = tolower(out);
            }

            cerr << out;
        }
        cerr << endl;
    }
    cerr << "--------" << endl << endl;
}

Board::Board(string fen){
    zobristHash_ = 0; // TODO FIX

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

        if (c == '/'){
            rank -= 1;
            file = 0;
            continue;
        }
        else if (isdigit(c)){
            file += c - '0';
            continue;
        }

        idx = rank * 8 + file;

        pieceBB_[(c != tmp[i]) ? nWhite : nBlack] |= 1ULL << idx;

        if (c == 'r'){
            pieceBB_[nRook] |= 1ULL << idx;
        }
        else if (c == 'n'){
            pieceBB_[nKnight] |= 1ULL << idx;
        }
        else if (c == 'b'){
            pieceBB_[nBishop] |= 1ULL << idx;
        }
        else if (c == 'q'){
            pieceBB_[nRook] |= 1ULL << idx;
            pieceBB_[nBishop] |= 1ULL << idx;
        }
        else if (c == 'k'){
            pieceBB_[nKing] |= 1ULL << idx;
        }
        else if (c == 'p'){
            pieceBB_[nPawn] |= 1ULL << idx;
        }
        else {
            cerr << "Unknown piece: " << tmp[i] << endl << flush;
            abort();
        }

        file += 1;
    }

    ss >> tmp;
    if (tmp == "w"){
        color_ = WHITE;
    }
    else if (tmp == "b"){
        color_ = BLACK;
    }
    else {
        cerr << "Invalid color: " << tmp << endl << flush;
        abort();
    }

    castle_oo_[WHITE] = false;
    castle_oo_[BLACK] = false;
    castle_ooo_[WHITE] = false;
    castle_ooo_[BLACK] = false;

    ss >> tmp;
    if (tmp == "-"){
        // do nothing
    }
    else {
        for (auto i = 0; i < tmp.size(); i++) {
            auto c = tmp[i];
            if (c == 'K'){
                castle_oo_[WHITE] = true;
            }
            else if (c == 'Q'){
                castle_ooo_[WHITE] = true;
            }
            else if (c == 'k'){
                castle_oo_[BLACK] = true;
            }
            else if (c == 'q'){
                castle_ooo_[BLACK] = true;
            }
            else {
                cerr << "Invalid castling: " << tmp << endl << flush;
                abort();
            }
        }
    }

    // TODO parse enpassant
    ss >> tmp;
    if (tmp != "-") {
        cerr << "No support for en passant target square: " << tmp << endl << flush;
        abort();
    }

    ss >> half_moves_;
    ss >> full_moves_;
}
