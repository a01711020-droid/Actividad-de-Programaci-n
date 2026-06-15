#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>
#include <random>
#include "generator.h"
#include "scenario.h"
#include "console.h"
#include "character.h"
#include "hero.h"
#include "exceptions.h"
#include "warrior.h"
#include "archer.h"
#include "wizard.h"
#include "enemy.h"
#include "goblin.h"
#include "captaingob.h"
#include "kinggob.h" 

using namespace std;

void creatingHeroes(vector<Character*> &heroes) {
    string name;
    int option;

    heroes.resize(2);
    for (int i = 0; i < heroes.size(); i++) {
        cout << "(" << i << ")" << " Hero's name? ";
        cin >> name;
        cout << "Hero class?\n";
        cout << "1. Warrior\n";
        cout << "2. Archer\n";
        cout << "3. Wizard\n";
        option = Console::validateIntegerInRange("Option? ", 1, 3);

        switch(option) {
            case 1 : heroes[i] = new Warrior(name); break;
            case 2 : heroes[i] = new Archer(name); break;
            default: heroes[i] = new Wizard(name); break;
        }
    }
}

int main(int argc, char* argv[]) {
    vector<Character*> heroes;

    creatingHeroes(heroes);

    vector<int> order = {0, 1, 2, 3, 4, 5};
    random_device rd;
    mt19937 gen(rd());
    shuffle(order.begin(), order.end(), gen);

    vector<Scenario> scenarios;
    for (int i = 0; i < 3; i++) {
        int index = order[i];
        stringstream filename;
        filename << "scenarios/scenario0" << (index + 1) << ".txt";
        bool isFinalBattle = (i == 2);

        // Manejo de excepciones
        try {
            scenarios.push_back(Scenario(filename.str(), heroes, isFinalBattle,
                Scenario::buffPairs[index][0], Scenario::buffPairs[index][1]));
        } catch (const std::exception &e) {
            cout << "Error: " << e.what() << "\n";
        }
    }

    int i = 0;
    while (i < scenarios.size()) {
        scenarios[i].execute();
        if (!scenarios[i].heroesWon()) {
            break;
        }
        i++;
    }

    return 0;
}