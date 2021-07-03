#include "uci.h"
#include "perft.h"
#include "move.h"

int main() {
//    return uci_loop(std::cin, std::cout);
    Masks::init();
    auto board = Board();
    std::cout << perft(board, 3) << std::endl;
}
