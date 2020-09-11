//
//  Noble.cpp
//  homework5
//
//  Created by Nahom Molla on 10/17/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include "Noble.hpp"
#include "Warrior.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace WarriorCraft {
    Noble::Noble(const string& name) : name(name) {}
    const string& Noble::getName() const { return name; }
    bool Noble::hire(Warrior& warriorToHire){
        if (warriorToHire.isFreeAgent()){
            warriorToHire.setEmployer(this);
            army.push_back(&warriorToHire);
            return true;
        }
        return false;
    }

    bool Noble::fire(Warrior& warriorToFire){
        for (size_t i=0; i<army.size(); ++i){
            if (army[i] == &warriorToFire){
                army[i] = nullptr;
                removeNullptr();
                return true;
            }
        }
        return false;
    }

    void Noble::battle(Noble& opponent){
        cout << name << " battles " << opponent.name << endl;
        if (this->alive && opponent.alive){
            if (this->getArmyStrength() > opponent.getArmyStrength()){
                cout << name << " defeats " << opponent.name << endl;
                this->subtractStrength(1-(opponent.army.size()/this->army.size()));
                opponent.kill();
            }
            else if(this->getArmyStrength() < opponent.getArmyStrength()){
                cout << opponent.name << " defeats " << name << endl;
                opponent.subtractStrength(1-(this->army.size()/opponent.army.size()));
                kill();
            }
            else {
                this->kill();
                opponent.kill();
                cout << "Mutual Annihalation: " << name << " and " << opponent.name <<
                " die at each other's hands" << endl;
            }
        }
        else if(this->alive){
            cout << "He's dead, " << this->name << endl;
        }
        else if(opponent.alive){
            cout << "He's dead, " << opponent.name << endl;
        }
        else {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
    }

    void Noble::removeNullptr(){
        bool start=false;
        for(size_t i=0; i<army.size()-1; ++i){
            if (army[i] == nullptr){
                start=true;
            }
            if(start){
                army[i] = army[i+1];
            }
        }
        army.pop_back();
    }

    void Noble::kill(){
        alive = false;
        for (size_t i=0; i<army.size(); ++i){
            army[i]->setStrength(0);
        }
    }

    void Noble::subtractStrength(double strengthRatio){
        for (Warrior* someWarrior : army){
            someWarrior->setStrength(someWarrior->getStrength() * strengthRatio);
        }
    }

    double Noble::getArmyStrength() const {
        double armyStrength=0;
        for (size_t i=0; i<army.size(); ++i){
            armyStrength += army[i]->getStrength();
        }
        return armyStrength;
    }

    ostream& operator<<(ostream& os, const Noble& rhs){
        os << rhs.name << " has an army of " << rhs.army.size() << endl;
        for (Warrior* someWarrior : rhs.army){
            os << "\t" << *someWarrior;
        }
        return os;
    }
}
