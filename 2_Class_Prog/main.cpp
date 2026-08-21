#include <iostream>
#include "Character.h"
#include "Item.h"
#include <vector>
#include <string>

int main()
{
    return 0;

    Character player = Character();
    std::vector<Character> enemies;
    std::string userInput;
    bool playerTurn = true;

    while (player.health > 0)
    {
        while (playerTurn)
        {
            std::cout << "Select Action\n1:Attack\n2:Items\n";
            std::cin >> userInput;
            try
            {
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
                    throw std::invalid_argument("Invalid Input");
                }
            }
            catch (const std::invalid_argument &e)
            {
                
            };
        };
        for (int i = 0; i < enemies.size(); i++)
        {
            // Enemy turn
        }
    };
}