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

TEST_CASE("checks if player moves correctly within bounds") {
    Player p;
    int max_rows = 5;
    int max_columns = 5;

    SECTION("Move down 's' increases row") {
        p.move('s', max_rows, max_columns);
        REQUIRE(p.get_row() == 1);
        REQUIRE(p.get_column() == 0);
    }

    SECTION("Move right 'd' increases column") {
        p.move('d', max_rows, max_columns);
        REQUIRE(p.get_row() == 0);
        REQUIRE(p.get_column() == 1);
    }

    SECTION("Move up 'w' decreases row but stays >= 0") {
        p.move('w', max_rows, max_columns);
        REQUIRE(p.get_row() == 0);
    }

    SECTION("Move left 'a' decreases column but stays >= 0") {
        p.move('a', max_rows, max_columns);
        REQUIRE(p.get_column() == 0);
    }
}

TEST_CASE("checks to see if player stays within grid bounds") {
    Player p;
    int max_rows = 3;
    int max_columns = 3;

    p.set_position(0, 0);
    p.move('w', max_rows, max_columns);
    REQUIRE(p.get_row() == 0);

    p.move('a', max_rows, max_columns);
    REQUIRE(p.get_column() == 0);

    p.set_position(2, 2);
    p.move('s', max_rows, max_columns);
    REQUIRE(p.get_row() == 2);

    p.move('d', max_rows, max_columns);
    REQUIRE(p.get_column() == 2);
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

    SECTION("Move down 'S' increases row") {
        p.move('S', max_rows, max_columns);
        REQUIRE(p.get_row() == 1);
        REQUIRE(p.get_column() == 0);
    }

    SECTION("Move right 'D' increases column") {
        p.move('D', max_rows, max_columns);
        REQUIRE(p.get_row() == 0);
        REQUIRE(p.get_column() == 1);
    }

    SECTION("Move up 'W' decreases row but stays >= 0") {
        p.move('W', max_rows, max_columns);
        REQUIRE(p.get_row() == 0);
    }

    SECTION("Move left 'A' decreases column but stays >= 0") {
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