#pragma once

class Bunny
{
private:
    int row;
    int column;
    bool alive = true;

public:
    Bunny(int r, int c) : row(r), column(c) {}

    bool is_alive() const { return alive; }
    int get_row() const { return row; }
    int get_column() const { return column; }

    //move bunny left to right
    void move(int max_columns)
    {
        column++;

        //deletes the bunny when it gets to the edge of the screen
        if (column >= max_columns)
            alive = false;
    }
};
