#pragma once

#include "farm.hpp"
#include "player.hpp"

class FarmPrinter
{
public:
    static void print_static(int rows = 5, int columns = 7);
    static void print(const Farm& farm, const Player& player);
};