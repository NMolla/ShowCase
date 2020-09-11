//
//  Warrior.cpp
//  homework5
//
//  Created by Nahom Molla on 10/17/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include "Warrior.hpp"
#include "Noble.hpp"
#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {
    Warrior::Warrior(const string& name, double strength) :
        name(name), strength(strength) {}
    const string& Warrior::getName() const { return name; }
    double Warrior::getStrength() const { return strength; }
    bool Warrior::isFreeAgent() const { return employer == nullptr; }
    void Warrior::setEmployer(Noble* employer) { this->employer = employer; }
    void Warrior::setStrength(double newStrength) { strength = newStrength; }
    bool Warrior::runaway(){
        if(!isFreeAgent()){
            cout << name << " flees in terror, abandoning his lord, " <<
                employer->getName() << endl;
            employer->fire(*this);
            this->employer = nullptr;
            return true;
        }
        return false;
    }
    ostream& operator<<(ostream& os, const Warrior& rhs){
        os << rhs.name << ": " << rhs.strength << endl;
        return os;
    }
}
