#include <iostream>
#include "Character.h"
#include "Item.h"
#include <vector>
#include <string>

int main()
{
    Character player = Character();
    std::vector<Character> enemies;
    std::string userInput;
    bool playerTurn = true;
    int waves = 0;

    while (player.health > 0)
    {
        while (playerTurn)
        {
            std::cout << "Select Action\n1:Attack\n2:Items\n";
            std::cin >> userInput;

            if (userInput == "1")
            {
                std::cout << "Select Enemy to Attack\n";
                for (int i = 0; i < enemies.size(); i++)
                {
                    // Print list of enemies
                }
                std::cin >> userInput;
                // Attack enemy
                playerTurn = false;
                if (enemies.size() == 0)
                {
                    std::cout << "New Enemies Appear\n";
                    // Add new enemies to the vector
                    playerTurn = true;
                    waves++;

                    if (waves == 10) {
                        std::cout << "Victory!\n";
                        return 0;
                    }
                }
            }
            else if (userInput == "2")
            {
                std::cout << "Select Item to Use\n";
                for (int i = 0; i < player.potions.size(); i++)
                {
                    // Print list of items
                }
                std::cin >> userInput;
                // Use item
                playerTurn = false;
            }
            else
            {
                std::cout << "Invalid input.\n";
            }
        };

        for (int i = 0; i < enemies.size(); i++)
        {
            // Enemy turn
        }
    };

    return 0;
}