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
        std::cout << "You will plant crops, water them, and harvest them.\n\n";
        std::cout << "Press ENTER to continue...";
        std::getline(std::cin, pause);

        std::cout << "\n*** IMPORTANT GAME RULES ***\n"
                  << "• A DAY ENDS AFTER 10 MOVES.\n"
                  << "• Crops grow +1 stage per day.\n"
                  << "• You may water ONE plant per day for +1 extra growth.\n\n";
        std::cout << "Press ENTER to continue...";
        std::getline(std::cin, pause);

        std::cout << "\n=== CONTROLS ===\n"
                  << "Move: W A S D\n"
                  << "Plant Carrot: C\n"
                  << "Plant Lettuce: L\n"
                  << "Plant Spinach: E\n"
                  << "Plant Beet: B\n"
                  << "Plant Brussel Sprouts: P\n"
                  << "Harvest Mature Crops: H\n"
                  << "Water a Plant: R\n"
                  << "Quit Game: Q\n\n"
                  << "Player character is: '@'\n\n";
        std::cout << "Press ENTER to continue...";
        std::getline(std::cin, pause);

        std::cout << "\n=== PLANT GROWTH ===\n"
                  << "Seeds use unique tilled-soil symbols:\n"
                  << "Carrot: '#' → 'c' → 'C'\n"
                  << "Lettuce: '%' → 'l' → 'L'\n"
                  << "Spinach: '*' → 'e' → 'E'\n"
                  << "Beet: '&' → 'b' → 'B'\n"
                  << "Brussel Sprouts: '?' → 'p' → 'P'\n\n"

                  << "Days to sprout:\n"
                  << "• Carrot = 1\n"
                  << "• Lettuce = 2\n"
                  << "• Spinach = 2\n"
                  << "• Beet = 2\n"
                  << "• Brussel Sprouts = 5\n\n"

                  << "Days from sprout to mature:\n"
                  << "• Carrot = 1\n"
                  << "• Lettuce = 2\n"
                  << "• Spinach = 3\n"
                  << "• Beet = 5\n"
                  << "• Brussel Sprouts = 10\n\n";
        std::cout << "Press ENTER to continue...";
        std::getline(std::cin, pause);

        std::cout << "\n=== WATERING ===\n"
                  << "• You may water ONE plant per day.\n"
                  << "• Watering instantly gives +1 growth.\n"
                  << "• You must stand on the plant to water it.\n\n";
        std::cout << "Press ENTER to continue...";
        std::getline(std::cin, pause);

        std::cout << "\n=== FINAL NOTES ===\n"
                  << "'.' = empty land\n"
                  << "Manage your moves, watering, and planting to grow crops efficiently!\n\n";
        std::cout << "Press ENTER to start the game...";
        std::getline(std::cin, pause);
    }
};
