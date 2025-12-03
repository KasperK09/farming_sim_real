#pragma once

#include <vector>
#include <iostream>

#include "player.hpp"
#include "ansi_clear.hpp"
#include "inventory.hpp"
#include "bunny.hpp"


class Farm
{
private:
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<int>> growth;
    int rows;
    int columns;
    bool hasWateredToday = false;

    Bunny *bunny = nullptr;

public:
    Farm(int r = 5, int c = 7) //farm size
        : rows(r), columns(c),
          grid(r, std::vector<char>(c, '.')),
          growth(r, std::vector<int>(c, 0)) {}

    int get_rows() const
    {
        return rows;
    }
    int get_columns() const
    { 
        return columns;
    }

    const std::vector<std::vector<char>>& get_grid() const
    {
        return grid;
    }

    bool is_tilled_soil(char tile) //tiled soil symbols
    {
        return tile=='#' || tile=='%' || tile=='*' || tile=='&' || tile=='?';
    }

    bool is_sprout(char tile) //sprout symbols
    {
        return tile=='c' || tile=='l' || tile=='e' || tile=='b' || tile=='p';
    }

    bool is_mature(char tile) //mature symbols
    {
        return tile=='C' || tile=='L' || tile=='E' || tile=='B' || tile=='P';
    }

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

        std::cout << "You planted " << name << "\n";
    }

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

    int days_to_sprout(char seed)
    {
        switch (seed) {
            case '#': return 1;
            case '%': return 2;
            case '*': return 2;
            case '&': return 2;
            case '?': return 5;
        }
        return 0;
    }

    int days_to_mature(char sprout)
    {
        switch (sprout) {
            case 'c': return 1;
            case 'l': return 2;
            case 'e': return 3;
            case 'b': return 5;
            case 'p': return 10;
        }
        return 0;
    }

    char sprout_symbol(char seed)
    {
        switch (seed) {
            case '#': return 'c';
            case '%': return 'l';
            case '*': return 'e';
            case '&': return 'b';
            case '?': return 'p';
        }
        return 0;
    }

    char mature_symbol(char sprout)
    {
        switch (sprout) {
            case 'c': return 'C';
            case 'l': return 'L';
            case 'e': return 'E';
            case 'b': return 'B';
            case 'p': return 'P';
        }
        return 0;
    }

    void water_crop(const Player& player)
    {
        if (hasWateredToday) {
            //I think these messages aren't being displayed any more because of the ansi clear
            std::cout << "You already watered a plant today!\n";
            return;
        }

        int r = player.get_row();
        int c = player.get_column();

        char tile = grid[r][c];

        if (tile == '.' || is_mature(tile)) {
            std::cout << "There's nothing here to water.\n";
            return;
        }

        growth[r][c]++;

        hasWateredToday = true;

        std::cout << "You watered the plant! It grew faster.\n";
    }

    void grow_crops()
    {
        hasWateredToday = false;

        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < columns; c++)
            {
                char& tile = grid[r][c];

                if (tile == '.') continue;

                growth[r][c]++;

                if (is_tilled_soil(tile))
                {
                    if (growth[r][c] >= days_to_sprout(tile)) {
                        tile = sprout_symbol(tile);
                        growth[r][c] = 0;
                    }
                }
                else if (is_sprout(tile))
                {
                    if (growth[r][c] >= days_to_mature(tile)) {
                        tile = mature_symbol(tile);
                    }
                }
            }
        }
    }

    void harvest_crop(Player& player)
    {
        int r = player.get_row();
        int c = player.get_column();

        char& tile = grid[r][c];

        switch (tile)
    {
        case 'C':
            std::cout << "You harvested a carrot!\n";
            player.get_inventory().add_carrot();
            break;

        case 'L':
            std::cout << "You harvested lettuce!\n";
            player.get_inventory().add_lettuce();
            break;

        case 'E':
            std::cout << "You harvested spinach!\n";
            player.get_inventory().add_spinach();
            break;

        case 'B':
            std::cout << "You harvested a beet!\n";
            player.get_inventory().add_beet();
            break;

        case 'P':
            std::cout << "You harvested brussel sprouts!\n";
            player.get_inventory().add_brussels();
            break;

        default:
            std::cout << "Nothing to harvest.\n";
            return;
    }
        grid[r][c] = '.';
        growth[r][c] = 0;
    }

    void spawn_bunny(int row)
    {
        if (bunny)
        {
            return;
        }
        if (row < 0 || row >= rows)
        {
            return;
        }

        bunny = new Bunny(row, 0);
    }

    void eat_bunny(int row)
    {
        int r = bunny -> get_row();
        int c = bunny -> get_column();

        char
    }
};
