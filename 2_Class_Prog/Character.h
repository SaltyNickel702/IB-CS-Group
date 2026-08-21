#ifndef CHAR_H
#define CHAR_H
#include "Item.h"
#include <vector>

struct Character {
    Character();

    void hurt();
    void attack();

    std::vector<Item> items;
};

#endif