#ifndef KINGGOB_H
#define KINGGOB_H

#include "enemy.h"
#include "generator.h"

using namespace std;

class GoblinKing : public Enemy {
private:
    vector<Character*> *allies;

public:
    GoblinKing()
    : Enemy(), allies(nullptr)
    {}

    GoblinKing(const GoblinKing &g)
    : Enemy(g), allies(g.allies)
    {}

    GoblinKing(string n)
    : Enemy(n, 220, 22, 8, 0.20, 1.8, 0.03, 3, 4), allies(nullptr)
    {}

    CharacterType getType() override {
        return CharacterType::GOBLIN_KING;
    }

    void setAllies(vector<Character*> *allyList) {
        allies = allyList;
    }

    void attack(vector<Character*> heroes) override {
        if (allies != nullptr) {
            Character* hurt = nullptr;
            for (int i = 0; i < allies->size(); i++) {
                Character* ally = (*allies)[i];
                if (ally != this && ally->isAlive() && ally->getHealth() < ally->getMaxHealth()) {
                    if (hurt == nullptr || *ally < *hurt) {
                        hurt = ally;
                    }
                }
            }

            if (hurt != nullptr) {
                hurt->heal(20);
                cout << name << " used Dark Mending on " << hurt->getName() << "!\n";
                return;
            }

            Character* weakest = nullptr;
            for (int i = 0; i < allies->size(); i++) {
                Character* ally = (*allies)[i];
                if (ally != this && ally->isAlive()) {
                    if (weakest == nullptr || *ally < *weakest) {
                        weakest = ally;
                    }
                }
            }

            if (weakest != nullptr) {
                weakest->buffStrength(1.2);
                cout << name << " used Royal Command on " << weakest->getName() << "!\n";
                return;
            }
        }

        vector<int> aliveIndices;
        int preferred = -1;
        for (int i = 0; i < heroes.size(); i++) {
            if (!heroes[i]->isAlive()) {
                continue;
            }

            aliveIndices.push_back(i);

            if (preferred == -1 || *heroes[i] < *heroes[preferred]) {
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

        cout << name << " is going to attack " << heroes[enemy]->getName() << ".\n";

        int attack = 1;
        bool poison = false;
        if (canUseSkill1()) {
            attack = 2;
            poison = true;
        } else if (canUseSkill2()) {
            attack = 3;
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
            damage = (int)(damage * typeMultiplier(heroes[enemy]));
            heroes[enemy]->receiveDamage(damage);
        }

        if (poison) {
            heroes[enemy]->applyPoison(3);
        }
    }

    int skillAttack1() override {
        if (!canUseSkill1()) {
            cout << "Skill unavailable!\n";
            return 0;
        }

        int damage = 14;
        currentCooldown1 = skillCooldown1;
        cout << name << " used Curse!\n";

        return damage;
    }

    int skillAttack2() override {
        if (!canUseSkill2()) {
            cout << "Skill unavailable!\n";
            return 0;
        }

        int damage = 26;
        currentCooldown2 = skillCooldown2;
        cout << name << " used Royal Strike!\n";

        return damage;
    }
};

#endif
