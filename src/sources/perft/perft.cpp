//
// Created by ludvig on 7/3/21.
//

#include "perft.h"
#include <iostream>

int perft(Board &board, int ply) {
    Move moves[256];
    int nodes = 0 ;
    if (ply == 0) { return 1; }
    int num_moves = board.pseudo_legal_moves(moves);
    for (int mv = 0; mv < num_moves; mv++) {
        bool legal = board.make_move(moves[mv]);
        if (legal) {
            nodes += perft(board, ply - 1);
            std::cout << "From: " << moves[mv].from_ << " to: " << moves[mv].to_ << std::endl;
//            board.print();
        }
        board.unmake_move(moves[mv]);
    }
    return nodes;
}
