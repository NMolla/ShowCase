//
//  Noble.hpp
//  homework5
//
//  Created by Nahom Molla on 10/17/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#ifndef Noble_hpp
#define Noble_hpp
#include <string>
#include <iostream>
#include <vector>

namespace WarriorCraft {
    class Warrior;
    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);
    public:
        Noble(const std::string& name);
        const std::string& getName() const;
        bool hire(Warrior& warriorToHire);
        bool fire(Warrior& warriorToFire);
        void battle(Noble& opponent);
    private:
        std::string name;
        bool alive=true;
        std::vector<Warrior*> army;
        double getArmyStrength() const;
        void removeNullptr();
        void kill();
        void subtractStrength(double strengthRatio);
    };
}
#endif /* Noble_hpp */
