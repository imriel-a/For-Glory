// Wizard.cpp
// Implements the Wizard class, a magic-based subclass derived from Character.
// Wizards use mana to cast spells, perform magical defenses, and regenerate
// their resources over time. This file defines how wizards attack, defend,
// recover mana, and save/load their unique statistics.

#include "Wizard.h"
#include <algorithm>
#include <limits>

using namespace std;

// Default constructor: builds a generic wizard with baseline magic stats.
Wizard::Wizard()
    : Character("Unknown Wizard", "Wizard"),
      maxMana(60), currentMana(60),
      spellPower(15), manaRegenRate(5) {}

// Overloaded constructor: creates a named wizard with initialized stats.
Wizard::Wizard(const string& name)
    : Character(name, "Wizard"),
      maxMana(60), currentMana(60),
      spellPower(15), manaRegenRate(5) {}

// Restores a specified amount of mana, capped at maxMana.
void Wizard::restoreMana(int amount) {
    currentMana = min(maxMana, currentMana + amount);
    cout << name << " restores " << amount << " mana.\n";
}

// Print shared stats then wizard-specific details.
void Wizard::printStatus() const {
    Character::printStatus();
    cout << "Mana: " << currentMana << "/" << maxMana << "\n";
    cout << "Spell Power: " << spellPower << "\n";
}

// Wizard's basic attack.
// If enough mana: casts Magic Bolt.
// If low mana: casts physical staff hit.
void Wizard::basicAttack(Character& target) {
    if (currentMana < 5) {
        cout << name << " hits with staff.\n";
        target.takeDamage(baseAttack);
        return;
    }
    currentMana -= 5;

    cout << name << " casts Magic Bolt!\n";
    target.takeDamage(baseAttack + spellPower / 2);
}

// Base class defensive behavior plus mana regeneration.
void Wizard::defend() {
    Character::defend();
    restoreMana(manaRegenRate);
}

// Wizard's special action: casts Fireball.
// Consumes significant mana for high damage.
// If insufficient mana, falls back to basic attack.
void Wizard::specialAction(Character& target) {
    if (currentMana < 20) {
        cout << name << " lacks mana for Fireball.\n";
        basicAttack(target);
        return;
    }
    currentMana -= 20;

    cout << name << " casts FIREBALL!\n";
    target.takeDamage(spellPower * 2);
}

// After combat, regenerate mana and reset defending status.
void Wizard::updateAfterCombat() {
    Character::updateAfterCombat();
    restoreMana(manaRegenRate * 2);
}

// Saves wizard-specific stats after base character data.
void Wizard::saveToFile(ofstream& out) const {
    Character::saveToFile(out);
    out << maxMana << " " << currentMana << "\n";
    out << spellPower << " " << manaRegenRate << "\n";
}

// Loads wizard-specific stats after base character data.
void Wizard::loadFromFile(ifstream& in) {
    Character::loadFromFile(in);
    in >> maxMana >> currentMana;
    in >> spellPower >> manaRegenRate;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
}
