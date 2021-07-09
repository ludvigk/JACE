#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>
#include "move.h"

int main(int argc, char* argv[]) {
    Masks::init();
    return Catch::Session().run(argc, argv);
}
