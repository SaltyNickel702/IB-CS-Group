#ifndef CHAR_H
#define CHAR_H
#include "Item.h"
#include <vector>



struct Character {
    Character();

    void hurt(int damageAmount); //Assessing damage amount and evaluating against item buffs
    void attack(Character &attackedCharacter); //attacks character by evaluating items held and dealing damage

    int health;

    std::vector<Item> passives;
    std::vector<Item> consumables;
    Item weapon;
};

#endif