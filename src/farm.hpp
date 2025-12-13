#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <utility>

#include "player.hpp"
#include "inventory.hpp"
#include "bunny.hpp"

class Farm
{
private:
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<int>> growth;
    std::vector<std::vector<int>> fertilizer;
    int rows;
    int columns;
    bool hasWateredToday = false;

    Bunny* bunny = nullptr;
    static int bunny_spawn_chance_percent;

public:

    //for fertilize_test.cpp
    std::vector<std::vector<int>>& debug_fertilizer() { return fertilizer; }
    std::vector<std::vector<int>>& debug_growth() { return growth; }

    Farm(int r = 5, int c = 7)
        : rows(r), columns(c),
          grid(r, std::vector<char>(c, '.')),
          growth(r, std::vector<int>(c, 0)),
          fertilizer(r, std::vector<int>(c, 0))
    {
        //set random seed so bunny spawn can be random
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    ~Farm()
    {
        if (bunny)
        {
            delete bunny;
            bunny = nullptr;
        }
    }

    //size of farm
    int get_rows() const
    {
        return rows;
    }

    int get_columns() const
    {
        return columns;
    }

    //farm tiles
    const std::vector<std::vector<char>>& get_grid() const
    {
        return grid;
    }

    //for bunny tests
    std::vector<std::vector<char>>& debug_grid()
    {
        return grid;
    }

    const std::vector<std::vector<char>>& debug_grid() const
    {
        return grid;
    }


    //for bunny
    bool has_bunny() const
    {
        return bunny && bunny->is_alive();
    }

    int get_bunny_row() const
    {
        return has_bunny() ? bunny->get_row() : -1;
    }

    int get_bunny_column() const
    {
        return has_bunny() ? bunny->get_col() : -1;
    }

    //checks if tile has something on it
    bool is_tilled_soil(char tile)
    {
        return tile == '#' || tile == '%' || tile == '*' || tile == '&' || tile == '?';
    }

    bool is_sprout(char tile)
    {
        return tile == 'c' || tile == 'l' || tile == 'e' || tile == 'b' || tile == 'p';
    }

    bool is_mature(char tile)
    {
        return tile == 'C' || tile == 'L' || tile == 'E' || tile == 'B' || tile == 'P';
    }


    //checks if tile is empty if not lets u plant
    void plant(const Player& player, char seed_symbol, const std::string& name)
    {
        int r = player.get_row();
        int c = player.get_column();
        if (grid[r][c] != '.')
        {
            std::cout << "You can't plant here.\n";
            return;
        }

        grid[r][c] = seed_symbol;
        growth[r][c] = 0;
        fertilizer[r][c] = 0;
        std::cout << "You planted " << name << "\n";
    }

    //plant seeds 
    void plant_carrot(const Player& player)
    {
        plant(player, '#', "carrot");
    }

    void plant_lettuce(const Player& player)
    {
        plant(player, '%', "lettuce");
    }

    void plant_spinach(const Player& player)
    {
        plant(player, '*', "spinach");
    }

    void plant_beet(const Player& player)
    {
        plant(player, '&', "beet");
    }

    void plant_brussel_sprouts(const Player& player)
    {
        plant(player, '?', "brussel sprouts");
    }


    void water_crop(const Player& player)
    {
        if (hasWateredToday){ 
            std::cout << "You already watered a plant today!\n"; return;
        }

        int r = player.get_row();
        int c = player.get_column();
        char tile = grid[r][c];

        if (tile == '.' || is_mature(tile))
        { 
            std::cout << "There's nothing here to water.\n"; return; 
        }

        growth[r][c]++;
        hasWateredToday = true;
        std::cout << "You watered the plant! It grew faster.\n";
    }

    //can fertilize any age of plant
    void fertilize_tile(const Player& player)
    {
        int r = player.get_row();
        int c = player.get_column();

        if (grid[r][c] == '.')
        { 
            std::cout << "Nothing to fertilize.\n"; return;
        }

        fertilizer[r][c]++;
        if (fertilizer[r][c] >= 3)
        {
            std::cout << "Over-fertilized! Plant died.\n";
            grid[r][c] = '.';
            growth[r][c] = 0;
            fertilizer[r][c] = 0;
        }
        else if (fertilizer[r][c] == 2) 
        {
            std::cout << "Second fertilizer applied (no extra effect).\n"; 
        }
        else 
        { 
            std::cout << "Fertilized! +1 yield.\n";
        }
    }

    void grow_crops()
    {
        hasWateredToday = false;
        for(int r=0;r<rows;r++)
        {
            for(int c=0;c<columns;c++)
            {
                char& tile = grid[r][c];
                if (tile == '.') continue;

                growth[r][c]++;
                if (is_tilled_soil(tile))
                {
                    if (growth[r][c] >= days_to_sprout(tile))
                    {
                        tile = sprout_symbol(tile);
                        growth[r][c] = 0;
                    }
                }
                else if (is_sprout(tile))
                {
                    if (growth[r][c] >= days_to_mature(tile))
                        tile = mature_symbol(tile);
                }
            }
        }
    }

    void harvest_crop(Player& player)
    {
        int r = player.get_row();
        int c = player.get_column();
        char tile = grid[r][c];
        int yield = (fertilizer[r][c]>=1) ? 2 : 1;

        switch (tile)
        {
        case 'C':
            for (int i = 0; i < yield; i++)
            {
                player.get_inventory().add_carrot();
            }
            std::cout << "You harvested " << yield << " carrot(s)!\n";
            break;

        case 'L':
            for (int i = 0; i < yield; i++)
            {
                player.get_inventory().add_lettuce();
            }
            std::cout << "You harvested " << yield << " lettuce!\n";
            break;

        case 'E':
            for (int i = 0; i < yield; i++)
            {
                player.get_inventory().add_spinach();
            }
            std::cout << "You harvested " << yield << " spinach!\n";
            break;

        case 'B':
            for (int i = 0; i < yield; i++)
            {
                player.get_inventory().add_beet();
            }
            std::cout << "You harvested " << yield << " beet(s)!\n";
            break;

        case 'P':
            for (int i = 0; i < yield; i++)
            {
                player.get_inventory().add_brussels();
            }
            std::cout << "You harvested " << yield << " brussel sprout(s)!\n";
            break;

        default:
            std::cout << "Nothing to harvest.\n";
            return;
        }
        grid[r][c] = '.';
        growth[r][c] = 0;
        fertilizer[r][c] = 0;
    }

    void maybe_spawn_bunny(const Player& player)
    {
        if (has_bunny()) return;
        int roll = std::rand()%100;
        if (roll < bunny_spawn_chance_percent)
            bunny = new Bunny(0, 0, rows, columns); //spawn top left everytime
    }

    void bunny_eat_if_on_plant()
    {
        if (!has_bunny()) return;
        int r = bunny->get_row();
        int c = bunny->get_col();
        if(grid[r][c]!='.')
        {
            grid[r][c]='.';
            growth[r][c]=0;
            fertilizer[r][c]=0;
            std::cout<<"A bunny ate your plant at ("<<r<<","<<c<<")!\n";
        }
    }

    void update_bunny_after_player_move(const Player& player)
    {
        if(!has_bunny()) return;

        int br = bunny->get_row();
        int bc = bunny->get_col();
        int pr = player.get_row();
        int pc = player.get_column();

        //check if player is adjacent
        bool adjacent = (abs(pr - br) == 1 && pc == bc) || (abs(pc - bc) == 1 && pr == br);

        if(adjacent && !bunny->is_scared())
        {
            //mark as scared
            bunny -> scare();
            std::cout << "The bunny got scared and ran away!\n";

            //immediately runs away from player
            Position player_pos{pr, pc};
            bunny -> run_away(player_pos);

            //delete bunny if it ran off map
            if(!bunny->is_alive())
            {
                delete bunny;
                bunny = nullptr;
            }
        }
    }


    void move_bunny_end_of_day(const Player& player)
    {
        if(!has_bunny()) return;

        if(bunny->is_scared())
        {
            Position player_pos{player.get_row(), player.get_column()};
            bunny -> run_away(player_pos);

            //Delete bunny if it runs off the map
            if(!bunny -> is_alive())
            {
                delete bunny;
                bunny = nullptr;

                //try spawning a new bunny
                maybe_spawn_bunny(player);
            }
        }
        else
        {
            //move right
            Position p = bunny -> get_position();
            int new_r = p.row;
            int new_c = p.col + 1;

            //bunny out of bounds delete
            if(new_c >= columns)
            {
                delete bunny;
                bunny = nullptr;

                //try to spawn new bunny
                maybe_spawn_bunny(player);
            }
            else
            {
                bunny->set_position(new_r, new_c);
            }
        }
    }
    
    void start_of_day_updates(const Player& player)
    {
        maybe_spawn_bunny(player);
        bunny_eat_if_on_plant();
    }

    static void set_bunny_spawn_chance(int percent)
    {
        bunny_spawn_chance_percent = std::max(0, std::min(100, percent));
    }

    //data for how long it takes to sprout
    int days_to_sprout(char seed)
    {
        switch (seed)
        {
            case '#': 
                return 1;
            case '%': 
                return 2;
            case '*': 
                return 2;
            case '&': 
                return 2;
            case '?': 
                return 5;
            default:  
                return 0;
        }
    }

    //data for how long it takes to mature
    int days_to_mature(char sprout)
    {
        switch (sprout)
        {
            case 'c': 
                return 1;
            case 'l': 
                return 2;
            case 'e': 
                return 3;
            case 'b': 
                return 5;
            case 'p': 
                return 10;
            default:  
                return 0;
        }
    }

    char sprout_symbol(char seed)
    {
        switch (seed)
        {
            case '#': 
                return 'c';
            case '%': 
                return 'l';
            case '*': 
                return 'e';
            case '&': 
                return 'b';
            case '?': 
                return 'p';
            default:  
                return 0;
        }
    }

    char mature_symbol(char sprout)
    {
        switch (sprout)
        {
            case 'c': 
                return 'C';
            case 'l': 
                return 'L';
            case 'e': 
                return 'E';
            case 'b': 
                return 'B';
            case 'p': 
                return 'P';
            default:  
                return 0;
        }
    }
};
