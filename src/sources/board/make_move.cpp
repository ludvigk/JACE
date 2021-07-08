//
// Created by ludvig on 27.02.2021.
//

#include "board.h"

bool Board::make_move(Move &move) {

    bitboard_t move_toBB = SquareM[move.to_];
    bitboard_t move_fromBB = SquareM[move.from_];

    // En passant
    pieceBB_[nPawn] &= ~(Rank1M | Rank8M);

    // TODO: Zobrist hash
    switch (move.capture_) {
        case 'p':
            break;
        case 'b':
            break;
        case 'n':
            break;
        case 'r':
            break;
        case 'q':
            break;
        case 'k':
            break;
        default:
            break;
    }

    if (((move.to_ == 0) && (color_ == BLACK)) || ((move.to_ == 56) && (color_ == WHITE))) {
        castle_ooo_[!color_] = false;
    } else if (((move.to_ == 7) && (color_ == BLACK)) || ((move.to_ == 63) && (color_ == WHITE))) {
        castle_oo_[!color_] = false;
    }

    pieceBB_[nRook] &= ~move_toBB;
    pieceBB_[nBishop] &= ~move_toBB;
    pieceBB_[nKing] &= ~move_toBB;
    pieceBB_[nKnight] &= ~move_toBB;
    pieceBB_[nPawn] &= ~move_toBB;

    if (move.enpassent_ && (color_ == WHITE)) {
        pieceBB_[nPawn] &= ~bb(move.to_-8);
        pieceBB_[!color_] &= ~bb(move.to_-8);
    } else if (move.enpassent_ && (color_ == BLACK)) {
        pieceBB_[nPawn] &= ~bb(move.to_+8);
        pieceBB_[!color_] &= ~bb(move.to_+8);
        // this->print();
    }

    if (pieceBB_[nRook] & move_fromBB) {
        move_piece(move.from_, move.to_, nRook, color_);
        if (((move.from_ == 0) && (color_ == WHITE)) || ((move.from_ == 56) && (color_ == BLACK))) {
            castle_ooo_[color_] = false;
        } else if (((move.from_ == 7) && (color_ == WHITE)) || ((move.from_ == 63) && (color_ == BLACK))) {
            castle_oo_[color_] = false;
        }
        if (((move.to_ == 0) && (color_ == WHITE)) || ((move.to_ == 56) && (color_ == BLACK))) {
            castle_ooo_[color_] = false;
        } else if (((move.to_ == 7) && (color_ == WHITE)) || ((move.to_ == 63) && (color_ == BLACK))) {
            castle_oo_[color_] = false;
        }
    }
    if (pieceBB_[nBishop] & move_fromBB) {
        move_piece(move.from_, move.to_, nBishop, color_);
    }
    if (pieceBB_[nKing] & move_fromBB) {
        move_piece(move.from_, move.to_, nKing, color_);
        castle_oo_[color_] = false;
        castle_ooo_[color_] = false;
        // Castling
        if (move.from_ == 4 && move.to_ == 6) {
            move_piece(7, 5, nRook, color_);
        } else if (move.from_ == 4 && move.to_ == 2) {
            move_piece(0, 3, nRook, color_);
        } else if (move.from_ == 60 && move.to_ == 62) {
            move_piece(63, 61, nRook, color_);
        } else if (move.from_ == 60 && move.to_ == 58) {
            move_piece(56, 59, nRook, color_);
        }
    }
    if (pieceBB_[nKnight] & move_fromBB) {
        move_piece(move.from_, move.to_, nKnight, color_);
    }
    if (this->get_pawns(color_) & move_fromBB) {
        pieceBB_[nPawn] &= ~move_fromBB;
        pieceBB_[nPawn] |= move_toBB;
        pieceBB_[color_] |= move_toBB;
        if ((move_toBB & Rank4M) && (move_fromBB & Rank2M)) {
            pieceBB_[nPawn] |= bb(move.from_ - 8);
        }
        if ((move_toBB & Rank5M) && (move_fromBB & Rank7M)) {
            pieceBB_[nPawn] |= bb(move.from_ + 8);
        }
    }

    switch (move.promote_) {
        case 'Q':
            pieceBB_[nRook] |= move_toBB;
            pieceBB_[nBishop] |= move_toBB;
            pieceBB_[nPawn] &= ~move_toBB;
            break;
        case 'R':
            pieceBB_[nRook] |= move_toBB;
            pieceBB_[nPawn] &= ~move_toBB;
            break;
        case 'B':
            pieceBB_[nBishop] |= move_toBB;
            pieceBB_[nPawn] &= ~move_toBB;
            break;
        case 'N':
            pieceBB_[nKnight] |= move_toBB;
            pieceBB_[nPawn] &= ~move_toBB;
            break;
        default:
            break;
    }

    pieceBB_[color_] &= ~move_fromBB;
    pieceBB_[color_] |= move_toBB;
    pieceBB_[!color_] &= ~move_toBB;

    bool legal = !is_in_check(color_);
    color_ = !color_;
//    this->print();
    return legal;
}

bool Board::unmake_move(Move &move) {

    bitboard_t move_toBB = SquareM[move.to_];
    bitboard_t move_fromBB = SquareM[move.from_];

    color_ = !color_;

    // TODO: Zobrist hash
    if (move.enpassent_ && (color_ == WHITE)) {
        pieceBB_[nPawn] |= SquareM[move.to_-8];
        pieceBB_[!color_] |= SquareM[move.to_-8];
        pieceBB_[!color_] |= SquareM[move.to_-8];

    } else if (move.enpassent_ && (color_ == BLACK)) {
        pieceBB_[nPawn] |= SquareM[move.to_+8];
        pieceBB_[!color_] |= SquareM[move.to_+8];
    }

    switch (move.promote_) {
        case 'Q':
            pieceBB_[nRook] &= ~move_toBB;
            pieceBB_[nBishop] &= ~move_toBB;
            break;
        case 'R':
            pieceBB_[nRook] &= ~move_toBB;
            break;
        case 'B':
            pieceBB_[nBishop] &= ~move_toBB;
            break;
        case 'N':
            pieceBB_[nKnight] &= ~move_toBB;
            break;
        default:
            break;
    }

    if (pieceBB_[nRook] & move_toBB) {
        pieceBB_[nRook] &= ~move_toBB;
        pieceBB_[nRook] |= move_fromBB;
    }
    if (pieceBB_[nBishop] & move_toBB) {
        pieceBB_[nBishop] &= ~move_toBB;
        pieceBB_[nBishop] |= move_fromBB;
    }
    if (pieceBB_[nKing] & move_toBB) {
        pieceBB_[nKing] &= ~move_toBB;
        pieceBB_[nKing] |= move_fromBB;
        // Castling
        if (move.from_ == 4 && move.to_ == 6) {
            move_piece(5, 7, nRook, color_);
        } else if (move.from_ == 4 && move.to_ == 2) {
            move_piece(3, 0, nRook, color_);
        } else if (move.from_ == 60 && move.to_ == 62) {
            move_piece(61, 63, nRook, color_);
        } else if (move.from_ == 60 && move.to_ == 58) {
            move_piece(59, 56, nRook, color_);
        }
    }
    if (pieceBB_[nKnight] & move_toBB) {
        pieceBB_[nKnight] &= ~move_toBB;
        pieceBB_[nKnight] |= move_fromBB;
    }
    if (pieceBB_[nPawn] & move_toBB) {
        pieceBB_[nPawn] &= ~move_toBB;
        pieceBB_[nPawn] |= move_fromBB;
    }

    switch (move.capture_) {
        case 'P':
            pieceBB_[nPawn] |= move_toBB;
            pieceBB_[!color_] |= move_toBB;
            break;
        case 'B':
            pieceBB_[!color_] |= move_toBB;
            pieceBB_[nBishop] |= move_toBB;
            break;
        case 'N':
            pieceBB_[!color_] |= move_toBB;
            pieceBB_[nKnight] |= move_toBB;
            break;
        case 'R':
            pieceBB_[!color_] |= move_toBB;
            pieceBB_[nRook] |= move_toBB;
            break;
        case 'Q':
            pieceBB_[!color_] |= move_toBB;
            pieceBB_[nRook] |= move_toBB;
            pieceBB_[nBishop] |= move_toBB;
            break;
        case 'K':
            pieceBB_[!color_] |= move_toBB;
            pieceBB_[nKing] |= move_toBB;
            break;
        default:
            break;
    }
    pieceBB_[nPawn] = move.pawns;
    castle_oo_ = move.castle_oo_;
    castle_ooo_ = move.castle_ooo_;

    pieceBB_[color_] &= ~move_toBB;
    pieceBB_[color_] |= move_fromBB;

    return true;
}
