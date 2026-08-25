#ifndef CHAR_H
#define CHAR_H
#include "Item.h"
#include <vector>
#include <string>


struct Character {
    Character(int startHealth);
    
    struct Effect {
        Effect (Item potion);

        int length; //How many turns are left
        Item potionBase; //Copies effects of potion
    };
    struct LootBundle {
        LootBundle(Character &source, float proportion); // Only use on death, clears all Items from Character
        LootBundle(Character &source) : LootBundle(source,1.0) {};
        std::vector<Item*> loot;
        void GiveLoot (Character &destination, int lootIndex); //give specific loot piece
        void GiveLoot (Character &destination) { GiveLoot(destination, -1); }
        void GiveLoot (Character &destination, Item* item) {
            auto it = std::find(loot.begin(), loot.end(), item);
            if (it != loot.end()) GiveLoot(destination, it - loot.begin());
        }

        ~LootBundle();
    };

    static std::vector<Character*> characters;
    static void updateTurn (); //Tells all active Characters that a turn has passed

    bool DEAD;

    void hurt(int damageAmount); //Assessing damage amount and evaluating against item buffs
    void attack(Character &attackedCharacter); //attacks character by evaluating items held and dealing damage
    
    void giveItem (Item* item);
    void usePotion(int index);


    int health();
    std::string name;

    std::vector<Item*> passives; //Are pointers because items can be dropped
    std::vector<Item*> potions;
    Item* weapon;
    Item* armor;
    std::vector<Effect> effects;

    ~Character();

    private:
       int baseHealth; //base health w/out effects
       int healthMod();
};

#endif