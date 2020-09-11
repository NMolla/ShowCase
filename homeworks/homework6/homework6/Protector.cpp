//
//  Protector.cpp
//  homework6
//
//  Created by Nahom Molla on 11/8/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include "Protector.hpp"
#include "Lord.hpp"
using namespace std;

namespace WarriorCraft {
    Protector::Protector(const string& name, double strength) :
    name(name), strength(strength) {}
    const string& Protector::getName() const { return name; }
    double Protector::getStrength() const { return strength; }
    bool Protector::isEmployed() const { return employer; }
    void Protector::setEmployer(Lord* employer) { this->employer = employer; }
    void Protector::setStrength(double newStrength) { strength = newStrength; }
    bool Protector::runaway(){
        if (employer){
            string employerName = employer->getName();
            if (employer->release(*this)) {
                cout << name << " flees in terror, abandoning his lord, " <<
                employerName << endl;
                return true;
            }
        }
        return false;
    }
    Lord* Protector::getEmployer() const { return employer; }
}
