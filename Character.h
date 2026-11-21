#ifndef CHARACTER_H
#define CHARACTER_H

// Character.h
// Base class that represents any playable or enemy character in the game.
// Stores core stats like name, level, health, and basic combat values.
// Also provides a polymorphic interface for actions such as attacking,
// defending, special abilities, and saving/loading character data.

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Character {
protected:
// ===== Core character identity & progression =====
    string name;        // Character's display name.
    string classType;   // Character's class type (e.g., Warrior, Wizard, Rogue).
    int level;          // Character's current level.
    int xp;             // Current experience points.

// ===== Health and combat stats =====
    int maxHealth;      // Maximum health points.
    int currentHealth;  // Current health points (0 means dead).
    int baseAttack;     // Base attack damage (for physical/magical damage).
    int baseDefense;    // Base defense value (reduces incoming damage).
    bool isAlive;       // Is the character alive.
    bool defending;     // Is the character currently defending.

// ===== Shared save/load helpers =====
    void saveBase(ofstream& out) const;
    void loadBase(ifstream& in);

public:
// ===== Constructors =====

    // Default constructor: sets up a generic level 1 character with default name and starting stats.
    Character();

    // Constructor: sets name and class type, and initializes base stats.
    Character(const string& name, const string& classType);

// ===== Core gameplay / state-changing functions =====

    // Apply damage to this character, taking into account baseDefense 
    // and whether the character is currently defending, may set isAlive to false.
    void takeDamage(int amount);

    // Heal this character by a given amount, without exceeding maxHealth.
    void heal(int amount);

    // Fully restore health (and clear defending status), can be used between duels.
    virtual void rest();

    // Add experience points, and handle leveling up if enough XP is gained.
    void addXP(int amount);

    // Level up the character, increasing stats appropriately, and resetting currentHealth to maxHealth.
    void levelUp();

// ===== Simple getters =====
    string getName() const { return name; }
    string getClassType() const { return classType; }
    int getLevel() const { return level; }
    int getCurrentHealth() const { return currentHealth; }
    int getMaxHealth() const { return maxHealth; }
    bool alive() const { return isAlive; }

// Change the class label (used when loading from a file).
    void setClassType(const string& type) { classType = type; }

// ===== Polymorphic combat interface =====

    // Print a summary of this character's stats,
    // derived classes may add more info (stamina, mana, energy, etc.).
    virtual void printStatus() const;

    // Perform a basic attack against a target character.
    // Derived classes override this to implement class-specific behavior.
    virtual void basicAttack(Character& target);

    // Put the character into a defending state, reducing damage on the next hit, 
    // derived classes may extend this with extra effects (like regen).
    virtual void defend();

    // Perform the character's special ability (spell, power move, etc.),
    // must be implemented by every derived class.
    virtual void specialAction(Character& target) = 0;

    // Called after each combat to clean up temporary states or provide small recovery.
    virtual void updateAfterCombat();

// ===== File I/O for saving and loading =====

    // Save this character's data to an already-open output file stream.
    // Base implementation writes shared fields; derived classes append their own.
    virtual void saveToFile(ofstream& out) const;

    // Load this character's data from an already-open input file stream.
    // Base implementation reads shared fields; derived classes read their own.
    virtual void loadFromFile(ifstream& in);

// ===== Difficulty adjustment (used for enemies only) =====
    void applyEnemyDifficultyModifier();

// Virtual destructor to allow safe deletion through Character* pointers.
    virtual ~Character();
};

#endif
