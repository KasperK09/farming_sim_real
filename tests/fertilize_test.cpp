#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/farm.hpp"
#include "../src/player.hpp"

TEST_CASE("check if fertilizing empty tile does nothing")
{
    Farm farm(5, 5);
    Player player;

    player.set_position(2, 2); //on empty tile
    REQUIRE(farm.get_grid()[2][2] == '.');

    farm.fertilize_tile(player);

    //still empty fertilizer level unchanged
    REQUIRE(farm.get_grid()[2][2] == '.');
}

TEST_CASE("check if first fertilizer increases fertilizer level")
{
    Farm farm(5, 5);
    Player player;

    //plant something
    farm.debug_grid()[2][2] = '#';

    player.set_position(2, 2);
    farm.fertilize_tile(player);

    //fertilizer level should now be 1
    REQUIRE(farm.debug_fertilizer()[2][2] == 1);
    REQUIRE(farm.get_grid()[2][2] == '#');
}

TEST_CASE("check if second fertilizer does not kill plant")
{
    Farm farm(5, 5);
    Player player;

    farm.debug_grid()[2][2] = '#';

    player.set_position(2, 2);
    farm.fertilize_tile(player);  //fertilizer = 1
    farm.fertilize_tile(player);  //fertilizer = 2

    REQUIRE(farm.debug_fertilizer()[2][2] == 2);
    REQUIRE(farm.get_grid()[2][2] == '#');
}

TEST_CASE("check if third fertilizer kills plant and resets tile")
{
    Farm farm(5, 5);
    Player player;

    farm.debug_grid()[2][2] = '#';

    player.set_position(2, 2);
    farm.fertilize_tile(player);  //fertilizer = 1
    farm.fertilize_tile(player);  //fertilizer = 2
    farm.fertilize_tile(player);  //fertilizer = 3 so dead

    REQUIRE(farm.get_grid()[2][2] == '.'); //plant removed
    REQUIRE(farm.debug_fertilizer()[2][2] == 0); //fertilizer reset
    REQUIRE(farm.debug_growth()[2][2] == 0); //growth reset
}

TEST_CASE("check if fertilizing any plant type works the same")
{
    Farm farm(5, 5);
    Player player;

    //test each plantable seed
    char seeds[] = { '#', '%', '*', '&', '?' };

    for (char seed : seeds)
    {
        farm.debug_grid()[1][1] = seed;
        farm.debug_fertilizer()[1][1] = 0;
        player.set_position(1, 1);

        farm.fertilize_tile(player);
        REQUIRE(farm.debug_fertilizer()[1][1] == 1);

        //reset for next seed
        farm.debug_grid()[1][1] = '.';
        farm.debug_fertilizer()[1][1] = 0;
    }
}
