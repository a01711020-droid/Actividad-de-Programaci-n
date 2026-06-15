#ifndef ARCHER_H
#define ARCHER_H

#include "hero.h"

class Archer : public Hero {
private:
    double dodgeChance;

public:
    Archer() 
    : Hero(), dodgeChance(0.15)
    {}

    Archer(const Archer &a)
    : Hero(a), dodgeChance(0.15)
    {}
    
    Archer(std::string n)
    : Hero(n, 90, 16, 5, 0.30, 2.0, 0.10, 1, 3, 50, 4, 8, 10), dodgeChance(0.15)
    {}

    CharacterType getType() override {
        return CharacterType::ARCHER;
    }

    void receiveDamage(int damage) override {
        double dodgeRoll = (rand() % 100) / 100.0;
        if (dodgeRoll < dodgeChance) {
            std::cout << name << " dodged the attack!\n";
            return;
        }

        Character::receiveDamage(damage);
    }

    int skillAttack1() override {
        if (!canUseSkill1()) {
            std::cout << "Skill unavailable!\n";
            return 0;
        }

        int damage = 10;
        useMana(manaCost1);
        currentCooldown1 = skillCooldown1;
        std::cout << name << " used Lightning Arrow!\n";

        return damage;
    }

    int skillAttack2() override {
        if (!canUseSkill2()) {
            std::cout << "Skill unavailable!\n";
            return 0;
        }

        int damage = 33;
        useMana(manaCost2);
        currentCooldown2 = skillCooldown2;
        std::cout << name << " used Double Shot!\n";

        return damage;
    }

    void displayAttacks() {
        std::cout << "1. Basic attack.\n";
        std::cout << "2. Lightning Arrow." << skillStatusSuffix(true) << "\n";
        std::cout << "3. Double Shot." << skillStatusSuffix(false) << "\n";
    }
};

#endif