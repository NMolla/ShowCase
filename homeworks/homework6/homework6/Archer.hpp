//
//  Archer.hpp
//  homework6
//
//  Created by Nahom Molla on 11/8/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#ifndef Archer_hpp
#define Archer_hpp

#include "Warrior.hpp"

namespace WarriorCraft {
    class Archer : public Warrior {
    public:
        Archer(const std::string& name, double strength);
        void attack() const override;
    };
}
#endif /* Archer_hpp */
