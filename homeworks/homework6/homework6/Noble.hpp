//
//  Noble.hpp
//  homework6
//
//  Created by Nahom Molla on 11/8/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#ifndef Noble_hpp
#define Noble_hpp

#include <iostream>

namespace WarriorCraft {
    class Noble {
    public:
        Noble(const std::string& name);
        
        const std::string& getName() const;
        void battle(Noble& opponent);
        
    private:
        std::string name;
        
        virtual bool isAlive() const = 0;
        virtual double getStrength() const = 0;
        virtual void reduceStrength(double factor) = 0;
        virtual void kill() = 0;
        virtual void fight() const = 0;
    };
}
#endif /* Noble_hpp */
