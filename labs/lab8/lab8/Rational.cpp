//
//  Rational.cpp
//  lab8
//
//  Created by Nahom Molla on 10/26/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include "Rational.hpp"
#include <iostream>
using namespace std;

namespace CS2124 {
    //CONSTRUCTOR
    Rational::Rational(int numerator, int denominator) :
    numerator(numerator), denominator(denominator){
        if (denominator == 0){
            std::cerr << "Invalid rational number!" << std::endl;
            std::exit(1);
        }
        normalize();
    }

    //Qualified
    Rational& Rational::operator+=(const Rational& rhs){
        numerator = numerator * rhs.denominator + denominator * rhs. numerator;
        denominator *= rhs.denominator;
        normalize();
        return *this;
    }
    Rational& Rational::operator++(){
        numerator += denominator;
        normalize();
        return *this;
    }
    Rational Rational::operator++(int){ //dummy
        Rational original = *this;
        ++(*this);
        return original;
    }
    Rational::operator bool() const { return numerator; }

    int Rational::greatestCommonDivisor(int x, int y) const {
        while (y != 0) {
            int temp = x % y;
            x = y;
            y = temp;
        }
        return x;
    }
    void Rational::normalize(){
        int gcf = greatestCommonDivisor(numerator, denominator);
        numerator /= gcf;
        denominator /= gcf;
        arrangeSigns();
    }
    void Rational::arrangeSigns(){
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
    }

    //friends
    ostream& operator<<(ostream& os, const Rational& rhs) {
        os << rhs.numerator << '/' << rhs.denominator;
        return os;
    }
    istream& operator>>(istream& is, Rational& rhs){
        char div;
        is >> rhs.numerator >> div >> rhs.denominator;
        return is;
    }
    bool operator==(const Rational& lhs, const Rational& rhs){
        return (lhs.numerator == rhs.numerator) && (lhs.denominator == rhs.denominator);
    }
    bool operator<(const Rational& lhs, const Rational& rhs){
        return lhs.numerator * rhs.denominator < lhs.denominator * rhs.numerator;
    }

    //nonfriends
    Rational operator+(const Rational& lhs, const Rational& rhs){
        Rational lhsCopy = lhs;
        lhsCopy += rhs;
        return lhsCopy;
    }

    bool operator!=(const Rational& lhs, const Rational& rhs){
        return !(lhs==rhs);
    }

    Rational& operator--(Rational& rhs){
        rhs += Rational(-1);
        return rhs;
    }

    Rational operator--(Rational& lhs, int){
        Rational orignial = lhs;
        --lhs;
        return orignial;
    }

    bool operator>(const Rational& lhs, const Rational& rhs){
        return rhs < lhs;
    }

    bool operator<=(const Rational& lhs, const Rational& rhs){
        return lhs < rhs || lhs == rhs;
    }

    bool operator>=(const Rational& lhs, const Rational& rhs){
        return rhs <= lhs;
    }
}
