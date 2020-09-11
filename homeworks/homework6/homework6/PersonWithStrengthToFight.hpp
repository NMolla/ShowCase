//
//  PersonWithStrengthToFight.hpp
//  homework6
//
//  Created by Nahom Molla on 11/8/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#ifndef PersonWithStrengthToFight_hpp
#define PersonWithStrengthToFight_hpp

#include <iostream>
#include "Noble.hpp"

namespace WarriorCraft {
    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(const std::string& name, double strength);
        
    private:
        double strength;
        
        bool isAlive() const override;
        double getStrength() const override;
        void kill() override;
        void fight() const override;
        void reduceStrength(double opponentStrength) override;
    };
}
#endif /* PersonWithStrengthToFight_hpp */
