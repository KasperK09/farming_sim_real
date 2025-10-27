#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/farm_printer.hpp"
#include "../src/farm.hpp"
#include "../src/player.hpp"

TEST_CASE("farm printer runs with correct dimensions, ensure parameters are valid before printing, Prints to console for visual confirmation")
{
    int rows = 2;
    int cols = 3;

    REQUIRE(rows > 0);
    REQUIRE(cols > 0);

    FarmPrinter::print_static(rows, cols);
}

TEST_CASE("farm printer prints with player at (0,0), verify initial logical state before print, prints to console")
{
    Farm farm(2, 3);
    Player player;

    REQUIRE(farm.get_rows() == 2);
    REQUIRE(farm.get_columns() == 3);
    REQUIRE(player.get_row() == 0);
    REQUIRE(player.get_column() == 0);

    FarmPrinter::print(farm, player);
}

TEST_CASE("farm printer prints player at correct postion, prints to console for visual check")
{
    Farm farm(3, 3);
    Player player;
    player.set_position(1, 2);

    REQUIRE(player.get_row() == 1);
    REQUIRE(player.get_column() == 2);

    FarmPrinter::print(farm, player);
}