#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "legend.hpp"
#include "farm.hpp"
#include "farm_printer.hpp"
#include "player.hpp"
#include "ansi_clear.hpp"

char getch()
{
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    char c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return c;
}

int main()
{
    Legend::show_legend();
    clear_screen();

    Farm farm(5, 7);
    Player player;
    char input;
    int steps = 0;
    int day = 1;
    bool running = true;

    while (running)
    {
        clear_screen();

        FarmPrinter::print(farm, player);

        std::cout << "=== Day " << day << " ===\n\n";

        std::cout
            << "Move (WASD)\n"
            << "Plant Carrot (C)\n"
            << "Plant Lettuce (L)\n"
            << "Plant Spinach (E)\n"
            << "Plant Beet (B)\n"
            << "Plant Brussel Sprouts (P)\n"
            << "Harvest (H)\n"
            << "Water (R)\n"
            << "Quit (Q)\n"
            << "Choose action: ";

        input = getch();

        switch (input)
        {
            case 'q': case 'Q':
            {
                running = false;

                int score = player.get_inventory().get_score();
                std::cout << "\n===== FINAL SCORE DAY " << day << " =====\n";
                std::cout << "Carrot (20 each)\n";
                std::cout << "Lettuce (40 each)\n";
                std::cout << "Spinach (50 each)\n";
                std::cout << "Beet (70 each)\n";
                std::cout << "Brussels Sprouts (150 each)\n\n";
                std::cout << "Your total score: " << score << "\n";
                std::cout << "=======================\n\n";
                std::cout << "THANKS FOR PLAYING!\n\n";

                break;
            }

            case 'c': case 'C':
                farm.plant_carrot(player);
                break;

            case 'l': case 'L':
                farm.plant_lettuce(player);
                break;

            case 'e': case 'E':
                farm.plant_spinach(player);
                break;

            case 'b': case 'B':
                farm.plant_beet(player);
                break;

            case 'p': case 'P':
                farm.plant_brussel_sprouts(player);
                break;


            case 'h': case 'H':
                farm.harvest_crop(player);
                break;


            case 'r': case 'R':
                farm.water_crop(player);
                break;


            default:
                player.move(input, farm.get_rows(), farm.get_columns());
                steps++;
                break;
        }

        if (steps >= 10)
        {
            std::cout << "\nDay " << day << " has ended!\n";

            farm.grow_crops();
            steps = 0;
            day++;

            std::cout << "Your crops have grown.\n\n";
        }
    }
}
