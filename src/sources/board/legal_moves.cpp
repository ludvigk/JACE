//
// Created by ludvig on 27.02.2021.
//

#include <iostream>
#include <bitset>
#include "board.h"

bool Board::is_attacked(square_t sq){
    if (get_rook_moves(sq, this->get_pieces()) & this->get_rooks(!color_)){return true;}
    if (get_bishop_moves(sq, this->get_pieces()) & this->get_bishops(!color_)){return true;}
    if (KingM[sq] & this->get_king(color_)){return true;}
    if (PawnA[color_][sq] & this->get_pawns(!color_)){return true;}
    if (KnightM[sq] & this->get_knights(color_)){return true;}
    return false;
}

bool Board::is_in_check(Color color){
    square_t sq = __builtin_ctzl(pieceBB_[color] & pieceBB_[nKing]);
    return is_attacked(sq);
}

int Board::pseudo_legal_moves(Move *move_list) {
    int move_idx = 0;
    for (square_t sq = A1; sq <= H8; sq++) {
        bitboard_t sqBB = 1ULL << sq;
        if (!this->get_pieces(color_) & sqBB) {
            continue;
        }

        // King
        if (sqBB & this->get_king(color_)) {
            auto moves = KingM[sq] & ~this->get_pieces(color_);
            square_t to_sq = 0;
            while (moves != 0) {
                auto t = moves & -moves;
                to_sq = __builtin_ctzl(moves);
                char capture = this->get_piece(1ULL << to_sq, !color_);
                move_list[move_idx++] = Move {sq, to_sq, false, ' ', capture};
                moves ^= t;
            }
            if (this->can_castle_oo()) {
                auto home_rank = color_ == WHITE ? Rank1M : Rank8M;
                auto sq1 = __builtin_ctzl(home_rank & FileFM);
                auto sq2 = __builtin_ctzl(home_rank & FileGM);
                if (!((SquareM[sq1] | SquareM[sq2]) & this->get_pieces())){
                    if (!is_attacked(sq) && !is_attacked(sq1) && !is_attacked(sq2)){
                        move_list[move_idx++] = Move {sq, sq2, false, ' ', ' '};
                    }
                }
            }
            if (this->can_castle_ooo()) {
                auto home_rank = color_ == WHITE ? Rank1M : Rank8M;
                auto sq1 = __builtin_ctzl(home_rank & FileBM);
                auto sq2 = __builtin_ctzl(home_rank & FileCM);
                auto sq3 = __builtin_ctzl(home_rank & FileDM);
                if (!((SquareM[sq1] | SquareM[sq2] | SquareM[sq3]) & this->get_pieces())){
                    if (!is_attacked(sq2) && !is_attacked(sq3) && !is_attacked(sq)){
                        move_list[move_idx++] = Move {sq, sq2, false, ' ', ' '};
                    }
                }
            }
            continue;
        }

        // Knights
        if (sqBB & this->get_knights(color_)) {
            auto moves = KnightM[sq] & ~this->get_pieces(color_);
            square_t to_sq = 0;
            while (moves != 0) {
                auto t = moves & -moves;
                to_sq = __builtin_ctzl(moves);
                char capture = this->get_piece(1ULL << to_sq, !color_);
                move_list[move_idx++] = Move {sq, to_sq, false, ' ', capture};
                moves ^= t;
            }
            continue;
        }

        // Pawns
        if (sqBB & this->get_pawns(color_)) {
            auto moves = (PawnM[color_][sq] | PawnA[color_][sq] & this->get_pieces(!color_)) & ~this->get_pieces(color_);
            square_t to_sq = 0;
            while (moves != 0) {
                bitboard_t t = moves & -moves;
                to_sq = __builtin_ctzl(moves);
                moves ^= t;

                bitboard_t to_sqBB = 1ULL << to_sq;
                if (get_enpassent() & to_sqBB) {
                    char capture = this->get_piece(Backward(to_sqBB, color_), !color_);
                    move_list[move_idx++] = Move {sq, to_sq, true, ' ', capture};
                    continue;
                }
                if (to_sqBB & (Rank1M | Rank8M)) {
                    for (char promotion : {'Q', 'N', 'R', 'B'}) {
                        char capture = this->get_piece(1ULL << to_sq, !color_);
                        move_list[move_idx++] = Move {sq, to_sq, false, promotion, capture};
                    }
                    continue;
                }
                char capture = this->get_piece(1ULL << to_sq, !color_);
                move_list[move_idx++] = Move {sq, to_sq, false, ' ', capture};
            }
        }

        // Rooks
        if (sqBB & this->get_rooks(color_)) {
            auto moves = get_rook_moves(sq, this->get_pieces()) & ~this->get_pieces(color_);
            square_t to_sq = 0;
            while (moves != 0) {
                auto t = moves & -moves;
                to_sq = __builtin_ctzl(moves);
                char capture = this->get_piece(1ULL << to_sq, !color_);
                move_list[move_idx++] = Move {sq, to_sq, false, ' ', capture};
                moves ^= t;
            }
        }

        // Bishops
        if (sqBB & this->get_bishops(color_)) {
            auto moves = get_bishop_moves(sq, this->get_pieces()) & ~this->get_pieces(color_);
            square_t to_sq = 0;
            while (moves != 0) {
                auto t = moves & -moves;
                to_sq = __builtin_ctzl(moves);
                char capture = this->get_piece(1ULL << to_sq, !color_);
                move_list[move_idx++] = Move {sq, to_sq, false, ' ', capture};
                moves ^= t;
            }
        }
    }
    return move_idx;
}