//
//  Archer.cpp
//  homework6
//
//  Created by Nahom Molla on 11/8/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include "Archer.hpp"
using namespace std;

namespace WarriorCraft {
    Archer::Archer(const string& name, double strength) : Warrior(name, strength) {}
    void Archer::attack() const {
        cout << "TWANG! ";
        Warrior::attack();
    }
}
