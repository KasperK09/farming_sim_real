#pragma once

#include <vector>
#include <iostream>

#include "player.hpp"
#include "ansi_clear.hpp"


class Farm
{
private:
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<int>> growth;
    int rows;
    int columns;
    bool hasWateredToday = false;

public:
    Farm(int r = 5, int c = 7)
        : rows(r), columns(c),
          grid(r, std::vector<char>(c, '.')),
          growth(r, std::vector<int>(c, 0)) {}

    int get_rows() const { return rows; }
    int get_columns() const { return columns; }
    const std::vector<std::vector<char>>& get_grid() const { return grid; }

    bool is_seed(char t)
    {
        return t=='#' || t=='%' || t=='*' || t=='&' || t=='?';
    }

    bool is_sprout(char t)
    {
        return t=='c' || t=='l' || t=='e' || t=='b' || t=='p';
    }

    bool is_mature(char t)
    {
        return t=='C' || t=='L' || t=='E' || t=='B' || t=='P';
    }

    void plant(const Player& p, char seedSymbol, const std::string& name)
    {
        int r = p.get_row();
        int c = p.get_column();

        if (grid[r][c] != '.')
        {
            std::cout << "You can't plant here.\n";
            return;
        }

        grid[r][c] = seedSymbol;
        growth[r][c] = 0;

        std::cout << "You planted " << name << "\n";
    }

    void plant_carrot(const Player& p)
    {
        plant(p, '#', "carrot");
    }

    void plant_lettuce(const Player& p) 
    {
        plant(p, '%', "lettuce");
    }

    void plant_spinach(const Player& p) 
    {
        plant(p, '*', "spinach");
    }

    void plant_beet(const Player& p) 
    {
        plant(p, '&', "beet");
    }

    void plant_brussel_sprouts(const Player& p) 
    {
        plant(p, '?', "brussel sprouts");
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
        return '?';
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
        return '?';
    }

    void water_crop(const Player& p)
    {
        if (hasWateredToday) {
            std::cout << "You already watered a plant today!\n";
            return;
        }

        int r = p.get_row();
        int c = p.get_column();

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

                if (is_seed(tile))
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

    void harvest_crop(Player& p)
    {
        int r = p.get_row();
        int c = p.get_column();

        char& tile = grid[r][c];

    switch (tile)
    {
        case 'C':
            std::cout << "You harvested a carrot!\n";
            break;

        case 'L':
            std::cout << "You harvested lettuce!\n";
            break;

        case 'E':
            std::cout << "You harvested spinach!\n";
            break;

        case 'B':
            std::cout << "You harvested a beet!\n";
            break;

        case 'P':
            std::cout << "You harvested brussel sprouts!\n";
            break;

        default:
            std::cout << "Nothing to harvest.\n";
            return;
    }


        grid[r][c] = '.';
        growth[r][c] = 0;
    }
};
