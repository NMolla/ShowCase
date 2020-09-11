//
//  Warrior.hpp
//  homework6
//
//  Created by Nahom Molla on 11/8/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#ifndef Warrior_hpp
#define Warrior_hpp

#include "Protector.hpp"

namespace WarriorCraft {
    class Warrior : public Protector {
    public:
        Warrior(const std::string& name, double strength);
        void attack() const override; // = 0;
    };
}
#endif /* Warrior_hpp */
