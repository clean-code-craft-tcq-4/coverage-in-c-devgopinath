#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits")
{
    REQUIRE(inferBreach(19, 20, 30) == TOO_LOW);
    REQUIRE(inferBreach(31, 20, 30) == TOO_HIGH);
    REQUIRE(inferBreach(20, 20, 30) == NORMAL);
    REQUIRE(inferBreach(30, 20, 30) == NORMAL);
}

TEST_CASE("classify breach")
{
    REQUIRE(classifyBreach(PASSIVE_COOLING, -1) == TOO_LOW);
    REQUIRE(classifyBreach(MED_ACTIVE_COOLING, -1) == TOO_LOW);

    REQUIRE(classifyBreach(PASSIVE_COOLING, 0) == NORMAL);
    REQUIRE(classifyBreach(PASSIVE_COOLING, 20) == NORMAL);
    REQUIRE(classifyBreach(PASSIVE_COOLING, 35) == NORMAL);
    REQUIRE(classifyBreach(MED_ACTIVE_COOLING, 0) == NORMAL);
    REQUIRE(classifyBreach(MED_ACTIVE_COOLING, 20) == NORMAL);
    REQUIRE(classifyBreach(MED_ACTIVE_COOLING, 40) == NORMAL);

    REQUIRE(classifyBreach(PASSIVE_COOLING, 36) == TOO_HIGH);
    REQUIRE(classifyBreach(MED_ACTIVE_COOLING, 41) == TOO_HIGH);
}
