#ifndef GAME_H
#define GAME_H

// Game.h
// The Game class manages the overall flow of the program, including menus,
// character creation, saving/loading, duels, and the healing mini-game.
// It serves as the controller of the entire project, coordinating interactions
// between the player, enemy characters, and gameplay systems.

#include "Character.h"
#include "Warrior.h"
#include "Wizard.h"
#include "Rogue.h"

using namespace std;

class Game {
private:
    Character* player;      // Pointer to the player's currently active character.
    bool hasPlayer;         // Does the player have a character created/loaded?

    // Safely request an integer from the user within a given range.
    // Automatically reprompts on invalid input.
    int getIntInRange(int min, int max);    

    // Displays the main menu.
    void showMainMenu();

    // Displays the in-character menu.
    void characterMenu();

    // Create a new character through user input.
    void createCharacter();

    // Load a character from a file.
    void loadCharacter();

    // Save the current character to a file.
    void saveCharacter();

    // Begin a duel between the player and a random enemy.
    void startDuel();

    // Generate a random enemy character and adjust its stats.
    Character* generateRandomEnemy();

    // Runs turn-based duel between player and enemy, handles combat choices, fleeing, healing, and combat outcomes.
    void duel(Character* player, Character* enemy);

    // Clears the console screen.
    void clearScreen();

    // Prints the game title.
    void printTitle();

    // Mini-game where the player can heal their character.
    void healingMiniGame();

public:
    Game();         // Initializes game state.
    ~Game();        // Cleans up game resources.
    void run();     // Starts the main game loop.
};

#endif
