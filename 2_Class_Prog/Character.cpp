#include "Character.h"
#include <algorithm>
#include <format>
#include <random>
#include <cmath>

using namespace std;

Character::Effect::Effect (Item p) {
    potionBase = p;
    length = potionBase.potionDuration;
}

Character::LootBundle::LootBundle (Character &c, float proportion) {
    vector<Item*> al; //All loot
    if (c.weapon) al.push_back(c.weapon);
    if (c.armor) al.push_back(c.armor);
    for (Item *i : c.passives) al.push_back(i);
    for (Item *i : c.potions) al.push_back(i);

    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(al.begin(), al.end(), g);
    
    int deleteToIndex = round((al.size()-1)*(1-proportion));
    for (int i = 0; i <= deleteToIndex; i++) {
        delete al.at(i);
    }
    al.erase(al.begin(), al.begin() + deleteToIndex + 1);
    loot = al;

    //Delete loot on donor character
    c.weapon = nullptr;
    c.armor = nullptr;
    c.passives.clear();
    c.potions.clear();
}
void Character::LootBundle::GiveLoot(Character &c, int lI) {
    if (lI == -1) {
        while (loot.size() > 0) {
            c.giveItem(loot.at(0));
            loot.erase(loot.begin());
        }
    } else {
        c.giveItem(loot.at(lI));
        loot.erase(loot.begin() + lI + 1);
    }
}
Character::LootBundle::~LootBundle () {
    for (Item* i : loot) delete i;
}

vector<Character*> Character::characters;
Character::Character (int sHealth) : weapon(nullptr), armor(nullptr), baseHealth(sHealth), DEAD(false) {
    characters.push_back(this);
    name = "Char-" + to_string(characters.size()-1); //Default name, can be overriden
};
Character::~Character () {
    auto i = find(characters.begin(), characters.end(), this);
    if (i != characters.end()) {
        characters.erase(i);
    }
}
void Character::updateTurn () {
    for (Character *c : characters) {
        vector<Effect*> toDel;
        for (int i = 0; i < c->effects.size(); i++) {
            Effect &e = c->effects[i];
            e.length--;
            if (e.length < 0) {
                c->effects.erase(c->effects.begin() + i);
                i--;
            }
        }
    }
}

int Character::health () {return baseHealth + healthMod();};
int Character::healthMod () {
    int hp = 0;
    for (Effect e : effects) {
        hp+= e.potionBase.maxHealthModifier;
    }
    for (Item* p : passives) {
        hp+= p->maxHealthModifier;
    }
    return hp;
}

void Character::attack (Character &c) {
    int dmg = weapon ? weapon->baseDamage : 1;
    
    for (Item* i : passives) dmg+= i->damageModifier;
    for (Effect e : effects) dmg+= e.potionBase.damageModifier;

    c.hurt(dmg);
};
void Character::hurt (int dmg) {
    int defence = armor ? armor->defense : 0;
    dmg = max(dmg - defence,0);
    baseHealth -= dmg;
    if (health() <= 0) DEAD = true;
};

void Character::giveItem (Item* i) {
    switch (i->ItemType) {
        case Item::Types::armor:
            if (!armor) {
                armor = i;
            } else {
                // Only pick up armor if its defense is strictly greater
                if (i->defense > armor->defense) {
                    delete armor;
                    armor = i;
                } else {
                    // Not better: discard incoming item
                    delete i;
                }
            }
            break;
        case Item::Types::charm:
            passives.push_back(i);
            break;
        case Item::Types::weapon:
            if (!weapon) {
                weapon = i;
            } else {
                // Only pick up weapon if its base damage is strictly greater
                if (i->baseDamage > weapon->baseDamage) {
                    delete weapon;
                    weapon = i;
                } else {
                    // Not better: discard incoming item
                    delete i;
                }
            }
            break;
        case Item::Types::potion:
            potions.push_back(i);
            break;
        case Item::Types::random:
            break;
    }
}
void Character::usePotion (int i) {
    if (i < 0 || i >= potions.size()) {
        return;
    }

    Item* p = potions.at(i);
    baseHealth += p->heal;

    Effect e = Effect(*p);
    effects.push_back(e);

    potions.erase(potions.begin() + i);
    delete p;
}

