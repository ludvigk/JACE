#include <bitset>
#include "uci.h"
#include "perft.h"
#include "move.h"

int main() {
//    return uci_loop(std::cin, std::cout);
    Masks::init();
    auto board = Board("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1 ");
    board.print();
    std::cout << perft(board, 3) << std::endl;
}
