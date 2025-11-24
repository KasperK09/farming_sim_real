#include <catch2/catch_test_macros.hpp>
#include "../src/farm.hpp"
#include "../src/player.hpp"

//cannot check carrot because it always grows in one day
//checks if plants can be watered everyday too

TEST_CASE("check if watering works for lettuce")
{
    Farm farm(3, 3);
    Player p;

    farm.plant_lettuce(p);

    farm.grow_crops();
    farm.grow_crops();

    farm.water_crop(p);

    farm.grow_crops();

    REQUIRE(farm.get_grid()[0][0] == 'L');
}

TEST_CASE("check if watering works for spinach")
{
    Farm farm(3, 3);
    Player p;

    farm.plant_spinach(p);

    farm.grow_crops();
    farm.grow_crops();

    farm.water_crop(p);

    farm.grow_crops();
    farm.grow_crops();

    REQUIRE(farm.get_grid()[0][0] == 'E');
}

TEST_CASE("check if watering works for beet")
{
    Farm farm(3, 3);
    Player p;

    farm.plant_beet(p);

    farm.grow_crops();
    farm.grow_crops();

    farm.water_crop(p);
    farm.grow_crops(); //+2

    farm.water_crop(p);
    farm.grow_crops(); //+2

    farm.grow_crops();

    REQUIRE(farm.get_grid()[0][0] == 'B');
}

TEST_CASE("check if watering works for Brussel Sprouts")
{
    Farm farm(3, 3);
    Player p;

    farm.plant_brussel_sprouts(p);

    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops();

    farm.water_crop(p);
    farm.grow_crops(); //+2

    farm.water_crop(p);
    farm.grow_crops(); //+2

    farm.water_crop(p);
    farm.grow_crops();

    farm.water_crop(p);
    farm.grow_crops();

    farm.water_crop(p);
    farm.grow_crops(); //should be +10 total

    REQUIRE(farm.get_grid()[0][0] == 'P');
}