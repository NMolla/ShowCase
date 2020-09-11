/*
//
//  hw03.cpp
//  homework3
//
//  Created by Nahom Molla on 10/1/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Warrior {
public:
    Warrior(const string& theName, double theStrength) :
    name(theName), strength(theStrength){}
    
    const string& getName() const {
        return name;
    }
    double getStrength() const {
        return strength;
    }
    void setStrength(double newStrength) {
        strength = newStrength;
    }
    bool isFreeAgent() const {
        return free;
    }
    bool hire() {
        if(free == true){
            free = false;
            return true;
        }
        return false;
    }
    void fire(){
        free = true;
    }
    
private:
    string name;
    double strength;
    bool free=true;
};

class Noble {
public:
    Noble(const string& theName) : name(theName){}
    
    bool hire(Warrior& myWarrior){
        if (alive && myWarrior.isFreeAgent()){
            myWarrior.hire();
            army.push_back(&myWarrior);
            return true;
        }
        return false;
    }
    bool fire(Warrior& myWarrior){
        if (alive){
            for (size_t i=0; i<army.size(); ++i){
                //if (army[i]->getName() == myWarrior.getName()){
                if (army[i] == &myWarrior){
                    army[i]->fire();
                    army[i] = nullptr;
                    ++amountOfNulls;
                    cout << myWarrior.getName() << ", you're fired! --" << name << endl;
                    return true;
                }
            }
        }
        return false;
    }
    void battle(Noble& myNoble){
        cout << name << " battles " << myNoble.name << endl;
        if (this->alive && myNoble.alive){ //both nobles are alive
            double strengthOne=this->armyStrength(), strengthTwo=myNoble.armyStrength();
            if (strengthOne > strengthTwo){ //ArmyOne is stronger
                cout << name << " defeats " << myNoble.name << endl;
                double ratioOfStrengths = strengthTwo/strengthOne; //amount to decrease strengthOne by
                for (size_t i=0; i<this->army.size(); ++i){
                    if (this->army[i]){ // != nullptr
                        this->army[i]->setStrength((strengthOne-ratioOfStrengths));
                    }
                }
                myNoble.kill();
            }
            else if(strengthOne < strengthTwo){ //ArmyTwo is stronger
                cout << myNoble.name << " defeats " << name << endl;
                double ratioOfStrengths = strengthOne/strengthTwo; //amount to decrease strengthTwo by
                for (size_t i=0; i<myNoble.army.size(); ++i){
                    if (myNoble.army[i]){ // != nullptr
                        myNoble.army[i]->setStrength(strengthTwo-ratioOfStrengths);
                    }
                }
                kill();
            }
            else { //Armies have same strength
                this->kill();
                myNoble.kill();
                cout << "Mutual Annihalation: " << name << " and " << myNoble.name <<
                " die at each other's hands" << endl;
            }
        }
        else if(this->alive){ //Only NobleOne is alive
            cout << "He's dead, " << this->name << endl;
        }
        else if(myNoble.alive){ //Only NobleTwo is alive
            cout << "He's dead, " << myNoble.name << endl;
        }
        else { //both nobles are dead
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
    }
    void display() const {
        cout << name << " has an army of " << army.size()-amountOfNulls << endl;
        for (size_t i=0; i<army.size(); ++i){
            if (army[i]){
                cout << "\t" << army[i]->getName() << ": " << army[i]->getStrength() << endl;
            }
        }
    }
    
private:
    string name;
    vector<Warrior*> army;
    bool alive=true;
    int amountOfNulls=0;
    void kill(){ // a method that sets the fields accordingly when a Noble dies
        alive = false;
        for (size_t i=0; i<army.size(); ++i){
            if (army[i]){
                army[i]->setStrength(0);
            }
        }
    }
    double armyStrength() const { //returns the strength of a Noble's army
        double armyStrength=0;
        for (size_t i=0; i<army.size(); ++i){
            if (army[i]){ //!=nullptr
                armyStrength += army[i]->getStrength();
            }
        }
        
        return armyStrength;
    }
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
    
    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();
    
    art.fire(cheetah);
    art.display();
    
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
}
*/
