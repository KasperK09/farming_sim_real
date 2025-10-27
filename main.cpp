#include <iostream>
#include "legend.hpp"
#include "farm.hpp"
#include "farm_printer.hpp"
#include "player.hpp"

int main()
{
    Legend::show_legend();

    Farm farm(5, 7);
    Player player;
    char input;
    int steps = 0;
    int day = 1;
    bool running = true;

        while (running)
    {
        std::cout << "=== Day " << day << " ===\n";
        FarmPrinter::print(farm, player);

        std::cout << "\nMove (WASD), Plant (C), Harvest (H), or Quit (Q): ";
        std::cin >> input;

        if (input == 'q' || input == 'Q')
        {
            running = false;
        }
        else if (input == 'c' || input == 'C')
        {
            farm.plant_carrot(player);
        }
        else if (input == 'h' || input == 'H')
        {
            farm.harvest_crop(player);
        }
        else
        {
            player.move(input, farm.get_rows(), farm.get_columns());
            steps++;
        }

        if (steps >= 10)
        {
            std::cout << "\nDay " << day << " has ended!\n";
            farm.grow_crops();
            steps = 0;
            day++;
            std::cout << "Your crops have matured!\n\n";
        }

        std::cout << '\n';
    }

}