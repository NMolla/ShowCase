//
//  Protector.hpp
//  homework6
//
//  Created by Nahom Molla on 11/8/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#ifndef Protector_hpp
#define Protector_hpp

#include <iostream>

namespace WarriorCraft {
    class Lord;
    
    class Protector {
    public:
        Protector(const std::string& name, double strength);
        
        const std::string& getName() const;
        double getStrength() const;
        bool isEmployed() const;
        void setEmployer(Lord* employer);
        void setStrength(double newStrength);
        bool runaway();
        virtual void attack() const = 0;
        
    protected:
        Lord* getEmployer() const;
    private:
        std::string name;
        double strength;
        Lord* employer=nullptr;
    };
}
#endif /* Protector_hpp */
