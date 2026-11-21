// Game.cpp
// Implements the Game class, which controls interactions like main menu navigation,
// character creation, saving, loading, duels, healing mini-games, enemy generation 
// and combat flow.
// This file connects all other classes together and serves as the controller
// of the entire program.

#include "Game.h"
#include <iostream>
#include <random>
#include <limits>
#include <fstream>

using namespace std;

// Constructor.
Game::Game() : player(nullptr), hasPlayer(false) {}

// Destructor.
Game::~Game() {
    delete player;
}

// Clear the console screen.
void Game::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Print the game title.
void Game::printTitle() {
    cout <<  " _____   ___   ____        ____  _       ___   ____   __ __ " << endl;    
    cout <<  "|     | /   \\ |    \\      /    || |     /   \\ |    \\ |  |  |" << endl;
    cout <<  "|   __||     ||  D  )    |   __|| |    |     ||  D  )|  |  |" << endl;
    cout <<  "|  |_  |  O  ||    /     |  |  || |___ |  O  ||    / |  ~  |" << endl;
    cout <<  "|   _] |     ||    \\     |  |_ ||     ||     ||    \\ |___, |" << endl;
    cout <<  "|  |   |     ||  .  \\    |     ||     ||     ||  .  \\|     |" << endl;
    cout <<  "|__|    \\___/ |__|\\_|    |___,_||_____| \\___/ |__|\\_||____/ " << endl;

    cout << "========================================================================" << endl;
                                                                
}

// Safely request an integer from the user within a given range.
int Game::getIntInRange(int min, int max) {
    int choice;
    while (true) {
        cout << "Enter choice (" << min << "-" << max << "): ";
        if (cin >> choice && choice >= min && choice <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Display the main menu.
void Game::showMainMenu() {
    clearScreen();        
    printTitle();         

    cout << "1) Create new character\n";
    cout << "2) Load character\n";
    cout << "3) Exit\n";
}

// Display the in-character menu after create/load.
void Game::characterMenu() {
    if (!hasPlayer || player == nullptr) {
        cout << "No character loaded.\n";
        return;
    }

    bool exitMenu = false;
    while (!exitMenu) {
        clearScreen();

        cout << "===== CHARACTER MENU: " << player->getName() << " =====\n";
        player->printStatus();
        cout << "===============================================\n";

        cout << "1) Start Duel\n";
        cout << "2) Save Character\n";
        cout << "3) Return to Main Menu\n";
        cout << "4) Healing Mini-Game\n";

        int choice = getIntInRange(1, 4);
        if (choice == 1) {
            startDuel();
        } else if (choice == 2) {
            saveCharacter();
        } else if (choice == 3) {
            exitMenu = true;
        } else if (choice == 4) {
            healingMiniGame();
        }
    }
}

// Create a new character through user input.
void Game::createCharacter() {
    delete player;
    player = nullptr;

    cout << "\nChoose Class:\n";
    cout << "1) Warrior\n";
    cout << "2) Wizard\n";
    cout << "3) Rogue\n";

    int choice = getIntInRange(1, 3);

    cout << "Enter character name: ";
    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    if (choice == 1) player = new Warrior(name);
    else if (choice == 2) player = new Wizard(name);
    else player = new Rogue(name);

    hasPlayer = true;
    cout << "\nCharacter created!\n";
    player->printStatus();
    characterMenu();
}

// Load a character from a file.
void Game::loadCharacter() {
    delete player;
    player = nullptr;

    cout << "Enter filename to load (e.g., hero.txt): ";
    string filename;
    getline(cin, filename);   

    if (filename.empty()) {
        cout << "No filename entered.\n";
        cout << "Press Enter to return to the main menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    ifstream in(filename);
    if (!in) {
        cout << "Could not open file: " << filename << "\n";
        cout << "Press Enter to return to the main menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    string type;
    getline(in, type);

    if (type == "Warrior") {
        player = new Warrior();
    } else if (type == "Wizard") {
        player = new Wizard();
    } else if (type == "Rogue") {
        player = new Rogue();
    } else {
        cout << "Unknown class type in file: " << type << "\n";
        cout << "Press Enter to return to the main menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        in.close();
        return;
    }

    player->setClassType(type);
    player->loadFromFile(in);
    in.close();

    hasPlayer = true;
    cout << "Character loaded successfully:\n";
    player->printStatus();

    cout << "\nPress Enter to go to the character menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    characterMenu();
}

// Save the current character to a file.
void Game::saveCharacter() {
    if (!hasPlayer) {
        cout << "No character to save.\n";
        return;
    }

    cout << "Enter filename to save: ";
    string filename;
    getline(cin, filename);

    ofstream out(filename);
    if (!out) {
        cout << "Failed to open file.\n";
        return;
    }

    out << player->getClassType() << "\n";
    player->saveToFile(out);
    out.close();

    cout << "Character saved.\n";
}

// Generate a random enemy character and adjust its stats.
Character* Game::generateRandomEnemy() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 3);

    int type = dist(gen);
    Character* enemy = nullptr;

    if (type == 1) enemy = new Warrior("Enemy Warrior");
    else if (type == 2) enemy = new Wizard("Enemy Wizard");
    else enemy = new Rogue("Enemy Rogue");

    enemy->applyEnemyDifficultyModifier();

    return enemy;
}

// Sets up and begins combat between player and enemy.
void Game::startDuel() {
    if (!hasPlayer || player == nullptr) {
        cout << "No player character available.\n";
        return;
    }
    Character* enemy = generateRandomEnemy();

    clearScreen();   

    cout << "==================================================\n";
    cout << "                 BATTLE START!                    \n";
    cout << "==================================================\n\n";

    cout << "Your Hero:\n";
    player->printStatus();
    cout << "\nEnemy:\n";
    enemy->printStatus();

    duel(player, enemy);
    delete enemy;
}

// Runs the combat loop including player/enemy turns, healing, fleeing, victory/defeat.
void Game::duel(Character* player, Character* enemy) {
    bool fleeing = false;
    bool usedHeal = false; 
    bool enemyUsedHeal = false; 

    // Player turn
    while (player->alive() && enemy->alive() && !fleeing) {
        cout << "\n===== Your Turn =====\n";
        player->printStatus();
        cout << "\nEnemy:\n";
        enemy->printStatus();

        cout << "\n--- Choose Your Action ---\n";
        cout << "1) Basic Attack\n";
        cout << "2) Defend\n";
        cout << "3) Special Action\n";
        cout << "4) Heal\n";       
        cout << "5) Flee\n";        

        int choice = getIntInRange(1,5);
        if (choice == 1) player->basicAttack(*enemy);
        else if (choice == 2) player->defend();
        else if (choice == 3) player->specialAction(*enemy);
        else if (choice == 4) { 
            if (usedHeal) {
                cout << "You have already used your heal this duel!\n";
            } else {
                int healAmount = player->getMaxHealth() / 5; 
                cout << player->getName() << " uses Heal and recovers "
                     << healAmount << " HP!\n";
                player->heal(healAmount);
                usedHeal = true;
            }
        }
        else if (choice == 5) { 
            fleeing = true;
        }


        if (!enemy->alive()) break;
        if (fleeing) break;  

        // Enemy turn
        cout << "\n===== Enemy Turn =====\n";

        int lowHealthThreshold = enemy->getMaxHealth() * 40 / 100; 
        if (!enemyUsedHeal && enemy->getCurrentHealth() <= lowHealthThreshold) {
            int healAmount = enemy->getMaxHealth() / 5; 
            cout << enemy->getName() << " uses Heal and recovers "
                 << healAmount << " HP!\n";
            enemy->heal(healAmount);
            enemyUsedHeal = true;
        }
        else {
            static random_device rd;
            static mt19937 gen(rd());
            uniform_int_distribution<> dist(1, 3);
            int move = dist(gen);

            if (move == 1) enemy->basicAttack(*player);
            else if (move == 2) enemy->defend();
            else enemy->specialAction(*player);
        }
    }

    // After battle
    if (!player->alive()) {
        cout << "\n============== YOU WERE DEFEATED ==============\n";
    } else if (!enemy->alive()) {
        cout << "\n================== VICTORY! ===================\n";
        player->addXP(100);
    } else if (fleeing) {
        cout << "\n================= YOU FLED ====================\n";
    }

    player->updateAfterCombat();
    enemy->updateAfterCombat();

    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Mini-game where the player can heal their character.
void Game::healingMiniGame() {
    if (!hasPlayer || player == nullptr) {
        cout << "No character to heal.\n";
        return;
    }

    clearScreen();
    cout << "========== HEALING MINI-GAME ==========\n";
    cout << "Guess the lucky number between 1 and 5!\n";
    cout << "If you guess correctly, you heal a lot and recover your\n";
    cout << "special resource (stamina / mana / energy).\n";
    cout << "If not, you still heal and recover a bit.\n\n";

    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 5);

    int secret = dist(gen);

    cout << "Enter your guess (1-5): ";
    int guess = getIntInRange(1, 5);

    bool success = (guess == secret);

    int healAmountSmall = player->getMaxHealth() / 10;  // 10% HP
    int healAmountBig   = player->getMaxHealth() / 4;   // 25% HP

    if (success) {
        cout << "\nCorrect! You feel rejuvenated!\n";
        player->heal(healAmountBig);
    } else {
        cout << "\nNot quite! The lucky number was " << secret << ".\n";
        cout << "You still recover a bit of strength.\n";
        player->heal(healAmountSmall);
    }

    // Restore class-specific resource.
    if (Warrior* w = dynamic_cast<Warrior*>(player)) {
        if (success) {
            w->restoreStamina(20);   
        } else {
            w->restoreStamina(10);   
        }
    }
    else if (Wizard* wz = dynamic_cast<Wizard*>(player)) {
        if (success) {
            wz->restoreMana(20);     
        } else {
            wz->restoreMana(10);     
        }
    }
    else if (Rogue* r = dynamic_cast<Rogue*>(player)) {
        if (success) {
            r->restoreEnergy(20);    
        } else {
            r->restoreEnergy(10);    
        }
    }

    cout << "\nPress Enter to return to the character menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Runs the program until player exits.
void Game::run() {
    bool running = true;
    while (running) {
        showMainMenu();
        int choice = getIntInRange(1, 3);
        if (choice == 1) createCharacter();
        else if (choice == 2) loadCharacter();
        else {
            cout << "Goodbye!\n";
            running = false;
        }
    }
}
