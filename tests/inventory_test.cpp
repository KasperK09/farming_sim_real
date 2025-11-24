#include <catch2/catch_test_macros.hpp>
#include "../src/farm.hpp"
#include "../src/player.hpp"
#include "../src/inventory.hpp"

TEST_CASE("Inventory starts at zero for all vegetables")
{
    Inventory inventory;

    REQUIRE(inventory.get_carrots()  == 0);
    REQUIRE(inventory.get_lettuce()  == 0);
    REQUIRE(inventory.get_spinach()  == 0);
    REQUIRE(inventory.get_beets()    == 0);
    REQUIRE(inventory.get_brussels() == 0);
}

TEST_CASE("Harvesting a carrot increases carrot count")
{
    Farm farm(1, 1);
    Player p;

    farm.plant_carrot(p);

    farm.grow_crops(); //sprout

    farm.grow_crops(); //mature

    REQUIRE(farm.get_grid()[0][0] == 'C');

    farm.harvest_crop(p);

    REQUIRE(p.get_inventory().get_carrots() == 1);
}

TEST_CASE("Harvesting lettuce increases lettuce count")
{
    Farm farm(1, 1);
    Player p;

    farm.plant_lettuce(p);

    farm.grow_crops();
    farm.grow_crops();

    farm.grow_crops();
    farm.grow_crops();

    farm.harvest_crop(p);

    REQUIRE(p.get_inventory().get_lettuce() == 1);
}

TEST_CASE("Harvesting spinach increases spinach count")
{
    Farm farm(1, 1);
    Player p;

    farm.plant_spinach(p);

    farm.grow_crops();
    farm.grow_crops();

    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops();

    REQUIRE(farm.get_grid()[0][0] == 'E');

    farm.harvest_crop(p);

    REQUIRE(p.get_inventory().get_spinach() == 1);
}

TEST_CASE("Harvesting beet increases beet count")
{
    Farm farm(1, 1);
    Player p;

    farm.plant_beet(p);

    farm.grow_crops();
    farm.grow_crops();

    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops();

    REQUIRE(farm.get_grid()[0][0] == 'B');

    farm.harvest_crop(p);

    REQUIRE(p.get_inventory().get_beets() == 1);
}

TEST_CASE("Harvesting brussel sprouts increases brussels count")
{
    Farm farm(1, 1);
    Player p;

    farm.plant_brussel_sprouts(p);

    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops(); //sprout
    farm.grow_crops();
    farm.grow_crops();

    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops(); //mature
    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops();
    farm.grow_crops();

    REQUIRE(farm.get_grid()[0][0] == 'P');

    farm.harvest_crop(p);

    REQUIRE(p.get_inventory().get_brussels() == 1);
}
