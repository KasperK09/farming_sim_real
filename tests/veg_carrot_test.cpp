#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/farm.hpp"
#include "../src/player.hpp"

TEST_CASE("Carrot grows correctly without watering")
{
    Farm farm(1,1);
    Player p;

    farm.plant_carrot(p);
    REQUIRE(farm.get_grid()[0][0] == '#');

    farm.grow_crops();
    REQUIRE(farm.get_grid()[0][0] == 'c');

    farm.grow_crops();
    REQUIRE(farm.get_grid()[0][0] == 'C');
}
