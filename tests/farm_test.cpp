#include <catch2/catch_test_macros.hpp>
#include "../src/farm.hpp"
#include "../src/player.hpp"

TEST_CASE("Player movement stays inside farm grid")
{
    Farm farm(5, 7);
    Player p;

    p.set_position(0, 0);

    p.move('w', farm.get_rows(), farm.get_columns());
    REQUIRE(p.get_row() == 0);

    p.move('a', farm.get_rows(), farm.get_columns());
    REQUIRE(p.get_column() == 0);

    p.set_position(4, 6); 

    p.move('s', farm.get_rows(), farm.get_columns());
    REQUIRE(p.get_row() == 4);

    p.move('d', farm.get_rows(), farm.get_columns());
    REQUIRE(p.get_column() == 6);
}

TEST_CASE("Planting places tilled soil in grid for carrot")
{
    Farm farm(3, 3);
    Player p;
    p.set_position(1, 1);

    farm.plant_carrot(p);
    REQUIRE(farm.get_grid()[1][1] == '#');
}

TEST_CASE("Planting places tilled soil in grid for lettuce")
{
    Farm farm(3, 3);
    Player p;
    p.set_position(1, 1);

    farm.plant_lettuce(p);
    REQUIRE(farm.get_grid()[1][1] == '%');
}

TEST_CASE("Planting places tilled soil in grid for spinach")
{
    Farm farm(3, 3);
    Player p;
    p.set_position(1, 1);

    farm.plant_spinach(p);
    REQUIRE(farm.get_grid()[1][1] == '*');
}

TEST_CASE("Planting places tilled soil in grid for beet")
{
    Farm farm(3, 3);
    Player p;
    p.set_position(1, 1);

    farm.plant_beet(p);
    REQUIRE(farm.get_grid()[1][1] == '&');
}

TEST_CASE("Planting places tilled soil in grid for brussel sprouts")
{
    Farm farm(3, 3);
    Player p;
    p.set_position(1, 1);

    farm.plant_brussel_sprouts(p);
    REQUIRE(farm.get_grid()[1][1] == '?');
}
