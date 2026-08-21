#ifndef ITEM_H
#define ITEM_H

struct Item {
    Item();

    int baseDamage;
    int damageModifier;
    int mhealthModifier;
    int heal;

    enum Types {
        //ex. Weapon, Potion...
    };
};

#endif