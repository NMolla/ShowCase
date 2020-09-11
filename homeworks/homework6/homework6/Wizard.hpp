//
//  Wizard.hpp
//  homework6
//
//  Created by Nahom Molla on 11/8/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#ifndef Wizard_hpp
#define Wizard_hpp

#include "Protector.hpp"

namespace WarriorCraft {
    class Wizard : public Protector {
    public:
        Wizard(const std::string& name, double strength);
        void attack() const override;
    };
}

#endif /* Wizard_hpp */
