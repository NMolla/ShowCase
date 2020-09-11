//
//  Lord.cpp
//  homework6
//
//  Created by Nahom Molla on 11/8/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include "Lord.hpp"
#include "Protector.hpp"
using namespace std;

namespace WarriorCraft {
    Lord::Lord(const string& name) : Noble(name) {}
    bool Lord::isAlive() const { return alive; }
    double Lord::getStrength() const {
        double armyStrength=0;
        for (Protector* someProtector : protectors){
            armyStrength += someProtector->getStrength();
        }
        return armyStrength;
    }
    bool Lord::hires(Protector& protectorToHire){
        if (alive && !protectorToHire.isEmployed()){
            protectorToHire.setEmployer(this);
            protectors.push_back(&protectorToHire);
            return true;
        }
        return false;
    }
    bool Lord::fire(Protector& protectorToFire){
        if (alive && release(protectorToFire)) {
            cout << protectorToFire.getName() << "You are fired --" << getName() << endl;
            return true;
        }
        return false;
    }
    bool Lord::release(Protector& protectorToRelease) {
        size_t indexOfWarrior = findProtector(protectorToRelease);
        if(indexOfWarrior == protectors.size()){
            cerr << "Protector not in army!" << endl;
            return false;
        }
        protectors[indexOfWarrior]->setEmployer(nullptr);
        for (size_t i=indexOfWarrior; i<protectors.size(); ++i){
            protectors[i] = protectors[i+1];
        }
        protectors.pop_back();
        return true;
    }
    void Lord::fight() const {
        for (Protector* someProtector : protectors){
            someProtector->attack();
        }
    }
    void Lord::kill() {
        alive = false;
        for (Protector* someProtector : protectors){ //changed
            someProtector->setStrength(0);
        }
    }
    size_t Lord::findProtector(Protector& protectorToFind) const {
        for (size_t i=0; i<protectors.size(); ++i){
            if (protectors[i] == &protectorToFind){
                return i;
            }
        }
        return protectors.size();
    }
    void Lord::reduceStrength(double opponentStrength) {
        double factor = 1 - opponentStrength/getStrength();
        for (Protector* someProtector : protectors){
            someProtector->setStrength(someProtector->getStrength() * factor);
        }
    }
}
