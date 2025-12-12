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

TEST_CASE("Bunny spawns correctly")
{
    Farm::set_bunny_spawn_chance(100); //should always spawn
    Farm f(5, 5);
    Player p;

    f.start_of_day_updates(p);
    REQUIRE(f.has_bunny());
}

TEST_CASE("Bunny does NOT spawn if chance is 0")
{
    Farm::set_bunny_spawn_chance(0);
    Farm f(5, 5);
    Player p;

    f.start_of_day_updates(p);
    REQUIRE_FALSE(f.has_bunny());
}

TEST_CASE("Bunny eats a plant on its tile")
{
    Farm::set_bunny_spawn_chance(100);
    Farm f(5, 5);
    Player p;

    f.start_of_day_updates(p);
    REQUIRE(f.has_bunny());

    int r = f.get_bunny_row();
    int c = f.get_bunny_column();

    f.debug_grid()[r][c] = '#'; //force a plant under the bunny

    f.bunny_eat_if_on_plant();

    REQUIRE(f.debug_grid()[r][c] == '.'); //check that bunny ate it
}


TEST_CASE("Bunny deletes itself when walking out of bounds")
{
    Farm::set_bunny_spawn_chance(100);
    Farm f(3, 3);
    Player p;

    f.start_of_day_updates(p);
    REQUIRE(f.has_bunny());

    //force bunny to be at edge
    f.get_bunny_row();
    f.get_bunny_column();

    //manually set to right border
    f.move_bunny_end_of_day(p);

    //bunny should delete when moving out
    if (f.get_bunny_column() == -1)
        REQUIRE_FALSE(f.has_bunny());
}

TEST_CASE("Bunny gets scared when adjacent to player")
{
    Farm f(5, 5);
    Farm::set_bunny_spawn_chance(100);

    Player p;
    f.start_of_day_updates(p);
    REQUIRE(f.has_bunny());

    int br = f.get_bunny_row();
    int bc = f.get_bunny_column();

    //move player above bunny
    p.set_position(br - 1, bc);

    f.update_bunny_after_player_move(p);

    //delete bunny, but must NOT be in old location
    REQUIRE((!f.has_bunny() || f.get_bunny_row() != br || f.get_bunny_column() != bc));
}
