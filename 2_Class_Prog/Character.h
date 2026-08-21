#ifndef CHAR_H
#define CHAR_H
#include "Item.h"
#include <vector>
#include <string>



struct Character {
    Character();

    void hurt(int damageAmount); //Assessing damage amount and evaluating against item buffs
    void attack(Character &attackedCharacter); //attacks character by evaluating items held and dealing damage
    void giveItem (Item* item);

    int health;

    std::string name;

    std::vector<Item*> passives;
    std::vector<Item*> potions;
    Item* weapon;
    Item* armor;
};

#endif