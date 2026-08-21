#ifndef ITEM_H
#define ITEM_H

struct Item {
    enum Types {
        //ex. Weapon, Potion...
        random,
        weapon,
        charm,
        armor,
        potion
    };

    Item(Item::Types type = Types::random);


    Item::Types ItemType;

    int baseDamage; //base damage of the item
    int damageModifier; //damage modifier of the item
    int maxHealthModifier; //max health modifier of the item
    int heal; //Amount of health the item heals
    int defense; //flat damage reduction of the item

    int potionDuration; //Amount of turns a potion is active after use
};
#endif