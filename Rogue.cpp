// Rogue.cpp
// Implements the Rogue class, an agile subclass of Character.
// Rogues specialize in fast attacks, critical hits, and evasive tactics.
// Their primary resource is Energy, used for rapid strikes and Backstab.
// This file defines how rogues attack, defend, regenerate energy, and
// save/load their unique stats during persistence.

#include "Rogue.h"
#include <algorithm>
#include <random>
#include <limits>

using namespace std;

// Default Rogue with preset energy, crit rate, and weapon.
Rogue::Rogue()
    : Character("Unknown Rogue", "Rogue"),
      maxEnergy(50), currentEnergy(50),
      critChance(0.25), dodgeChance(0.2),
      weaponName("Daggers") {}

// Named Rogue with initialized stats and weapon.
Rogue::Rogue(const string& name)
    : Character(name, "Rogue"),
      maxEnergy(50), currentEnergy(50),
      critChance(0.25), dodgeChance(0.2),
      weaponName("Daggers") {}

// Restore a specified amount of energy, capped at maxEnergy.
void Rogue::restoreEnergy(int amount) {
    currentEnergy = min(maxEnergy, currentEnergy + amount);
    cout << name << " restores " << amount << " energy.\n";
}

// Print shared stats then rogue-specific details.
void Rogue::printStatus() const {
    Character::printStatus();
    cout << "Energy: " << currentEnergy << "/" << maxEnergy << "\n";
    cout << "Crit Chance: " << critChance * 100 << "%\n";
    cout << "Dodge Chance: " << dodgeChance * 100 << "%\n";
}

// Rogue's basic attack with chance for critical hit.
// If low energy: weak attack.
void Rogue::basicAttack(Character& target) {
    if (currentEnergy < 5) {
        cout << name << " makes a weak slash.\n";
        target.takeDamage(baseAttack);
        return;
    }
    currentEnergy -= 5;

    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 1.0);

    bool crit = dist(gen) < critChance;
    int damage = baseAttack;
    if (crit) {
        damage = static_cast<int>(damage * 1.75);
        cout << "CRITICAL HIT! ";
    }
    cout << name << " slashes " << target.getName() << "!\n";
    target.takeDamage(damage);
}

// Rogue defend, regenerates some energy and reduces incoming damage.
void Rogue::defend() {
    Character::defend();
    restoreEnergy(5);
}

// Perform a high-damage Backstab attack consuming significant energy.
void Rogue::specialAction(Character& target) {
    if (currentEnergy < 15) {
        cout << name << " is out of energy. Using basic attack.\n";
        basicAttack(target);
        return;
    }
    currentEnergy -= 15;

    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 1.0);

    bool crit = dist(gen) < (critChance + 0.25);
    int damage = baseAttack + 5;
    if (crit) {
        damage *= 2;
        cout << "DEVASTATING BACKSTAB! ";
    }
    cout << name << " performs Backstab!\n";
    target.takeDamage(damage);
}

// Regenerates energy after combat and resets defensive status.
void Rogue::updateAfterCombat() {
    Character::updateAfterCombat();
    restoreEnergy(10);
}

// Saves rogue-specific stats after base character data.
void Rogue::saveToFile(ofstream& out) const {
    Character::saveToFile(out);
    out << maxEnergy << " " << currentEnergy << "\n";
    out << critChance << " " << dodgeChance << "\n";
    out << weaponName << "\n";
}

// Loads rogue-specific stats after base character data.
void Rogue::loadFromFile(ifstream& in) {
    Character::loadFromFile(in);
    in >> maxEnergy >> currentEnergy;
    in >> critChance >> dodgeChance;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(in, weaponName);
}
