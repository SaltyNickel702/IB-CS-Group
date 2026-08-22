#ifndef ITEM_H
#define ITEM_H

struct Item
{
    enum Types
    {
        random,
        weapon,
        charm,
        armor,
        potion
    };

    Item(Types type = random);

    int rarityRoll();

    Types ItemType;

    int baseDamage;         // Base damage of the item
    int damageModifier;     // Damage modifier of the item
    int maxHealthModifier;  // Max health modifier of the item
    int heal;               // Amount of health the item heals
    int defense;            // Flat damage reduction of the item

    int potionDuration;     // Amount of turns a potion is active
};

#endif
