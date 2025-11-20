#pragma once
#include <iostream>

inline void clear_screen() {
    std::cout << "\033[2J\033[1;1H";
}
