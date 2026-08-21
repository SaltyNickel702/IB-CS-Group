#include "Character.h"
#include <algorithm>
using namespace std;

Character::Character (int sHealth) : weapon(nullptr), armor(nullptr), baseHealth(sHealth), DEAD(false) {
    characters.push_back(this);
};
Character::~Character () {
    auto i = find(characters.begin(), characters.end(), this);
    if (i != characters.end()) {
        characters.erase(i);
    }
}

int Character::health () {return baseHealth + modHealth();};
int Character::modHealth () {
    int hp = 0;
    for (Effect e : effects) {
        hp+= e.potionBase.maxHealthModifier;
    }
}

void Character::attack (Character &c) {
    int dmg = weapon ? weapon->baseDamage : 1;
    
    for (Item* i : passives) dmg+= i->damageModifier;
    for (Effect e : effects) dmg+= e.potionBase.damageModifier;

    c.hurt(dmg);
};
void Character::hurt (int dmg) {
    int defence = armor ? armor->maxHealthModifier : 0;
    dmg = max(dmg - defence,0);
    baseHealth -= dmg;
    if (health() <= 0) DEAD = true;
};