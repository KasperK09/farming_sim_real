#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/farm_printer.hpp"
#include "../src/farm.hpp"
#include "../src/player.hpp"
#include "../src/bunny.hpp"

TEST_CASE("check if bunny initializes correctly")
{
    Bunny b(3, 4, 10, 10);

    REQUIRE(b.get_row() == 3);
    REQUIRE(b.get_col() == 4);
    REQUIRE(b.is_alive() == true);
    REQUIRE(b.is_scared() == false);
}

TEST_CASE("check if bunny scare() changes bunny to scared")
{
    Bunny b(2, 2, 10, 10);

    REQUIRE_FALSE(b.is_scared());
    b.scare();
    REQUIRE(b.is_scared());
}

TEST_CASE("check if bunny runs upward when scared and player is below")
{
    Bunny b(5, 5, 20, 20);
    b.scare();

    Position player{10, 5}; //player is below bunny

    b.run_away(player);

    // Bunny should move up by 4 rows
    REQUIRE(b.get_row() == 1);
    REQUIRE(b.get_col() == 5);
    REQUIRE_FALSE(b.is_scared());
}

TEST_CASE("check if bunny runs downward when player is above")
{
    Bunny b(5, 5, 20, 20);
    b.scare();

    Position player{0, 5}; //player is above bunny

    b.run_away(player);

    //Bunny should move down by 4
    REQUIRE(b.get_row() == 9);
    REQUIRE(b.get_col() == 5);
}

TEST_CASE("checks if bunny runs right when player is left")
{
    Bunny b(5, 5, 20, 20);
    b.scare();

    Position player{5, 0}; // player comes from the left

    b.run_away(player);

    REQUIRE(b.get_row() == 5);
    REQUIRE(b.get_col() == 9);
}

TEST_CASE("checks if bunny runs left when player is right")
{
    Bunny b(5, 5, 20, 20);
    b.scare();

    Position player{5, 10}; //player comes from the right

    b.run_away(player);

    REQUIRE(b.get_row() == 5);
    REQUIRE(b.get_col() == 1);
}

TEST_CASE("checks if bunny dies when running out of bounds")
{
    Bunny b(1, 1, 10, 10);
    b.scare();

    Position player{0, 1}; //bunny runs down
    b.run_away(player);

    REQUIRE(b.is_alive());

    b.scare();
    Position player2{10, 1}; //bunny runs up
    b.run_away(player2);

    REQUIRE(b.is_alive());
    
    //scare and run up but should go off grid
    b.scare();
    b.run_away(player2);

    REQUIRE_FALSE(b.is_alive());
}
