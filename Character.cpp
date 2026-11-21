// Character.cpp
// Implements the base Character class used by all playable characters and enemies.
// This file defines core gameplay behavior such as taking damage, healing,
// leveling up, and saving/loading shared character data.

#include "Character.h"
#include <algorithm>
#include <limits>

using namespace std;

// Default constructor: creates a level 1 "Unknown" character with base stats.
Character::Character()
    : name("Unknown"), classType("Character"), level(1), xp(0),
      maxHealth(100), currentHealth(100), baseAttack(10),
      baseDefense(5), isAlive(true), defending(false) {}

// Constructor: initializes character with given name and class type.
Character::Character(const string& name, const string& classType)
    : name(name), classType(classType), level(1), xp(0),
      maxHealth(100), currentHealth(100), baseAttack(10),
      baseDefense(5), isAlive(true), defending(false) {}

// Apply damage to this character, considering defense and defending status. If HP drops to 0, character dies.
void Character::takeDamage(int amount) {
    int damage = amount - baseDefense;
    if (defending) damage /= 2;
    if (damage < 0) damage = 0;

    currentHealth -= damage;
    if (currentHealth <= 0) {
        currentHealth = 0;
        isAlive = false;
    }

    cout << name << " takes " << damage << " damage.\n";
}

// Heal this character by a specified amount, not exceeding maxHealth.
void Character::heal(int amount) {
    currentHealth = min(maxHealth, currentHealth + amount);
    cout << name << " heals " << amount << " HP (" 
         << currentHealth << "/" << maxHealth << ").\n";
}

// Fully restore health and clear defending status. Called between duels.
void Character::rest() {
    currentHealth = maxHealth;
    defending = false;
    cout << name << " rests and fully recovers health.\n";
}

// Add experience points and handle leveling up if threshold is reached.
void Character::addXP(int amount) {
    xp += amount;
    cout << name << " gains " << amount << " XP.\n";

    while (xp >= level * 100) {
        xp -= level * 100;
        levelUp();
    }
}

// Level up the character, increasing stats and restoring health.
void Character::levelUp() {
    level++;
    maxHealth += 10;
    baseAttack += 2;
    baseDefense += 1;
    currentHealth = maxHealth;

    cout << "\n**************************************************\n";
    cout << "   LEVEL UP!  " << name << " reached level " << level << "!\n";
    cout << "   HP +" << 10 << "   ATK +2   DEF +1\n";
    cout << "**************************************************\n\n";
}

// Print a summary of this character's stats. Derived classes extend this with their own special attributes.
void Character::printStatus() const {
    cout << "+----------------------------------------------+\n";
    cout << "| " << name << "  (" << classType << ")\n";
    cout << "| Level: " << level << "   XP: " << xp << "\n";
    cout << "| HP: " << currentHealth << "/" << maxHealth
         << "   ATK: " << baseAttack
         << "   DEF: " << baseDefense << "\n";
    cout << "+----------------------------------------------+\n";
}

// Standard attack using the base attack stat. Derived classes override this
// to customize their combat behavior (e.g., spells, crits, stamina use).
void Character::basicAttack(Character& target) {
    cout << name << " attacks " << target.getName() << "!\n";
    target.takeDamage(baseAttack);
}

// Put the character into a defending state, reducing damage on the next hit.
void Character::defend() {
    defending = true;
    cout << name << " braces for impact (defending).\n";
}

// Reset temporary states and provide small recovery after combat.
void Character::updateAfterCombat() {
    defending = false;
    if (isAlive && currentHealth < maxHealth) heal(maxHealth / 10);
}

// Apply difficulty adjustments for enemy characters.
void Character::applyEnemyDifficultyModifier() {
    maxHealth = maxHealth * 3 / 4;     
    currentHealth = maxHealth;         
    if (baseAttack > 3) {
        baseAttack -= 3;               
    }
    if (baseDefense > 1) {
        baseDefense -= 1;              
    }
}

// Save shared character data to a file. Derived classes append their own data.
void Character::saveBase(ofstream& out) const {
    out << name << "\n";
    out << level << " " << xp << "\n";
    out << maxHealth << " " << currentHealth << "\n";
    out << baseAttack << " " << baseDefense << "\n";
    out << isAlive << "\n";
}

// Load shared character data from a file. Derived classes load their own data.
void Character::loadBase(ifstream& in) {
    getline(in, name);
    in >> level >> xp;
    in >> maxHealth >> currentHealth;
    in >> baseAttack >> baseDefense;
    in >> isAlive;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    defending = false;
}

// Base implementations (meant to be overridden if needed)
void Character::saveToFile(ofstream& out) const {
    saveBase(out);
}

void Character::loadFromFile(ifstream& in) {
    loadBase(in);
}

// Destructor
Character::~Character() {}
