#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>
#include "perft.h"

int main(int argc, char* argv[]) {
    Masks::init();
    return Catch::Session().run(argc, argv);
}

TEST_CASE("Starting position") {
    auto board = Board();
    REQUIRE(perft(board, 1) == 19);
    // REQUIRE(perft(board, 2) == 400);
    // REQUIRE(perft(board, 3) == 8902);
    //     REQUIRE(perft(board, 4) == 197281);
    REQUIRE(perft(board, 5) == 4865609);
    //    REQUIRE(perft(board, 6) == 119060324);
    // REQUIRE(perft(board, 7) == 3195901860);
}

TEST_CASE("kiwipete") {
    auto board = Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
    // REQUIRE(perft(board, 1) == 48);
    // REQUIRE(perft(board, 2) == 2039);
    //    REQUIRE(perft(board, 3) == 97862);
    REQUIRE(perft(board, 4) == 4085603);
    // REQUIRE(perft(board, 5) == 193690690);
    // REQUIRE(perft(board, 6) == 8031647685);
}

TEST_CASE("Position 3") {
    auto board = Board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
    // REQUIRE(perft(board, 1) == 14);
    // REQUIRE(perft(board, 2) == 191);
    // REQUIRE(perft(board, 3) == 2812);
    REQUIRE(perft(board, 4) == 43238);
    // REQUIRE(perft(board, 5) == 674624);
    // REQUIRE(perft(board, 6) == 11030083);
    //    REQUIRE(perft(board, 7) == 178633661);
    // REQUIRE(perft(board, 8) == 3009794393);
}

TEST_CASE("Position 4") {
    auto board = Board("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    // REQUIRE(perft(board, 1) == 6);
    // REQUIRE(perft(board, 2) == 264);
    //    REQUIRE(perft(board, 3) == 9467);
    REQUIRE(perft(board, 4) == 422333);
    // REQUIRE(perft(board, 5) == 15833292);
    // REQUIRE(perft(board, 6) == 706045033);
}

TEST_CASE("Position 4 mirrored") {
    auto board = Board("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1");
    // REQUIRE(perft(board, 1) == 6);
    // REQUIRE(perft(board, 2) == 264);
    //    REQUIRE(perft(board, 3) == 9467);
    REQUIRE(perft(board, 4) == 422333);
    // REQUIRE(perft(board, 5) == 15833292);
    // REQUIRE(perft(board, 6) == 706045033);
}

TEST_CASE("Position 5") {
    auto board = Board("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1");
    // REQUIRE(perft(board, 1) == 44);
    // REQUIRE(perft(board, 2) == 1486);
    //    REQUIRE(perft(board, 3) == 62379);
    REQUIRE(perft(board, 4) == 2103487);
    // REQUIRE(perft(board, 5) == 89941194);
}
