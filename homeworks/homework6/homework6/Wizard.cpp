//
//  Wizard.cpp
//  homework6
//
//  Created by Nahom Molla on 11/8/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include "Wizard.hpp"
using namespace std;

namespace WarriorCraft {
    Wizard::Wizard(const string& name, double strength) : Protector(name, strength) {}
    void Wizard::attack() const { cout << "POOF!" << endl; }
}
