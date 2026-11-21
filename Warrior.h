#ifndef WARRIOR_H
#define WARRIOR_H

// Warrior.h
// Defines the Warrior class, derived from Character.
// Warriors rely on stamina and physical strength.
// This class extends the base character behavior with 
// stamina consumption, physical abilities, weapon
// modifiers, and persistence through file I/O.

#include "Character.h"
using namespace std;

class Warrior : public Character {
private:
    int maxStamina;         // Maximum stamina capacity.
    int currentStamina;     // Current stamina available for actions.
    string weaponName;      // Name of the warrior's equipped weapon.
    int weaponDamageBonus;  // Additional damage added to all attacks.

public:

    // Default warrior with preset combat stats and weapon.
    Warrior();

    // Named warrior with initialized stats and weapon.
    Warrior(const string& name);

    // Restore a specified amount of stamina, capped at maxStamina.
    void restoreStamina(int amount);

    // Print the current status of the warrior, including stamina and weapon details.
    virtual void printStatus() const override;

    // Perform a basic physical attack using the warrior's weapon.
    virtual void basicAttack(Character& target) override;

    // Warrior defend, regenerates some stamina and reduces incoming damage.
    virtual void defend() override;

    // Perform a powerful special attack consuming significant stamina.
    virtual void specialAction(Character& target) override;

    // Regenerates stamina after combat and resets defensive status.
    virtual void updateAfterCombat() override;

    // Saves warrior-specific stats after base character data.
    virtual void saveToFile(ofstream& out) const override;

    // Loads warrior-specific stats after base character data.
    virtual void loadFromFile(ifstream& in) override;
};

#endif
