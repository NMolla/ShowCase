//
//  hw05.cpp
//  homework5
//
//  Created by Nahom Molla on 10/17/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Noble;

class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& rhs);
public:
    Warrior(const string& name, double strength);
    const string& getName() const;
    double getStrength() const;
    void setEmployer(Noble* employer);
    bool isFreeAgent() const;
    void setStrength(double newStrength);
    bool runaway();
private:
    string name;
    double strength=0;
    Noble* employer=nullptr;
};

class Noble {
    friend ostream& operator<<(ostream& os, const Noble& rhs);
public:
    Noble(const string& name);
    bool hire(Warrior& warriorToHire);
    bool fire(Warrior& warriorToFire);
    void battle(Noble& opponent);
private:
    string name;
    bool alive=true;
    vector<Warrior*> army;
    double getArmyStrength() const;
    void removeNullptr();
    void kill();
    void subtractStrength(double strengthRatio);
};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    
    cheetah.runaway();
    cout << art << endl;
    
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
}

//Noble
Noble::Noble(const string& name) : name(name) {}
bool Noble::hire(Warrior& warriorToHire){
    if (warriorToHire.isFreeAgent()){
        warriorToHire.setEmployer(this);
        army.push_back(&warriorToHire);
        return true;
    }
    return false;
}

bool Noble::fire(Warrior& warriorToFire){
    for (size_t i=0; i<army.size(); ++i){
        if (army[i] == &warriorToFire){
            army[i] = nullptr;
            removeNullptr();
            return true;
        }
    }
    return false;
}

void Noble::battle(Noble& opponent){
    cout << name << " battles " << opponent.name << endl;
    if (this->alive && opponent.alive){
        if (this->getArmyStrength() > opponent.getArmyStrength()){
            cout << name << " defeats " << opponent.name << endl;
            this->subtractStrength(1-(opponent.army.size()/this->army.size()));
            opponent.kill();
        }
        else if(this->getArmyStrength() < opponent.getArmyStrength()){
            cout << opponent.name << " defeats " << name << endl;
            opponent.subtractStrength(1-(this->army.size()/opponent.army.size()));
            kill();
        }
        else {
            this->kill();
            opponent.kill();
            cout << "Mutual Annihalation: " << name << " and " << opponent.name <<
            " die at each other's hands" << endl;
        }
    }
    else if(this->alive){
        cout << "He's dead, " << this->name << endl;
    }
    else if(opponent.alive){
        cout << "He's dead, " << opponent.name << endl;
    }
    else {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
}

void Noble::removeNullptr(){
    bool start=false;
    for(size_t i=0; i<army.size()-1; ++i){
        if (army[i] == nullptr){
            start=true;
        }
        if(start){
            army[i] = army[i+1];
        }
    }
    army.pop_back();
}

void Noble::kill(){
    alive = false;
    for (size_t i=0; i<army.size(); ++i){
        army[i]->setStrength(0);
    }
}

void Noble::subtractStrength(double strengthRatio){
    for (Warrior* someWarrior : army){
        someWarrior->setStrength(someWarrior->getStrength() * strengthRatio);
    }
}

double Noble::getArmyStrength() const {
    double armyStrength=0;
    for (size_t i=0; i<army.size(); ++i){
        armyStrength += army[i]->getStrength();
    }
    return armyStrength;
}

ostream& operator<<(ostream& os, const Noble& rhs){
    os << rhs.name << " has an army of " << rhs.army.size() << endl;
    for (Warrior* someWarrior : rhs.army){
        os << "\t" << *someWarrior;
    }
    return os;
}


//Warrior
Warrior::Warrior(const string& name, double strength) : name(name), strength(strength) {}
const string& Warrior::getName() const { return name; }
double Warrior::getStrength() const { return strength; }
bool Warrior::isFreeAgent() const { return employer == nullptr; }
void Warrior::setEmployer(Noble* employer) { this->employer = employer; }
void Warrior::setStrength(double newStrength) { strength = newStrength; }
bool Warrior::runaway(){
    if(!isFreeAgent()){
        cout << name << " just ran away!" << endl;
        employer->fire(*this);
        this->employer = nullptr;
        return true;
    }
    return false;
}
ostream& operator<<(ostream& os, const Warrior& rhs){
    os << rhs.name << ": " << rhs.strength << endl;
    return os;
}
