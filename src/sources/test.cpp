#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>
#include "perft.h"

int main(int argc, char* argv[]) {
    Masks::init();
    return Catch::Session().run(argc, argv);
}

TEST_CASE("Starting position") {
    auto board = Board();
    REQUIRE(perft(board, 1) == 20);
    REQUIRE(perft(board, 2) == 400);
    REQUIRE(perft(board, 3) == 8902);
    // REQUIRE(perft(board, 4) == 197281);
    // REQUIRE(perft(board, 5) == 4865609);
    // REQUIRE(perft(board, 6) == 119060324);
    // REQUIRE(perft(board, 7) == 3195901860);
}

TEST_CASE("kiwipete") {
    auto board = Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
    REQUIRE(perft(board, 1) == 48);
    // REQUIRE(perft(board, 2) == 2039);
    // REQUIRE(perft(board, 3) == 97862);
    // REQUIRE(perft(board, 4) == 4085603);
    // REQUIRE(perft(board, 5) == 193690690);
    // REQUIRE(perft(board, 6) == 8031647685);
}
