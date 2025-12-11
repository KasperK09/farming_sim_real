#include "farm_printer.hpp"
#include "ansi_clear.hpp"
#include <iostream>

void FarmPrinter::print_static(int rows, int columns)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            std::cout << ". ";
        }
        std::cout << '\n';
    }
}

void FarmPrinter::print(const Farm &farm, const Player &player)
{
    clear_screen();

    int rows = farm.get_rows();
    int columns = farm.get_columns();
    const auto& grid = farm.get_grid();

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            // Player has display priority
            if (i == player.get_row() && j == player.get_column())
            {
                std::cout << "@ ";
                continue;
            }

            // Bunny overlays grid but does NOT modify grid
            if (farm.has_bunny() && farm.get_bunny_row() == i && farm.get_bunny_column() == j)
            {
                std::cout << "R ";
                continue;
            }

            std::cout << grid[i][j] << ' ';
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    player.get_inventory().print();
}
