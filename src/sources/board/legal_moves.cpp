//
// Created by ludvig on 27.02.2021.
//

#include <iostream>
#include <bitset>
#include "board.h"

bool Board::is_attacked(square_t sq){
    if (get_rook_moves(sq, this->get_pieces()) & this->get_rooks(!color_)){return true;}
    if (get_bishop_moves(sq, this->get_pieces()) & this->get_bishops(!color_)){return true;}
    if (KingM[sq] & this->get_king(!color_)){return true;}
    if (PawnA[color_][sq] & this->get_pawns(!color_)){return true;}
    if (KnightM[sq] & this->get_knights(!color_)){return true;}
    return false;
}

bool Board::is_in_check(Color color){
    square_t sq = __builtin_ctzl(pieceBB_[color] & pieceBB_[nKing]);
    return is_attacked(sq);
}

int Board::pseudo_legal_moves(Move *move_list) {
    std::array<bool, 2> castle_oo;
    std::array<bool, 2> castle_ooo;
//    std::copy_n(castle_oo_, 2, castle_oo);
//    std::copy_n(castle_ooo_, 2, castle_ooo);
    castle_oo[0] = castle_oo_[0];
    castle_oo[1] = castle_oo_[1];
    castle_ooo[0] = castle_ooo_[0];
    castle_ooo[1] = castle_ooo_[1];

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
                move_list[move_idx++] = Move {sq, to_sq, false, ' ', capture, pieceBB_[nPawn], castle_oo, castle_ooo};
                moves ^= t;
            }
            if (this->can_castle_oo(color_)) {
                auto home_rank = color_ == WHITE ? Rank1M : Rank8M;
                auto sq1 = __builtin_ctzl(home_rank & FileFM);
                auto sq2 = __builtin_ctzl(home_rank & FileGM);
                if (!((SquareM[sq1] | SquareM[sq2]) & this->get_pieces())){
                    if (!is_attacked(sq) && !is_attacked(sq1) && !is_attacked(sq2)){
                        move_list[move_idx++] = Move {sq, sq2, false, ' ', ' ', pieceBB_[nPawn], castle_oo, castle_ooo};
                    }
                }
            }
            if (this->can_castle_ooo(color_)) {
                auto home_rank = color_ == WHITE ? Rank1M : Rank8M;
                auto sq1 = __builtin_ctzl(home_rank & FileBM);
                auto sq2 = __builtin_ctzl(home_rank & FileCM);
                auto sq3 = __builtin_ctzl(home_rank & FileDM);
                if (!((SquareM[sq1] | SquareM[sq2] | SquareM[sq3]) & this->get_pieces())){
                    if (!is_attacked(sq2) && !is_attacked(sq3) && !is_attacked(sq)){
                        move_list[move_idx++] = Move {sq, sq2, false, ' ', ' ', pieceBB_[nPawn], castle_oo, castle_ooo};
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
                move_list[move_idx++] = Move {sq, to_sq, false, ' ', capture, pieceBB_[nPawn], castle_oo, castle_ooo};
                moves ^= t;
            }
            continue;
        }

        // Pawns
        if (sqBB & this->get_pawns(color_)) {
            auto takes = (PawnA[color_][sq] & (this->get_pieces(!color_) | this->get_enpassent()));
            auto moves = (PawnM[color_][sq] & ~this->get_pieces()) | takes;
            square_t to_sq = 0;
            while (moves != 0) {
                bitboard_t t = moves & -moves;
                to_sq = __builtin_ctzl(moves);
                moves ^= t;

                bitboard_t to_sqBB = 1ULL << to_sq;
                if (get_enpassent() & to_sqBB) {
                    if (color_ == WHITE && get_enpassent() & Rank3M) { continue; }
                    if (color_ == BLACK && get_enpassent() & Rank6M) { continue; }
                    move_list[move_idx++] = Move {sq, to_sq, true, ' ', ' ', pieceBB_[nPawn], castle_oo, castle_ooo};
                    continue;
                }

                if ((to_sqBB & Rank4M) && (sqBB & Rank2M) && (this->get_pieces() & (to_sqBB >> 8))) { continue; }
                if ((to_sqBB & Rank5M) && (sqBB & Rank7M) && (this->get_pieces() & (to_sqBB << 8))) { continue; }
                if (to_sqBB & (Rank1M | Rank8M)) {
                    for (char promotion : {'Q', 'N', 'R', 'B'}) {
                        char capture = this->get_piece(1ULL << to_sq, !color_);
                        move_list[move_idx++] = Move{sq, to_sq, false, promotion, capture, pieceBB_[nPawn], castle_oo, castle_ooo};
                    }
                    continue;
                }
                char capture = this->get_piece(1ULL << to_sq, !color_);
                move_list[move_idx++] = Move {sq, to_sq, false, ' ', capture, pieceBB_[nPawn], castle_oo, castle_ooo};
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
                move_list[move_idx++] = Move {sq, to_sq, false, ' ', capture, pieceBB_[nPawn], castle_oo, castle_ooo};
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
                move_list[move_idx++] = Move {sq, to_sq, false, ' ', capture, pieceBB_[nPawn], castle_oo, castle_ooo};
                moves ^= t;
            }
        }
    }
    return move_idx;
}