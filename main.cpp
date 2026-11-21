// main.cpp
// Entry point of the "For Glory" RPG Battle Project.
// This file simply creates a Game object and begins the main menu loop.
// All gameplay logic, character management, battles, and file I/O are
// handled inside the Game class.

#include "Game.h"

using namespace std;

int main() {
    // Create the game controller object
    Game game;

    // Run the main game loop
    game.run();
    
    return 0;
}
