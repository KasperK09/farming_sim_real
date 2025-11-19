#pragma once
#include <iostream>

class Legend
{
public:
    static void show_legend()
    {

        //change this legend system because people don't read it and then don't know how the day ends

        //maybe make a tutorial game mode at the start so if they want to play the tutorial they can but they don't want to they can just go into the full game.

        std::cout << "\nWelcome to the Farming Simulator Program!\n"
                  << "\n*** IMPORTANT ***\n"
                  << "A DAY ENDS AFTER 10 MOVES.\n"
                  << "--------------------------\n\n"
                  << "Use WASD to move\n"
                  << "Player is '@'\n"
                  << "Carrots are 'c' (seedlings)\n"
                  << "Mature Carrots are 'C' (mature)\n\n" 

                  << "(below plants haven't been added yet)\n\n"

                  << "Lettuce are l\n"
                  << "Mature Lettuce are L\n"
                  << "Spinach are s\n"
                  << "Mature Spinach are S\n"
                  << "Beet are b\n"
                  << "Mature beet are B\n"
                  << "Brussel Sprouts are p\n"
                  << "Mature Brussel Sprouts are P\n"
                  << "Press Corresponding plant symbol to plant\n"
                  << "Press H to harvest a mature carrot\n"
                  << "Press q to quit the game\n\n";
    }
};
