//
// Created by ludvig on 26.02.2021.
//

#ifndef JACE_BOARD_H
#define JACE_BOARD_H

#include <cstdint>
#include <string>

typedef uint64_t bitboard_t;
typedef uint64_t zh_t;

enum color {
    WHITE,
    BLACK
};

struct Move {
    bitboard_t from_;
    bitboard_t to_;
    bool enpassent_;
    char promote_;
    char capture_;
};

class Board {
private:
    bitboard_t pieceBB_[7];
    zh_t zobristHash_;
    color color_;
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

    Board(std::string fen);

    void generate_moves(Move *move_list);
    void make_move(Move move);
    void unmake_move(Move move);

    bitboard_t get_pieces(){return pieceBB_[nWhite] | pieceBB_[nBlack];}
    bitboard_t get_pieces(color cl){return pieceBB_[cl];}
    bitboard_t get_pawns(color cl){return pieceBB_[cl] & pieceBB_[nPawn];}
    bitboard_t get_knight(color cl){return pieceBB_[cl] & pieceBB_[nKnight];}
    bitboard_t get_bishop(color cl){return pieceBB_[cl] & pieceBB_[nBishop];}
    bitboard_t get_rook(color cl){return pieceBB_[cl] & pieceBB_[nRook];}
    bitboard_t get_king(color cl){return pieceBB_[cl] & pieceBB_[nKing];}
    bitboard_t get_queen(color cl){return pieceBB_[cl] & (pieceBB_[nRook] | pieceBB_[nBishop]);}
};

#endif //JACE_BOARD_H
