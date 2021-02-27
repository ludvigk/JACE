//
// Created by ludvig on 26.02.2021.
//

#ifndef JACE_BOARD_H
#define JACE_BOARD_H

#include <cstdint>
#include <string>
#include "types.h"
#include "move.h"

void hello();

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
    };

    Board();

    Board(std::string fen);

    void print();

    void legal_moves(Move *move_list);

    void pseudo_legal_moves(Move *move_list);

    void make_move(Move move);

    void unmake_move(Move move);

    bitboard_t get_pieces() { return pieceBB_[nWhite] | pieceBB_[nBlack]; }

    bitboard_t get_pieces(Color cl) { return pieceBB_[cl]; }

    bitboard_t get_pawns(Color cl) { return pieceBB_[cl] & pieceBB_[nPawn] & ~Rank1M & ~Rank8M; }

    bitboard_t get_enpassent() { return Up(Up(pieceBB_[nPawn] & Rank1M)) |
                                        Down(Down(pieceBB_[nPawn] & Rank8M));  }

    bitboard_t get_knights(Color cl) { return pieceBB_[cl] & pieceBB_[nKnight]; }

    bitboard_t get_bishops(Color cl) { return pieceBB_[cl] & pieceBB_[nBishop]; }

    bitboard_t get_rooks(Color cl) { return pieceBB_[cl] & pieceBB_[nRook]; }

    bitboard_t get_king(Color cl) { return pieceBB_[cl] & pieceBB_[nKing]; }

    bitboard_t get_queens(Color cl) { return pieceBB_[cl] & (pieceBB_[nRook] | pieceBB_[nBishop]); }

    bool can_castle_oo() {return castle_oo_; }

    bool can_castle_ooo() {return castle_ooo_; }

    bool is_attacked(square_t sq);

    char get_piece(bitboard_t sq, Color cl) {
        if (!sq & get_pieces(cl)) { return ' '; }
        if (sq & get_pawns(cl)) { return 'P'; }
        if (sq & get_queens(cl)) { return 'Q'; }
        if (sq & get_king(cl)) { return 'K'; }
        if (sq & get_rooks(cl)) { return 'R'; }
        if (sq & get_bishops(cl)) { return 'B'; }
        if (sq & get_knights(cl)) { return 'N'; }
        return ' ';
    }
};

#endif //JACE_BOARD_H
