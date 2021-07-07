#include <bitset>
#include "uci.h"
#include "perft.h"
#include "move.h"

int main() {
//    return uci_loop(std::cin, std::cout);
    Masks::init();
    auto board = Board("k7/8/8/8/2pP4/8/8/7K b - d3 0 1");
    board.print();
    std::cout << perft(board, 1) << std::endl;
}
