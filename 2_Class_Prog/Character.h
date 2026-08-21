#ifndef CHAR_H
#define CHAR_H
#include "Item.h"
#include <vector>
#include <string>


struct Character {
    Character(int startHealth);
    struct Effect {
        Effect (int length);

        int length; //How many turns are left
        Item potionBase; //Copies effects of potion

        ~Effect();
    };
    static std::vector<Character*> characters;
    static void updateTurn (); //Tells all active Characters that a turn has passed

    bool DEAD;

    void hurt(int damageAmount); //Assessing damage amount and evaluating against item buffs
    void attack(Character &attackedCharacter); //attacks character by evaluating items held and dealing damage
    
    void giveItem (Item* item);
    void usePotion(int index);


<<<<<<< Updated upstream
    std::string name;

    std::vector<Item*> passives;
=======
    int health();

    vector<Item*> genLoot (float fraction);

    std::vector<Item*> passives; //Are pointers because items can be dropped
>>>>>>> Stashed changes
    std::vector<Item*> potions;
    Item* weapon;
    Item* armor;
    std::vector<Effect> effects;

    ~Character();

    private:
       int baseHealth; //base health w/out effects
       int modHealth();
};

#endif