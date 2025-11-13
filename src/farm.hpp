#pragma once

#include <vector>
#include <iostream>

#include "player.hpp"

class Farm
{
private:
    std::vector<std::vector<char>> grid;
    int rows;
    int columns;

public:
    Farm(int r = 5, int c = 7) : rows(r), columns(c), grid(r, std::vector<char>(c, '.')) {}

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

    void plant_carrot(const Player &player)
    {
        int r = player.get_row();
        int c = player.get_column();

        if (grid[r][c] == '.')
        {
            grid[r][c] = 'v';
            std::cout << "You planted a seedling!\n";
        }
        else if (grid[r][c] == 'v')
        {
            std::cout << "There's already a seedling here!\n";
        }
        else if (grid[r][c] == 'V')
        {
            std::cout << "You can’t plant on a mature crop! Harvest it first.\n";
        }
        else
        {
            std::cout << "You can’t plant here!\n";
        }
    }

    void grow_crops()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (grid[i][j] == 'v')
                {
                    grid[i][j] = 'V';
                }
            }
        }
    }

    void harvest_crop(const Player& player)
    {
        int r = player.get_row();
        int c = player.get_column();

        if (grid[r][c] == 'V')
        {
            grid[r][c] = '.';
            std::cout << "You harvested a mature carrot!\n";
        }
        if (grid[r][c] == 'F') //redo this for all new plants
        {
            grid[r][c] = '.';
            std::cout << "You harvested a some plant carrot!\n";
        }
        else
        {
            std::cout << "There's nothing to harvest here.\n";
        }
    }
};