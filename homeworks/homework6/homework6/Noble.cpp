//
//  Noble.cpp
//  homework6
//
//  Created by Nahom Molla on 11/8/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include "Noble.hpp"
using namespace std;

namespace WarriorCraft {
    Noble::Noble(const string& name) : name(name) {}
    const string& Noble::getName() const { return name; }
    void Noble::battle(Noble& opponent) {
        cout << name << " battles " << opponent.name << endl;
        if (isAlive() && opponent.isAlive()){ //both alive
            fight(); // prints out message if there is one
            opponent.fight();
            if (getStrength() > opponent.getStrength()){ //this is stronger
                cout << name << " defeats " << opponent.name << endl;
                reduceStrength(opponent.getStrength()); //is this correct???
                opponent.kill();
            }
            else if (getStrength() < opponent.getStrength()){ //opponent is stronger
                cout << opponent.name << " defeats " << name << endl;
                opponent.reduceStrength(getStrength());
                kill();
            }
            else { // strength == opponent.strength
                cout << "Mutual Annhialation: " << name << " and " << opponent.name <<
                " die at each other's hands" << endl;
                kill();
                opponent.kill();
            }
        }
        else if(isAlive()){ //this is alive
            cout << "He's dead, " << name << endl;
        }
        else if(opponent.isAlive()){ //opponent is alive
            cout << "He's dead, " << opponent.name << endl;
        }
        else { //both are not alive
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
    }
}
