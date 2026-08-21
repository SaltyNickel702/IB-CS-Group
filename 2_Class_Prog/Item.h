#ifndef ITEM_H
#define ITEM_H

struct Item {
    enum Types {
        //ex. Weapon, Potion...
        weapon,
        charm,
        armor,
        potion
    };

    Item();


    Item::Types ItemType;

    int baseDamage; //base damage of the item
    int damageModifier; //damage modifier of the item
    int maxHealthModifier; //max health modifier of the item
    int heal; //Amount of health the item heals
};
#endif