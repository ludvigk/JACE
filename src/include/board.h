//
// Created by ludvig on 26.02.2021.
//

#ifndef JACE_BOARD_H
#define JACE_BOARD_H

#include <cstdint>
#include <string>
#include "move.h"
#include "types.h"

extern zh_t StartZH;
extern zh_t PawnZH[64];
extern zh_t RookZH[64];
extern zh_t BishopZH[64];
extern zh_t KingZH[64];
extern zh_t WhiteZH[64];
extern zh_t BlackZH[64];
extern zh_t ColorZH;

namespace zobrist_hashes {
void init();
}

class Board {
   private:
    bitboard_t pieceBB_[7];
    zh_t zobristHash_;
    Color color_;
    int half_moves_;
    int full_moves_;
    bool castle_oo_[2];
    bool castle_ooo_[2];

   public:
    enum enumPiece {
        nWhite,
        nBlack,
        nPawn,
        nKnight,
        nBishop,
        nRook,
        nKing
        //
    };

    Board();

    Board(std::string fen);

    Board(const Board& b) {
        pieceBB_[0] = b.pieceBB_[0];
        pieceBB_[1] = b.pieceBB_[1];
        pieceBB_[2] = b.pieceBB_[2];
        pieceBB_[3] = b.pieceBB_[3];
        pieceBB_[4] = b.pieceBB_[4];
        pieceBB_[5] = b.pieceBB_[5];
        pieceBB_[6] = b.pieceBB_[6];
        color_ = b.color_;
    };

    void print();

    void legal_moves(Move* move_list);

    int pseudo_legal_moves(Move* move_list);

    zh_t zobrist(Move move);

    bool make_move(Move move);

    bool unmake_move(Move move);

    bitboard_t get_pieces() { return pieceBB_[nWhite] | pieceBB_[nBlack]; }

    bitboard_t get_pieces(Color cl) { return pieceBB_[cl]; }

    bitboard_t get_pawns(Color cl) {
        return pieceBB_[cl] & pieceBB_[nPawn] & ~Rank1M & ~Rank8M;
    }

    bitboard_t get_enpassent() {
        return Up(Up(pieceBB_[nPawn] & Rank1M)) |
               Down(Down(pieceBB_[nPawn] & Rank8M));
    }

    bitboard_t get_knights(Color cl) {
        return pieceBB_[cl] & pieceBB_[nKnight];
    }

    bitboard_t get_bishops(Color cl) {
        return pieceBB_[cl] & pieceBB_[nBishop];
    }

    bitboard_t get_rooks(Color cl) { return pieceBB_[cl] & pieceBB_[nRook]; }

    bitboard_t get_king(Color cl) { return pieceBB_[cl] & pieceBB_[nKing]; }

    bitboard_t get_queens(Color cl) {
        return pieceBB_[cl] & (pieceBB_[nRook] | pieceBB_[nBishop]);
    }

    bool can_castle_oo() { return castle_oo_[color_]; }

    bool can_castle_ooo() { return castle_ooo_[color_]; }

    bool is_attacked(square_t sq);

    bool is_in_check(Color color);

    char get_piece(bitboard_t sq, Color cl) {
        if (!sq & get_pieces(cl)) {
            return ' ';
        }
        if (sq & get_pawns(cl)) {
            return 'P';
        }
        if (sq & get_queens(cl)) {
            return 'Q';
        }
        if (sq & get_king(cl)) {
            return 'K';
        }
        if (sq & get_rooks(cl)) {
            return 'R';
        }
        if (sq & get_bishops(cl)) {
            return 'B';
        }
        if (sq & get_knights(cl)) {
            return 'N';
        }
        return ' ';
    }
};

#endif  // JACE_BOARD_H
