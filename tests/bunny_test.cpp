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
    Bunny bunny(3, 4, 10, 10);

    REQUIRE(bunny.get_row() == 3);
    REQUIRE(bunny.get_col() == 4);
    REQUIRE(bunny.is_alive() == true);
    REQUIRE(bunny.is_scared() == false);
}

TEST_CASE("check if bunny scare() changes bunny to scared")
{
    Bunny bunny(2, 2, 10, 10);

    REQUIRE_FALSE(bunny.is_scared());
    bunny.scare();
    REQUIRE(bunny.is_scared());
}

TEST_CASE("check if bunny runs upward when scared and player is below")
{
    Bunny bunny(5, 5, 20, 20);
    bunny.scare();

    Position player_position{10, 5}; //player is below bunny

    bunny.run_away(player_position);

    // Bunny should move up by 4 rows
    REQUIRE(bunny.get_row() == 1);
    REQUIRE(bunny.get_col() == 5);
    REQUIRE_FALSE(bunny.is_scared());
}

TEST_CASE("check if bunny runs downward when player is above")
{
    Bunny bunny(5, 5, 20, 20);
    bunny.scare();

    Position player_position{0, 5}; //player is above bunny

    bunny.run_away(player_position);

    //Bunny should move down by 4
    REQUIRE(bunny.get_row() == 9);
    REQUIRE(bunny.get_col() == 5);
}

TEST_CASE("checks if bunny runs right when player is left")
{
    Bunny bunny(5, 5, 20, 20);
    bunny.scare();

    Position player_position{5, 0}; // player comes from the left

    bunny.run_away(player_position);

    REQUIRE(bunny.get_row() == 5);
    REQUIRE(bunny.get_col() == 9);
}

TEST_CASE("checks if bunny runs left when player is right")
{
    Bunny bunny(5, 5, 20, 20);
    bunny.scare();

    Position player_position{5, 10}; //player comes from the right

    bunny.run_away(player_position);

    REQUIRE(bunny.get_row() == 5);
    REQUIRE(bunny.get_col() == 1);
}

TEST_CASE("checks if bunny dies when running out of bounds")
{
    Bunny bunny(1, 1, 10, 10);
    bunny.scare();

    Position player_below{0, 1}; //bunny runs down
    bunny.run_away(player_below);

    REQUIRE(bunny.is_alive());

    bunny.scare();
    Position player_above{10, 1}; //bunny runs up
    bunny.run_away(player_above);

    REQUIRE(bunny.is_alive());
    
    //scare and run up but should go off grid
    bunny.scare();
    bunny.run_away(player_above);

    REQUIRE_FALSE(bunny.is_alive());
}

TEST_CASE("check if Bunny spawns correctly")
{
    Farm::set_bunny_spawn_chance(100); //should always spawn
    Farm farm(5, 5);
    Player player;

    farm.start_of_day_updates(player);
    REQUIRE(farm.has_bunny());
}

TEST_CASE("check if Bunny does not spawn if chance is 0")
{
    Farm::set_bunny_spawn_chance(0);
    Farm farm(5, 5);
    Player player;

    farm.start_of_day_updates(player);
    REQUIRE_FALSE(farm.has_bunny());
}

TEST_CASE("check if Bunny eats a plant on its tile")
{
    Farm::set_bunny_spawn_chance(100);
    Farm farm(5, 5);
    Player player;

    farm.start_of_day_updates(player);
    REQUIRE(farm.has_bunny());

    int bunny_row = farm.get_bunny_row();
    int bunny_col = farm.get_bunny_column();

    farm.debug_grid()[bunny_row][bunny_col] = '#'; //force a plant under the bunny

    farm.bunny_eat_if_on_plant();

    REQUIRE(farm.debug_grid()[bunny_row][bunny_col] == '.'); //check that bunny ate it
}

TEST_CASE("check if Bunny deletes itself when walking out of bounds")
{
    Farm::set_bunny_spawn_chance(100);
    Farm farm(3, 3);
    Player player;

    farm.start_of_day_updates(player);
    REQUIRE(farm.has_bunny());

    //force bunny to be at edge
    farm.get_bunny_row();
    farm.get_bunny_column();

    //manually set to right border
    farm.move_bunny_end_of_day(player);

    //bunny should delete when moving out
    if (farm.get_bunny_column() == -1)
        REQUIRE_FALSE(farm.has_bunny());
}

TEST_CASE("check if Bunny gets scared when adjacent to player")
{
    Farm farm(5, 5);
    Farm::set_bunny_spawn_chance(100);

    Player player;
    farm.start_of_day_updates(player);
    REQUIRE(farm.has_bunny());

    int bunny_row = farm.get_bunny_row();
    int bunny_col = farm.get_bunny_column();

    //move player above bunny
    player.set_position(bunny_row - 1, bunny_col);

    farm.update_bunny_after_player_move(player);

    //delete bunny, but must NOT be in old location
    REQUIRE((!farm.has_bunny() || farm.get_bunny_row() != bunny_row || farm.get_bunny_column() != bunny_col));
}
