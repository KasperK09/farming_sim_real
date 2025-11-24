#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/farm.hpp"
#include "../src/player.hpp"

TEST_CASE("checks to see that player starts on (0,0)") {
    Player p;
    REQUIRE(p.get_row() == 0);
    REQUIRE(p.get_column() == 0);
}

TEST_CASE("checks if player moves correctly with lowercase wasd") {
    Player p;
    int max_rows = 5;
    int max_columns = 5;

    SECTION("checks if player down move up with s") {
        p.move('s', max_rows, max_columns);
        REQUIRE(p.get_row() == 1);
        REQUIRE(p.get_column() == 0);
    }

    SECTION("checks if player can right up with d") {
        p.move('d', max_rows, max_columns);
        REQUIRE(p.get_row() == 0);
        REQUIRE(p.get_column() == 1);
    }

    SECTION("checks if player can move up with w and stays inbounds") {
        p.move('w', max_rows, max_columns);
        REQUIRE(p.get_row() == 0);
    }

    SECTION("checks if player can move left with a and stays inbounds") {
        p.move('a', max_rows, max_columns);
        REQUIRE(p.get_column() == 0);
    }
}

TEST_CASE("checks if invalid direction does not change position") {
    Player p;
    p.set_position(1, 1);
    p.move('x', 5, 5);
    REQUIRE(p.get_row() == 1);
    REQUIRE(p.get_column() == 1);
}

TEST_CASE("checks if player moves with upppercase WASD") {
    Player p;
    int max_rows = 5;
    int max_columns = 5;

    SECTION("checks if player can move down with S") {
        p.move('S', max_rows, max_columns);
        REQUIRE(p.get_row() == 1);
        REQUIRE(p.get_column() == 0);
    }

    SECTION("checks if player can right down with D") {
        p.move('D', max_rows, max_columns);
        REQUIRE(p.get_row() == 0);
        REQUIRE(p.get_column() == 1);
    }

    SECTION("checks if player can up down with W and stays within bounds") {
        p.move('W', max_rows, max_columns);
        REQUIRE(p.get_row() == 0);
    }

    SECTION("checks if player can left down with A and stays within bounds") {
        p.move('A', max_rows, max_columns);
        REQUIRE(p.get_column() == 0);
    }
}

TEST_CASE("checks if player stays within bounds in 1x1 grid") {
    Player p;
    int max_rows = 1;
    int max_columns = 1;

    p.move('w', max_rows, max_columns);
    p.move('a', max_rows, max_columns);
    p.move('s', max_rows, max_columns);
    p.move('d', max_rows, max_columns);

    REQUIRE(p.get_row() == 0);
    REQUIRE(p.get_column() == 0);
}