#ifndef SCENARIO_H
#define SCENARIO_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include "character.h"
#include "hero.h"
#include "enemy.h"
#include "goblin.h"
#include "captaingob.h"
#include "kinggob.h"
#include "console.h"

class Scenario {
public:

    static constexpr CharacterType buffPairs[6][2] = {
        {CharacterType::ARCHER, CharacterType::WARRIOR},
        {CharacterType::GOBLIN, CharacterType::GOBLIN_CAPTAIN},
        {CharacterType::WIZARD, CharacterType::GOBLIN_KING},
        {CharacterType::GOBLIN_KING, CharacterType::WARRIOR},
        {CharacterType::WIZARD, CharacterType::GOBLIN_CAPTAIN},
        {CharacterType::WARRIOR, CharacterType::GOBLIN}
    };

private:
    std::string title, description, winningResult, losingResult;
    std::vector<Character*> heroes, enemies, characters;
    bool win;
    CharacterType buffedType, debuffedType;

    void generateEnemies(bool isFinalBattle) {
        if (isFinalBattle) {
            GoblinKing* king = new GoblinKing("Goblin King");
            enemies.push_back(king);

            int escorts = Generator::randomNumber(0, 2);
            for (int i = 0; i < escorts; i++) {
                if (Generator::randomNumber(1, 100) <= 70) {
                    enemies.push_back(new Goblin("Goblin Escort " + std::to_string(i + 1)));
                } else {
                    enemies.push_back(new GoblinCaptain("Goblin Captain Escort " + std::to_string(i + 1)));
                }
            }

            king->setAllies(&enemies);
        } else {
            int count = Generator::randomNumber(2, 3);
            for (int i = 0; i < count; i++) {
                if (Generator::randomNumber(1, 100) <= 70) {
                    enemies.push_back(new Goblin("Goblin Raider " + std::to_string(i + 1)));
                } else {
                    enemies.push_back(new GoblinCaptain("Goblin Captain " + std::to_string(i + 1)));
                }
            }
        }
    }

public:
    Scenario()
      : title(""), description(""), winningResult(""), losingResult(""), win(false),
        buffedType(CharacterType::WARRIOR), debuffedType(CharacterType::WARRIOR)
    {}

    Scenario(std::string filename, std::vector<Character *> &v, bool isFinalBattle,
        CharacterType buffedType, CharacterType debuffedType)
      : buffedType(buffedType), debuffedType(debuffedType) {
        std::ifstream file(filename);

        // Manejo de excepciones
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }

        if (!getline(file, title) ||
            !getline(file, description) ||
            !getline(file, winningResult) ||
            !getline(file, losingResult)) {
            throw std::runtime_error("Invalid scenario format in file: " + filename);
        }

        file.close();

        if (v.size() != 2) {
            throw std::invalid_argument("The party must contain exactly 2 heroes.");
        }

        win = false;

        heroes = std::vector<Character*>(v);

        generateEnemies(isFinalBattle);

        characters.resize(heroes.size() + enemies.size());
        int j = 0;
        for (int i = 0; i < heroes.size(); i++) {
            characters[j++] = heroes[i];
        }
        for (int i = 0; i < enemies.size(); i++) {
            characters[j++] = enemies[i];
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        shuffle(characters.begin(), characters.end(), gen);
    }

    Scenario(const Scenario &s)
      : title(s.title), description(s.description), winningResult(s.winningResult),
        losingResult(s.losingResult), win(s.win), characters(s.characters), heroes(s.heroes),
        enemies(s.enemies), buffedType(s.buffedType), debuffedType(s.debuffedType)
    {}

    bool heroesDefeated() {
        for (int i = 0; i < heroes.size(); i++) {
            if (heroes[i]->isAlive()) {
                return false;
            }
        }
        return true;
    }

    bool enemiesDefeated() {
        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i]->isAlive()) {
                return false;
            }
        }
        return true;
    }

    bool heroesWon() {
        return (win == true);
    }

    void execute() {
        std::cout << "\n===== " << title << " =====\n";
        std::cout << description << "\n";
        Console::waitForInput();

        std::vector<int> heroDeltas(heroes.size(), 0);
        for (int i = 0; i < heroes.size(); i++) {
            if (*heroes[i] == buffedType) {
                heroDeltas[i] = (int)(heroes[i]->getStrenght() * 0.2);
            } else if (*heroes[i] == debuffedType) {
                heroDeltas[i] = -(int)(heroes[i]->getStrenght() * 0.2);
            }

            if (heroDeltas[i] > 0) {
                heroes[i]->adjustStrength(heroDeltas[i]);
                std::cout << heroes[i]->getName() << " se siente fortalecido por este lugar! (+20% daño)\n";
            } else if (heroDeltas[i] < 0) {
                heroes[i]->adjustStrength(heroDeltas[i]);
                std::cout << heroes[i]->getName() << " se siente debilitado por este lugar! (-20% daño)\n";
            }
        }

        for (int i = 0; i < enemies.size(); i++) {
            if (*enemies[i] == buffedType) {
                enemies[i]->adjustStrength((int)(enemies[i]->getStrenght() * 0.2));
            } else if (*enemies[i] == debuffedType) {
                enemies[i]->adjustStrength(-(int)(enemies[i]->getStrenght() * 0.2));
            }
        }

        while (!heroesDefeated() && !enemiesDefeated()) {
            for (int i = 0; i < characters.size(); i++) {
                if (characters[i]->isAlive()) {
                    std::cout << "\n===== Attacking " << characters[i]->getName() << " =====\n";
                    if(dynamic_cast<Enemy*>(characters[i])) {
                        characters[i]->performAction(heroes);
                    } else if(dynamic_cast<Hero*>(characters[i])) {
                        characters[i]->displayStats();
                        characters[i]->performAction(enemies);
                    }
                    Console::waitForInput();
                }
            }
        }

        for (int i = 0; i < heroes.size(); i++) {
            if (heroDeltas[i] != 0) {
                heroes[i]->adjustStrength(-heroDeltas[i]);
            }
        }

        win = !heroesDefeated();
        if (win) {
            std::cout << "\n" << winningResult << "\n";
        } else {
            std::cout << "\n" << losingResult << "\n";
        }
        Console::waitForInput();
    }
};

#endif