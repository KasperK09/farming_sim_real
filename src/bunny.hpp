#pragma once

struct Position {
    int row;
    int col;
};

class Bunny
{
private:
    Position pos;
    bool alive;
    bool scared;

    int max_rows;
    int max_cols;

public:
    Bunny(int r, int c, int max_r, int max_c)
        : pos{r, c}, alive(true), scared(false),
          max_rows(max_r), max_cols(max_c) {}

    int get_row() const { return pos.row; }
    int get_col() const { return pos.col; }
    bool is_alive() const { return alive; }
    bool is_scared() const { return scared; }

    void scare() { scared = true; }

    Position get_position() const { return pos; }

    void set_position(int r, int c) { pos.row = r; pos.col = c; }

    // Move 4 squares away from the player if scared
    void run_away(const Position& player)
    {
        if(!alive) return;

        int dr = (pos.row - player.row);
        int dc = (pos.col - player.col);

        // Normalize direction to -1, 0, 1
        dr = (dr>0 ? 1 : (dr<0 ? -1 : 0));
        dc = (dc>0 ? 1 : (dc<0 ? -1 : 0));

        // Move 4 steps in that direction
        pos.row += dr * 4;
        pos.col += dc * 4;

        // Check out-of-bounds
        if(pos.row < 0 || pos.col < 0 || pos.row >= max_rows || pos.col >= max_cols)
        {
            alive = false; // bunny runs away permanently
        }

        scared = false; // reset scared state after running
    }
};
