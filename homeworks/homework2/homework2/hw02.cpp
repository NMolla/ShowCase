//
//  hw02.cpp
//  homework2
//
//  Created by Nahom Molla on 9/25/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Warrior {
    // overload the output operator for Warrior class
    friend ostream& operator<<(ostream& os, const Warrior& rhs){
        os << "Warrior: " << rhs.name << ", " << rhs.weapon;
        return os;
    }
    
    class Weapon{
        // overload the output operator for Weapon class
        friend ostream& operator<<(ostream& os, const Weapon& rhs){
            os << "weapon: " << rhs.name << ", " << rhs.strength;
            return os;
        }
    public:
        Weapon(const string& theName, int theStrength) :
            name(theName), strength(theStrength){}
        
        int getStrength() const { // returns the strength value of the Weapon class
            return strength;
        }
        void setStrength(int newStrength){ // modifies the value of the strength variable
            strength = newStrength;
        }
    private:
        string name;
        int strength;
    };
    
public:
    Warrior(const string& theNameOne, const string& theNameTwo, int theStrength) :
        name(theNameOne), weapon(theNameTwo, theStrength){}
    
    const string& getName() const { // returns the name of the Warrior class
        return name;
    }
    int getStrength() const { // returns the strength value of the Weapon class
        return weapon.getStrength();
    }
    void setStrength(int newStrength){ // modifies the strength value of Weapon class
        weapon.setStrength(newStrength);
    }
    
private:
    string name;
    Weapon weapon;
};

void openStream(ifstream& myStream);
void executeLines(ifstream& myStream);
void battle(Warrior& warriorOne, Warrior& warriorTwo);

int main(int argc, const char * argv[]) {
    ifstream myStream;
    openStream(myStream);
    executeLines(myStream);
}

void openStream(ifstream& myStream){
    myStream.open("warriors.txt");
    if (!myStream){
        cerr << "File not found" << endl;
        exit(1);
    }
}

void battle(Warrior& warriorOne, Warrior& warriorTwo){
    cout << warriorOne.getName() << " battles " << warriorTwo.getName() << endl;
    if (warriorOne.getStrength() > warriorTwo.getStrength()){
        if (warriorTwo.getStrength() == 0){ // warriorTwo already dead
            cout << "He's dead, " << warriorOne.getName() << endl;
        }
        else { //both are alive
            warriorOne.setStrength(warriorOne.getStrength()-warriorTwo.getStrength());
            warriorTwo.setStrength(0);
            cout << warriorOne.getName() << " defeats " << warriorTwo.getName() << endl;
        }
    }
    else if (warriorTwo.getStrength() > warriorOne.getStrength()){
        if (warriorOne.getStrength() == 0){ // warriorOne already dead
            cout << "He's dead, " << warriorTwo.getName() << endl;
        }
        else { //both are alive
            warriorTwo.setStrength(warriorTwo.getStrength()-warriorOne.getStrength());
            warriorOne.setStrength(0);
            cout << warriorTwo.getName() << " defeats " << warriorOne.getName() << endl;
        }
    }
    else { // strengths are equal
        if (warriorOne.getStrength() == 0){ // warriors are dead
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else { // warriors are alive
            warriorOne.setStrength(0);
            warriorTwo.setStrength(0);
            cout << "Mutual Annihilation: " << warriorOne.getName() << " and "
                << warriorTwo.getName() << " die at each other's hands" << endl;
        }
    }
}

void executeLines(ifstream& myStream){ // takes in a stream of commands and executes the lines
    string description;
    string tokenOne;
    string tokenTwo;
    int tokenThree;
    vector<Warrior> warriors;
    while (myStream >> description){
        if (description == "Warrior"){
            myStream >> tokenOne >> tokenTwo >> tokenThree;
            Warrior myWarrior(tokenOne, tokenTwo, tokenThree);
            warriors.push_back(myWarrior);
        }
        else if (description == "Battle"){
            myStream >> tokenOne >> tokenTwo;
            size_t i=0;
            size_t j=warriors.size()-1;
            while (i<warriors.size() && j>=0){
                if (warriors[i].getName() != tokenOne){
                    ++i;
                }
                if (warriors[j].getName() != tokenTwo){
                    --j;
                }
                if ((warriors[i].getName() == tokenOne) &&
                    (warriors[j].getName() == tokenTwo)){
                    battle(warriors[i], warriors[j]);
                    break;
                }
            }
        }
        else { //description == "Status"
            cout << "There are: " << warriors.size() << " warriors" << endl;
            for (const Warrior& someWarrior : warriors){
                cout << someWarrior << endl;
            }
        }
    }
}

