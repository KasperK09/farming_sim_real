#pragma once

#include "inventory.hpp"

class Player
{
private:
    int row;
    int column;
    Inventory inventory;

public:
    Player() : row(0), column(0) {}

    Inventory& get_inventory()
    {
        return inventory;
    }

    const Inventory& get_inventory() const
    {
        return inventory;
    }

    int get_row() const
    {
        return row;
    }

    int get_column() const
    {
        return column;
    }


    void set_position(int new_row, int new_column)
    {
        row = new_row;
        column = new_column;
    }

    void move(char direction, int max_rows, int max_columns)
    {
        switch (direction)
        {
        case 'w': case 'W':
            row--;
            break;
        case 's': case 'S':
            row++;
            break;
        case 'a': case 'A':
            column--;
            break;
        case 'd': case 'D':
            column++;
            break;
        default:
            return;
        }

        //keep player inbounds
        if (row < 0)
        {
            row = 0;
        }

        if (column < 0)
        {
            column = 0;
        }

        if (row >= max_rows)
        {
            row = max_rows - 1;
        }

        if (column >= max_columns)
        {
            column = max_columns - 1;
        }
    }
};
