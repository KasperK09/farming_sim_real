#pragma once
#include <iostream>

class Legend
{
public:
    static void show_legend()
    {
        std::cout << "\nWelcome to the Farming Simulator Program!\n"
                  << "Use WASD to move\n"
                  << "Player is '@'\n"
                  << "Carrots are 'v' (seedlings)\n"
                  << "Mature Carrots are 'V' (mature)\n" 
                  //add all of the new plants here maybe change this to have line by line
                  << "Press C to plant a carrot\n"
                  << "Press H to harvest a mature carrot\n"
                  << "Day ends when you move 10 steps\n"
                  << "Press q to quit the game\n\n";
    }
};
