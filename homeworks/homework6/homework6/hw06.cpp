//
//  main.cpp
//  homework6
//
//  Created by Nahom Molla on 11/3/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include "Lord.hpp"
#include "PersonWithStrengthToFight.hpp"
#include "Archer.hpp"
#include "Swordsman.hpp"
#include "Wizard.hpp"
using namespace std;
using namespace WarriorCraft;

int main(int argc, const char * argv[]) {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}
