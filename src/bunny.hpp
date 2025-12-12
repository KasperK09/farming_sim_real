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
    Bunny(int r, int c, int max_r, int max_c) : pos{r, c}, alive(true), scared(false), max_rows(max_r), max_cols(max_c) {}

    int get_row() const 
    { 
        return pos.row; 
    }
    int get_col() const 
    { 
        return pos.col; 
    }
    bool is_alive() const 
    {
        return alive; 
    }
    bool is_scared() const 
    {
         return scared; 
    }
    void scare() 
    { 
        scared = true; 
    }

    Position get_position() const 
    {
        return pos; 
    }

    void set_position(int r, int c) 
    { 
        pos.row = r; pos.col = c; 
    }

    //move 4 tiles away from the player when scared
    void run_away(const Position& player)
    {
        if (!alive) 
        {    
            return;
        }

        //run down
        if (player.row < pos.row)
        {
            pos.row += 4;   
        }

        //run up  
        else if (player.row > pos.row)
        {
            pos.row -= 4; 
        }    

        //run right
        else if (player.col < pos.col)
        {
            pos.col += 4;  
        }
        
        //run left  
        else
        {
            pos.col -= 4;
        }

        if (pos.row < 0 || pos.col < 0 || pos.row >= max_rows || pos.col >= max_cols)
        {
            alive = false;
        }

        scared = false;
    }
};
