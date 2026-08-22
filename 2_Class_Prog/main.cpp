#include <iostream>
#include "Character.h"
#include "Item.h"
#include <vector>
#include <string>
#include <cmath>

void getUserInput(int lowerBound, int upperBound, std::string &userInput)
{
    while (true)
    {
        std::cin >> userInput;
        try
        {
            int input = std::stoi(userInput);
            if (input >= lowerBound && input <= upperBound)
            {
                break;
            }
            else
            {
                std::cout << "Invalid input. Please enter a number between " << lowerBound << " and " << upperBound << ".\n";
            }
        }
        catch (std::invalid_argument &e)
        {
            std::cout << "Invalid input. Please enter a number between " << lowerBound << " and " << upperBound << ".\n";
        }
    }
}

void generateEnemies(std::vector<Character> &enemies, int numberOfEnemies)
{
    for (int i = 0; i < numberOfEnemies; i++)
    {
        Character enemy(30);
        enemy.name = "Enemy " + std::to_string(i + 1);
        Item *weapon = new Item(Item::Types::weapon);
        weapon->baseDamage = 10;
        enemy.weapon = weapon;
        enemies.push_back(enemy);
    }
}

int main()
{
    Character player = Character(100);
    player.name = "Player";
    player.weapon = new Item(Item::Types::weapon);
    player.weapon->baseDamage = 15;
    std::vector<Character> enemies;
    std::string userInput;
    bool playerTurn = true;
    int waves = 0;

    generateEnemies(enemies, 1);
    std::cout << "Welcome to the Battle Game!\nSurvive 10 waves of enemies to win.\n";

    while (player.health() > 0)
    {
        std::cout << enemies.size() << " enemies remain.\n";
        while (playerTurn)
        {
            std::cout << "Select Action\n1:Attack\n2:Items\n";
            getUserInput(1, 2, userInput);

            if (userInput == "1")
            {
                std::cout << "Select Enemy to Attack\n";
                for (int i = 0; i < enemies.size(); i++)
                {
                    // Print list of enemies
                    std::cout << i + 1 << ": " << enemies[i].name << " (Health: " << enemies[i].health() << ")\n";
                }
                getUserInput(1, enemies.size(), userInput);
                // Attack enemy
                player.attack(enemies[std::stoi(userInput) - 1]);
                if (enemies[std::stoi(userInput) - 1].health() <= 0)
                {
                    std::cout << "Enemy " << enemies[std::stoi(userInput) - 1].name << " has been defeated!\n";
                    enemies.erase(enemies.begin() + std::stoi(userInput) - 1);
                }
                else
                {
                    std::cout << "Enemy " << enemies[std::stoi(userInput) - 1].name << " has " << enemies[std::stoi(userInput) - 1].health() << " health remaining.\n";
                }

                playerTurn = false;
                if (enemies.size() == 0)
                {
                    std::cout << "New Enemies Appear\n";
                    // Add new enemies to the vector
                    generateEnemies(enemies, floor(waves / 3) + 1);
                    playerTurn = true;
                    waves++;

                    if (waves == 10)
                    {
                        std::cout << "Victory!\n";
                        return 0;
                    }
                }
            }
            else if (userInput == "2")
            {
                if (player.potions.size() == 0)
                {
                    std::cout << "No items available.\n";
                }
                else
                {
                    std::cout << "Select Item to Use\n";
                    for (int i = 0; i < player.potions.size(); i++)
                    {
                        // Print list of items
                        std::cout << i + 1 << ": Health Potion: " << player.potions[i]->heal << " HP\n";
                    }
                    getUserInput(1, player.potions.size(), userInput);
                    // Use item
                    playerTurn = false;
                    player.usePotion(std::stoi(userInput) - 1);
                    std::cout << "Player has " << player.health() << " health remaining.\n";
                    player.potions.erase(player.potions.begin() + std::stoi(userInput) - 1);
                }
            }
            else
            {
                std::cout << "Invalid input.\n";
            }
        };

        for (int i = 0; i < enemies.size(); i++)
        {
            // Enemy turn
            enemies[i].attack(player);
            std::cout << "Enemy " << enemies[i].name << " attacked player for " << enemies[i].weapon->baseDamage << " damage.\n";
            std::cout << "Player has " << player.health() << " health remaining.\n";
        }
        playerTurn = true;
    };

    return 0;
}