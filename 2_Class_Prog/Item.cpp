#include "Item.h"
#include <cstdlib>

Item::Item(Types t)
{
    ItemType = t;


    baseDamage = 0;
    damageModifier = 0;
    maxHealthModifier = 0;
    heal = 0;
    defense = 0;
    potionDuration = 0;

    // Nico wanted to be able to call items with the 'random' ask, so if you do that.
    // It'll roll the dice here to get a random different type.
    if (ItemType == random)
    {
        ItemType = static_cast<Types>(rand() % 4 + 1);
    }

    // I thought that there should be a tiered rarity for potent stat changes getting progressively rarer.
    // Theres rarities for each item type.
    switch (ItemType)
    {
    case weapon:
    {
        int rarity = rarityRoll();

        switch (rarity)
        {
        case 1:
            baseDamage = 1;
            break;

        case 2:
            baseDamage = 2;
            break;

        case 3:
            baseDamage = 3;
            break;

        case 4:
            baseDamage = 4;
            break;
        }

        break;
    }

    case armor:
    {
        int rarity = rarityRoll();

        switch (rarity)
        {
        case 1:
            defense = 1;
            break;

        case 2:
            defense = 2;
            break;

        case 3:
            defense = 3;
            break;

        case 4:
            defense = 4;
            break;
        }

        break;
    }

    case charm:
    {
        // Can increase max hp or damage modifier. Emil said to do this i think
        if (rand() % 2 == 0)
        {
            int rarity = rarityRoll();

            switch (rarity)
            {
            case 1:
                maxHealthModifier = 5;
                break;

            case 2:
                maxHealthModifier = 10;
                break;

            case 3:
                maxHealthModifier = 15;
                break;

            case 4:
                maxHealthModifier = 25;
                break;
            }
        }
        else
        {
            int rarity = rarityRoll();

            switch (rarity)
            {
            case 1:
                damageModifier = 1;
                break;

            case 2:
                damageModifier = 2;
                break;

            case 3:
                damageModifier = 3;
                break;

            case 4:
                damageModifier = 5;
                break;
            }
        }

        break;
    }


        // I didn't mess around with potion duration as i wasn't sure what to do with that.
        // Its still established in this class though, so you can edit it in if you'd like
    case potion:
    {
        int rarity = rarityRoll();

        switch (rarity)
        {
        case 1:
            heal = 10;
            break;

        case 2:
            heal = 20;
            break;

        case 3:
            heal = 30;
            break;

        case 4:
            heal = 50;
            break;
        }

        break;
    }

    default:
        break;
    }
}


// This rolls for rarity, each is progressively rarer
int Item::rarityRoll()
{
    int roll = rand() % 100 + 1;

    if (roll <= 60)
        return 1;
    else if (roll <= 85)
        return 2;
    else if (roll <= 95)
        return 3;
    else
        return 4;
}
