#ifndef WIZARD_H
#define WIZARD_H

#include "hero.h"

class Wizard : public Hero {
private:
    int adittionalManaRegeneration;

public:
    Wizard() 
    : Hero(), adittionalManaRegeneration(5)
    {}

    Wizard(const Wizard &w)
    : Hero(w), adittionalManaRegeneration(5)
    {}
    
    Wizard(std::string n)
    : Hero(n, 70, 10, 3, 0.25, 2.5, 0.15, 1, 4, 120, 8, 20, 25), adittionalManaRegeneration(5)
    {}

    CharacterType getType() override {
        return CharacterType::WIZARD;
    }

    void performAction(std::vector<Character*> v) override {
        restoreMana(adittionalManaRegeneration);
        std::cout << name << " restored " << adittionalManaRegeneration << " mana.\n";
        Hero::performAction(v);
    }

    int skillAttack1() override {
        if (!canUseSkill1()) {
            std::cout << "Skill unavailable!\n";
            return 0;
        }

        int damage = 20;
        useMana(manaCost1);
        currentCooldown1 = skillCooldown1;
        std::cout << name << " used Ice Storm!\n";

        return damage;
    }

    int skillAttack2() override {
        if (!canUseSkill2()) {
            std::cout << "Skill unavailable!\n";
            return 0;
        }

        int damage = 31;
        useMana(manaCost2);
        currentCooldown2 = skillCooldown2;
        std::cout << name << " used Fireball!\n";

        return damage;
    }

    void displayAttacks() {
        std::cout << "1. Basic attack.\n";
        std::cout << "2. Ice Storm." << skillStatusSuffix(true) << "\n";
        std::cout << "3. Fireball." << skillStatusSuffix(false) << "\n";
    }
};

#endif