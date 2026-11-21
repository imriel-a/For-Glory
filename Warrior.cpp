// Warrior.cpp
// Implements the Warrior class, a physically strong subclass derived from Character.
// Warriors rely on stamina and weapon-based attacks. This file defines how
// warriors strike, defend, recover stamina, and manage their unique attributes
// during combat and file saving/loading.

#include "Warrior.h"
#include <algorithm>
#include <limits>

using namespace std;

// Default warrior with preset combat stats and weapon.
Warrior::Warrior()
    : Character("Unknown Warrior", "Warrior"),
      maxStamina(50), currentStamina(50),
      weaponName("Sword"), weaponDamageBonus(5) {}

// Named warrior with initialized stats and weapon.
Warrior::Warrior(const string& name)
    : Character(name, "Warrior"),
      maxStamina(50), currentStamina(50),
      weaponName("Sword"), weaponDamageBonus(5) {}


// Restore a specified amount of stamina, capped at maxStamina.
void Warrior::restoreStamina(int amount) {
    currentStamina = min(maxStamina, currentStamina + amount);
    cout << name << " restores " << amount << " stamina.\n";
}

// Print the current status of the warrior, including stamina details.
void Warrior::printStatus() const {
    Character::printStatus();
    cout << "Stamina: " << currentStamina << "/" << maxStamina << "\n";
}

// Warrior basic attack.
// If low stamina: weak attack.
// Otherwise: attack with weapon bonus.
void Warrior::basicAttack(Character& target) {
    if (currentStamina < 5) {
        cout << name << " is low on stamina, weak attack.\n";
        target.takeDamage(baseAttack);
        return;
    }
    currentStamina -= 5;

    cout << name << " swings " << weaponName << "!\n";
    target.takeDamage(baseAttack + weaponDamageBonus);
}

// Warrior defend, regenerates some stamina and reduces incoming damage.
void Warrior::defend() {
    Character::defend();
    restoreStamina(5);
}

// Perform a powerful special attack consuming significant stamina.
// If insufficient stamina, falls back to basic attack.
void Warrior::specialAction(Character& target) {
    if (currentStamina < 15) {
        cout << name << " lacks stamina for Power Strike.\n";
        basicAttack(target);
        return;
    }
    currentStamina -= 15;

    cout << name << " uses POWER STRIKE!\n";
    target.takeDamage(baseAttack + weaponDamageBonus * 2);
}

// After combat, regenerate stamina and reset defending status.
void Warrior::updateAfterCombat() {
    Character::updateAfterCombat();
    restoreStamina(10);
}

// Saves warrior-specific stats after base character data.
void Warrior::saveToFile(ofstream& out) const {
    Character::saveToFile(out);
    out << maxStamina << " " << currentStamina << "\n";
    out << weaponName << "\n";
    out << weaponDamageBonus << "\n";
}

// Loads warrior-specific stats after base character data.
void Warrior::loadFromFile(ifstream& in) {
    Character::loadFromFile(in);
    in >> maxStamina >> currentStamina;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(in, weaponName);
    in >> weaponDamageBonus;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
}
