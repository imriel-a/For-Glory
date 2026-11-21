#ifndef ROGUE_H
#define ROGUE_H

// Rogue.h
// Defines the Rogue class, a subclass derived from Character.
// Rogues rely on agility, critical hits, and evasive maneuvers. They use
// "energy" as their main resource and specialize in fast, precise strikes,
// with occasional high-damage attacks such as Backstab.
// This file declares rogue-specific stats (energy, crit chance, dodge chance),
// overrides combat behavior, and provides save/load functions.

#include "Character.h"
using namespace std;

class Rogue : public Character {
private:
    int maxEnergy;          // Maximum energy capacity.
    int currentEnergy;      // Current energy available for rogue actions.
    double critChance;      // Chance to perform a critical hit.
    double dodgeChance;     // Chance to dodge an incoming attack.
    string weaponName;      // Name of the rogue's weapon.

public:

    // Default Rogue with preset energy, crit rate, and weapon.
    Rogue();

    // Named Rogue with initialized stats and weapon.
    Rogue(const string& name);

    // Restore a specified amount of energy, capped at maxEnergy.
    void restoreEnergy(int amount);

    // Print rogue-specific status including energy, crit chance, and dodge chance.
    virtual void printStatus() const override;

    // Perform a basic attack with chance for critical hit.
    virtual void basicAttack(Character& target) override;

    // Rogue defend, regenerates some energy and reduces incoming damage.
    virtual void defend() override;

    // Perform a high-damage Backstab attack consuming significant energy.
    virtual void specialAction(Character& target) override;

    // Regenerates energy after combat and resets defensive status.
    virtual void updateAfterCombat() override;

    // Saves rogue-specific stats after base character data.
    virtual void saveToFile(ofstream& out) const override;

    // Loads rogue-specific stats after base character data.
    virtual void loadFromFile(ifstream& in) override;
};

#endif
