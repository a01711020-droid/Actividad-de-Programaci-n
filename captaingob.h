#ifndef CAPTAINGOB_H
#define CAPTAINGOB_H

#include "enemy.h"
#include "generator.h"

using namespace std;

class GoblinCaptain : public Enemy {
public:
    GoblinCaptain()
    : Enemy()
    {}

    GoblinCaptain(const GoblinCaptain &g)
    : Enemy(g)
    {}

    GoblinCaptain(string n)
    : Enemy(n, 80, 16, 5, 0.20, 1.6, 0.05, 3, 4)
    {}

    CharacterType getType() override {
        return CharacterType::GOBLIN_CAPTAIN;
    }

    void attack(vector<Character*> v) override {
        vector<int> aliveIndices;
        int preferred = -1;
        for (int i = 0; i < v.size(); i++) {
            if (!v[i]->isAlive()) {
                continue;
            }

            aliveIndices.push_back(i);

            if (preferred == -1 || *v[i] < *v[preferred]) {
                preferred = i;
            }
        }

        if (preferred == -1) {
            cout << "There are no valid targets to attack.\n";
            return;
        }

        int enemy = preferred;
        if (aliveIndices.size() > 1 && Generator::randomNumber(1, 100) <= 40) {
            for (int i = 0; i < aliveIndices.size(); i++) {
                if (aliveIndices[i] != preferred) {
                    enemy = aliveIndices[i];
                    break;
                }
            }
        }

        cout << name << " is going to attack " << v[enemy]->getName() << ".\n";

        int attack = 1;
        bool poison = false;
        if (canUseSkill2()) {
            attack = 3;
            poison = true;
        } else if (canUseSkill1()) {
            attack = 2;
        }

        int damage = 0;
        switch(attack) {
            case 1 :
                damage = basicAttack();
                cout << name << " used Basic Attack!\n";
                break;
            case 2 :
                damage = skillAttack1();
                break;
            case 3 :
                damage = skillAttack2();
                break;
        }

        if (damage > 0) {
            damage = (int)(damage * typeMultiplier(v[enemy]));
            v[enemy]->receiveDamage(damage);
        }

        if (poison) {
            v[enemy]->applyPoison(3);
        }
    }

    int skillAttack1() override {
        if (!canUseSkill1()) {
            cout << "Skill unavailable!\n";
            return 0;
        }

        int damage = 22;
        currentCooldown1 = skillCooldown1;
        cout << name << " used Brutal Strike!\n";

        return damage;
    }

    int skillAttack2() override {
        if (!canUseSkill2()) {
            cout << "Skill unavailable!\n";
            return 0;
        }

        int damage = 20;
        currentCooldown2 = skillCooldown2;
        cout << name << " used Venom Slash!\n";

        return damage;
    }
};

#endif
