#include <iostream>
#include <cstdlib>
#include <ctime>

#include "legend.hpp"
#include "farm_printer.hpp"
#include "farm.hpp"
#include "player.hpp"
#include "ansi_clear.hpp"

int main()
{
    Legend::show_legend();
    clear_screen();

    Farm farm(3, 3);
    Player player;
    char input = '\0';
    int steps = 0;
    int day = 1;
    bool running = true;

    while (running)
    {
        //spawn bunny & bunny eats plant if on one
        farm.start_of_day_updates(player);

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
            << "Fertilize (F)\n"
            << "Quit (Q)\n"
            << "Choose action: ";

        std::cin >> input;

        switch (input)
        {
            //quit game
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

            //planting
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

            //crop actions
            case 'h': case 'H':
                farm.harvest_crop(player);
                break;

            case 'r': case 'R':
                farm.water_crop(player);
                break;

            case 'f': case 'F':
                farm.fertilize_tile(player);
                break;

            //movement
            case 'w': case 'a': case 's': case 'd':
            case 'W': case 'A': case 'S': case 'D':
                player.move(input, farm.get_rows(), farm.get_columns());
                steps++;

                //check if bunny should be scared after movement when player stands next to bunny
                farm.update_bunny_after_player_move(player);
                break;

            default:
                std::cout << "Unknown command.\n";
                break;
        }


        //end of day after 10 moves
        if (steps >= 10)
        {
            std::cout << "\nDay " << day << " has ended!\n";

            farm.grow_crops();
            farm.move_bunny_end_of_day(player);

            steps = 0;
            day++;

            std::cout << "Your crops have grown.\n\n";
            std::cout << "Press ENTER to continue...";
            std::string tmp;
            std::getline(std::cin, tmp); // flush newline
            std::getline(std::cin, tmp);
        }
    }

    return 0;
}
