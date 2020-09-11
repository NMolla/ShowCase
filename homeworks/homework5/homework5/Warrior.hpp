//
//  Warrior.hpp
//  homework5
//
//  Created by Nahom Molla on 10/17/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#ifndef Warrior_hpp
#define Warrior_hpp

#include <iostream>
#include <string>

namespace WarriorCraft {
    class Noble;
    class Warrior {
        friend std::ostream& operator<<(std::ostream& os, const Warrior& rhs);
    public:
        Warrior(const std::string& name, double strength);
        const std::string& getName() const;
        double getStrength() const;
        void setEmployer(Noble* employer);
        bool isFreeAgent() const;
        void setStrength(double newStrength);
        bool runaway();
    private:
        std::string name;
        double strength=0;
        Noble* employer=nullptr;
    };
}

#endif /* Warrior_hpp */
