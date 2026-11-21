#ifndef WIZARD_H
#define WIZARD_H

// Wizard.h
// Defines the Wizard class, derived from Character. 
// A Wizard specializes in magic combat, using mana to cast powerful spells.
// This class extends the base character functionality with mana management,
// spellcasting attacks, defensive magic, mana regeneration, and persistence
// functions for saving/loading wizard-specific data.

#include "Character.h"
using namespace std;

class Wizard : public Character {
private:
    int maxMana;            // Maximum mana the wizard can store.
    int currentMana;        // Current mana available for casting spells.
    int spellPower;         // Additional damage applied to spells.
    int manaRegenRate;      // Amount of mana restored after each duel and defend.

public:

    // Default constructor: builds a generic wizard with baseline magic stats.
    Wizard();

    // Overloaded constructor: creates a named wizard with initialized stats.
    Wizard(const string& name);

    // Restores a specified amount of mana, capped at maxMana.
    void restoreMana(int amount);

    // Print wizard-specific status including mana and spell power.
    virtual void printStatus() const override;

    // Perform a basic magical attack against a target character.
    virtual void basicAttack(Character& target) override;

    // Wizard defend, regenerates some mana and reduces incoming damage.
    virtual void defend() override;

    // Cast a powerful spell as the special action, consuming significant mana.
    virtual void specialAction(Character& target) override;

    // Regenerates mana after combat and resets defensive status.
    virtual void updateAfterCombat() override;

    // Saves wizard-specific stats after base character data.
    virtual void saveToFile(ofstream& out) const override;

    // Loads wizard-specific stats after base character data.
    virtual void loadFromFile(ifstream& in) override;
};

#endif
