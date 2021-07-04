//
// Created by ludvig on 27.02.2021.
//

#include "board.h"

bool Board::make_move(Move &move) {

    // En pessent
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

    pieceBB_[nRook] &= ~bb(move.to_);
    pieceBB_[nBishop] &= ~bb(move.to_);
    pieceBB_[nKing] &= ~bb(move.to_);
    pieceBB_[nKnight] &= ~bb(move.to_);
    pieceBB_[nPawn] &= ~bb(move.to_);

    switch (move.promote_) {
        case 'Q':
            pieceBB_[nRook] |= bb(move.to_);
            pieceBB_[nBishop] |= bb(move.to_);
            pieceBB_[nPawn] &= ~bb(move.to_);
            break;
        case 'R':
            pieceBB_[nRook] |= bb(move.to_);
            pieceBB_[nPawn] &= ~bb(move.to_);
            break;
        case 'B':
            pieceBB_[nBishop] |= bb(move.to_);
            pieceBB_[nPawn] &= ~bb(move.to_);
            break;
        case 'N':
            pieceBB_[nKnight] |= bb(move.to_);
            pieceBB_[nPawn] &= ~bb(move.to_);
            break;
        default:
            break;
    }

    if (move.enpassent_ && color_ == WHITE) {
        pieceBB_[nPawn] &= ~bb(move.to_-8);
    } else if (move.enpassent_ && color_ == BLACK) {
        pieceBB_[nPawn] &= ~bb(move.to_+8);
    }

    if (pieceBB_[nRook] & bb(move.from_)) {
        pieceBB_[nRook] &= ~bb(move.from_);
        pieceBB_[nRook] |= bb(move.to_);
    }
    if (pieceBB_[nBishop] & bb(move.from_)) {
        pieceBB_[nBishop] &= ~bb(move.from_);
        pieceBB_[nBishop] |= bb(move.to_);
    }
    if (pieceBB_[nKing] & bb(move.from_)) {
        pieceBB_[nKing] &= ~bb(move.from_);
        pieceBB_[nKing] |= bb(move.to_);
        // Castling
        if (move.from_ == 4 && move.to_ == 6) {
            pieceBB_[nRook] &= ~bb(7);
            pieceBB_[nRook] |= bb(5);
        } else if (move.from_ == 4 && move.to_ == 2) {
            pieceBB_[nRook] &= ~bb(0);
            pieceBB_[nRook] |= bb(3);
        } else if (move.from_ == 60 && move.to_ == 62) {
            pieceBB_[nRook] &= ~bb(63);
            pieceBB_[nRook] |= bb(61);
        } else if (move.from_ == 60 && move.to_ == 58) {
            pieceBB_[nRook] &= ~bb(56);
            pieceBB_[nRook] |= bb(59);
        }
    }
    if (pieceBB_[nKnight] & bb(move.from_)) {
        pieceBB_[nKnight] &= ~bb(move.from_);
        pieceBB_[nKnight] |= bb(move.to_);
    }
    if (pieceBB_[nPawn] & bb(move.from_)) {
        pieceBB_[nPawn] &= ~bb(move.from_);
        pieceBB_[nPawn] |= bb(move.to_);
    }

    pieceBB_[color_] &= ~bb(move.from_);
    pieceBB_[color_] |= bb(move.to_);
    pieceBB_[!color_] &= ~bb(move.to_);

    bool legal = !is_in_check(color_);
    color_ = !color_;
    return legal;
}

bool Board::unmake_move(Move &move) {

    color_ = !color_;

    // TODO: Zobrist hash
    if (move.enpassent_ && color_ == WHITE) {
        pieceBB_[nPawn] |= bb(move.to_-8);
    } else if (move.enpassent_ && color_ == BLACK) {
        pieceBB_[nPawn] |= bb(move.to_+8);
    }

    switch (move.promote_) {
        case 'Q':
            pieceBB_[nRook] &= ~bb(move.to_);
            pieceBB_[nBishop] &= ~bb(move.to_);
            break;
        case 'R':
            pieceBB_[nRook] &= ~bb(move.to_);
            break;
        case 'B':
            pieceBB_[nBishop] &= ~bb(move.to_);
            break;
        case 'N':
            pieceBB_[nKnight] &= ~bb(move.to_);
            break;
        default:
            break;
    }

    if (pieceBB_[nRook] & bb(move.to_)) {
        pieceBB_[nRook] &= ~bb(move.to_);
        pieceBB_[nRook] |= bb(move.from_);
    }
    if (pieceBB_[nBishop] & bb(move.to_)) {
        pieceBB_[nBishop] &= ~bb(move.to_);
        pieceBB_[nBishop] |= bb(move.from_);
    }
    if (pieceBB_[nKing] & bb(move.to_)) {
        pieceBB_[nKing] &= ~bb(move.to_);
        pieceBB_[nKing] |= bb(move.from_);
        // Castling
        if (move.from_ == 4 && move.to_ == 6) {
            pieceBB_[nRook] |= bb(7);
            pieceBB_[nRook] &= ~bb(5);
        } else if (move.from_ == 4 && move.to_ == 2) {
            pieceBB_[nRook] |= bb(0);
            pieceBB_[nRook] &= ~bb(3);
        } else if (move.from_ == 60 && move.to_ == 62) {
            pieceBB_[nRook] |= bb(63);
            pieceBB_[nRook] &= ~bb(61);
        } else if (move.from_ == 60 && move.to_ == 58) {
            pieceBB_[nRook] |= bb(56);
            pieceBB_[nRook] &= ~bb(59);
        }
    }
    if (pieceBB_[nKnight] & bb(move.to_)) {
        pieceBB_[nKnight] &= ~bb(move.to_);
        pieceBB_[nKnight] |= bb(move.from_);
    }
    if (pieceBB_[nPawn] & bb(move.to_)) {
        pieceBB_[nPawn] &= ~bb(move.to_);
        pieceBB_[nPawn] |= bb(move.from_);
    }

    switch (move.capture_) {
        case 'P':
            pieceBB_[nPawn] |= bb(move.to_);
            pieceBB_[!color_] |= bb(move.to_);
            break;
        case 'B':
            pieceBB_[!color_] |= bb(move.to_);
            pieceBB_[nBishop] |= bb(move.to_);
            break;
        case 'N':
            pieceBB_[!color_] |= bb(move.to_);
            pieceBB_[nKnight] |= bb(move.to_);
            break;
        case 'R':
            pieceBB_[!color_] |= bb(move.to_);
            pieceBB_[nRook] |= bb(move.to_);
            break;
        case 'Q':
            pieceBB_[!color_] |= bb(move.to_);
            pieceBB_[nRook] |= bb(move.to_);
            pieceBB_[nBishop] |= bb(move.to_);
            break;
        case 'K':
            pieceBB_[!color_] |= bb(move.to_);
            pieceBB_[nKing] |= bb(move.to_);
            break;
        default:
            break;
    }

    pieceBB_[color_] &= ~bb(move.to_);
    pieceBB_[color_] |= bb(move.from_);

    return true;
}