#ifndef SPELL_H
#define SPELL_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

// Clase abstracta base para todos los hechizos.
// Los operadores < y == comparan por poder base (getPower()).
class Spell {
public:
    virtual int getPower() const = 0;
    virtual void launch() = 0;
    virtual string toString() const = 0;
    virtual ~Spell() {}

    bool operator<(const Spell& other) const {
        return getPower() < other.getPower();
    }

    bool operator==(const Spell& other) const {
        return getPower() == other.getPower();
    }
};

// Hechizo de ataque
class AttackSpell : public Spell {
private:
    int basicDamage;
    int realDamage;

public:
    AttackSpell() : basicDamage(1), realDamage(1) {
        srand(time(0));
    }

    AttackSpell(const AttackSpell& other)
        : basicDamage(other.basicDamage), realDamage(other.realDamage) {
        srand(time(0));
    }

    AttackSpell(int damage) : basicDamage(damage), realDamage(damage) {
        srand(time(0));
    }

    int getPower() const override {
        return basicDamage;
    }

    void launch() override {
        int variation = rand() % 21 - 10;
        realDamage = basicDamage + variation;
    }

    string toString() const override {
        stringstream ss;
        ss << "Attack Spell causes " << realDamage << " damage.";
        return ss.str();
    }
};

// Hechizo defensivo
class DefenseSpell : public Spell {
private:
    int basicDefense;
    int realDefense;

public:
    DefenseSpell() : basicDefense(1), realDefense(1) {
        srand(time(0));
    }

    DefenseSpell(const DefenseSpell& other)
        : basicDefense(other.basicDefense), realDefense(other.realDefense) {
        srand(time(0));
    }

    DefenseSpell(int defense) : basicDefense(defense), realDefense(defense) {
        srand(time(0));
    }

    int getPower() const override {
        return basicDefense;
    }

    void launch() override {
        int variation = rand() % 11 - 5;
        realDefense = basicDefense + variation;
    }

    string toString() const override {
        stringstream ss;
        ss << "Defense Spell provides " << realDefense << " defense.";
        return ss.str();
    }
};

// Hechizo de curacion
class HealingSpell : public Spell {
private:
    int basicHealing;
    int realHealing;

public:
    HealingSpell() : basicHealing(1), realHealing(1) {
        srand(time(0));
    }

    HealingSpell(const HealingSpell& other)
        : basicHealing(other.basicHealing), realHealing(other.realHealing) {
        srand(time(0));
    }

    HealingSpell(int healing) : basicHealing(healing), realHealing(healing) {
        srand(time(0));
    }

    int getPower() const override {
        return basicHealing;
    }

    void launch() override {
        int variation = rand() % 17 - 8;
        realHealing = basicHealing + variation;
    }

    string toString() const override {
        stringstream ss;
        ss << "Healing Spell restores " << realHealing << " health points.";
        return ss.str();
    }
};

#endif
