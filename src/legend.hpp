#pragma once
#include <iostream>
#include <string>
#include "ansi_clear.hpp"

class Legend
{
public:
    static void show_legend()
    {
        std::string pause;

        std::cout << "\n===== FARMING SIMULATOR =====\n\n";
        std::cout << "Welcome to your farm!\n";
        std::cout << "You will plant crops, water them, fertalize them, protect them, and harvest them.\n\n";
        std::cout << "Press ENTER to continue...";
        std::getline(std::cin, pause);

        std::cout << "\n=== CONTROLS ===\n"
                  << "Move: W A S D\n"
                  << "Player performs action on tile they are directly on top of\n"
                  << "Plant Carrot: C\n"
                  << "Plant Lettuce: L\n"
                  << "Plant Spinach: E\n"
                  << "Plant Beet: B\n"
                  << "Plant Brussel Sprouts: P\n"
                  << "Harvest Mature Crops: H\n"
                  << "Water a Plant: R\n"
                  << "Fertilize a Plant: F\n"
                  << "Quit Game: Q\n\n"
                  << "Player character is: '@'\n"
                  << "Bunny character is: 'R'\n\n";
        std::cout << "Press ENTER to continue...";
        std::getline(std::cin, pause);

        std::cout << "\n=== WATERING ===\n"
                  << "You may water a plant once per day.\n"
                  << "Watering gives +1 growth.\n"
                  << "You must stand on the plant to water it.\n"
                  << "When the day ends the plant will be +2 to growth\n";
        std::cout << "Press ENTER to continue...";
        std::getline(std::cin, pause);

        std::cout << "\n=== FERTILIZING ===\n"
                  << "You may fertilize a plant once per turn.\n"
                  << "Fertilizer builds up on a plant. Fertilizer levels:\n"
                  << "  0 = no fertilizer\n"
                  << "  1 = lightly fertilized\n"
                  << "  2 = heavily fertilized\n"
                  << "If a plant is fertilized a THIRD time, it dies and resets to '.'\n"
                  << "Fertilizing has NO effect on empty tiles.\n\n";
        std::cout << "Press ENTER to continue...";
        std::getline(std::cin, pause);

        std::cout << "\n=== PLANT GROWTH ===\n"
                  << "Plants grow from tilled soil (seeds) to sprouts and mature:\n"
                  << "ONLY MATURE PLANTS CAN BE HARVESTED\n"
                  << "Carrot: '#' -> 'c' -> 'C'\n"
                  << "Lettuce: '%' -> 'l' -> 'L'\n"
                  << "Spinach: '*' -> 'e' -> 'E'\n"
                  << "Beet: '&' -> 'b' -> 'B'\n"
                  << "Brussel Sprouts: '?' -> 'p' -> 'P'\n\n"

                  << "Days to sprout:\n"
                  << "Carrot = 1\n"
                  << "Lettuce = 2\n"
                  << "Spinach = 2\n"
                  << "Beet = 2\n"
                  << "Brussel Sprouts = 5\n\n"

                  << "Days from sprout to mature:\n"
                  << "Carrot = 1\n"
                  << "Lettuce = 2\n"
                  << "Spinach = 3\n"
                  << "Beet = 5\n"
                  << "Brussel Sprouts = 10\n\n";
        std::cout << "Press ENTER to continue...";
        std::getline(std::cin, pause);

        std::cout << "\n*** IMPORTANT GAME RULES ***\n"
                  << "A DAY ENDS AFTER 10 MOVES.\n"
                  << "Crops add +1 to their counter per day.\n"
                  << "You may water a plant once per day for +1 extra growth.\n"
                  << "This means watered plants gain +2 at end of day.\n";
        std::cout << "Press ENTER to continue...";
        std::getline(std::cin, pause);

        std::cout << "\n*** GAME SCORING ***\n"
                  << "When you quit the game it tells you your score.\n"
                  << "\n===== FINAL SCORE =====\n"
                  << "Carrot (20 each)\n"
                  << "Lettuce (40 each)\n"
                  << "Spinach (50 each)\n"
                  << "Beet (70 each)\n"
                  << "Brussels Sprouts (150 each)\n\n";
        std::cout << "Press ENTER to continue...";
        std::getline(std::cin, pause);

        std::cout << "\n*** BUNNY ***\n"
                  << "At the start of each day, there is a chance a bunny will appear.\n"
                  << "The bunny always spawns on an top left tile.\n\n"
                  << "If the player moves into any of the 4 tiles directly around the bunny\n"
                  << "(up, down, left, right), the bunny becomes SCARED!.\n\n"
                  << "At the END of the day, a scared bunny runs in a straight line 4 tiles\n"
                  << "away from the player.\n"
                  << "If it runs off the edge of the map, it disappears.\n"
                  << "Bunnies can also eat seeds, sprouts, and mature plants if they stand on them.\n\n";
        std::cout << "Press ENTER to continue...";
        std::getline(std::cin, pause);

        std::cout << "\n=== FINAL NOTES ===\n"
                  << "'.' = farm land\n"
                  << "Manage your moves, watering, fertilizing, and planting to grow crops efficiently!\n"
                  << "HAVE FUN!!!!\n"
                  << "is anyone still reading?\n\n";
        std::cout << "Press ENTER to start the game...";
        std::getline(std::cin, pause);
    }
};
