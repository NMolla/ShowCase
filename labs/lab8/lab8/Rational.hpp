//
//  Rational.hpp
//  lab8
//
//  Created by Nahom Molla on 10/26/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#ifndef Rational_hpp
#define Rational_hpp
#include <iostream>

namespace CS2124 {
    class Rational {
        friend std::ostream& operator<<(std::ostream& os, const Rational& rhs);
        friend std::istream& operator>>(std::istream& is, Rational& rhs);
        friend bool operator==(const Rational& lhs, const Rational& rhs);
        friend bool operator<(const Rational& lhs, const Rational& rhs);
    public:
        Rational(int numerator=0, int denominator=1);
        Rational& operator+=(const Rational& rhs);
        Rational& operator++();
        Rational operator++(int);
        explicit operator bool() const;
        
    private:
        int numerator;
        int denominator;
        
        int greatestCommonDivisor(int x, int y) const;
        void normalize();
        void arrangeSigns();
    };

    Rational operator+(const Rational& lhs, const Rational& rhs);
    bool operator!=(const Rational& lhs, const Rational& rhs);
    Rational& operator--(Rational& rhs);
    Rational operator--(Rational& lhs, int);
    bool operator>(const Rational& lhs, const Rational& rhs);
    bool operator<=(const Rational& lhs, const Rational& rhs);
    bool operator>=(const Rational& lhs, const Rational& rhs);
}
#endif /* Rational_hpp */
