#include <iostream>
#include "Character.h"
#include "Item.h"
#include <vector>
#include <string>

int main () {
    return 0;

    Character player = Character();
    std::vector<Character> enemies;
    std::string userInput;

    while (player.health > 0) {
        std::cout << "Select Action\n1:Attack\n2:Items\n";
        std::cin >> userInput;

        
    };
}