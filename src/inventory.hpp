#pragma once
#include <iostream>

class Inventory {
private:
    int carrots = 0;
    int lettuce = 0;
    int spinach = 0;
    int beets = 0;
    int brussels = 0;

public:
    int get_carrots() const { return carrots; }
    int get_lettuce() const { return lettuce; }
    int get_spinach() const { return spinach; }
    int get_beets() const { return beets; }
    int get_brussels() const { return brussels; }

    void add_carrot() { carrots++; }
    void add_lettuce() { lettuce++; }
    void add_spinach() { spinach++; }
    void add_beet() { beets++; }
    void add_brussels() { brussels++; }

    int get_score() const {
        return carrots * 20
             + lettuce * 40
             + spinach * 50
             + beets   * 70
             + brussels * 150;
    }

    void print() const {
        std::cout << "\n== INVENTORY ===\n"
                  << "Carrots: " << carrots << " "
                  << "Lettuce: " << lettuce << "\n"
                  << "Spinach: " << spinach << " "
                  << "Beets: " << beets << "\n"
                  << "Brussel Sprouts: " << brussels << "\n\n";
    }
};
