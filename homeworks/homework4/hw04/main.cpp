//
//  main.cpp
//  homework4
//
//  Created by Nahom Molla on 10/8/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& rhs){
        os << rhs.name << ": " << rhs.strength;
        return os;
    }
public:
    Warrior(const string& name, double strength) :
    name(name), strength(strength){}
    
    const string& getName() const {
        return name;
    }
    double getStrength() const {
        return strength;
    }
    void setStrength(double newStrength){
        strength = newStrength;
    }
    void fired(){
        freeAgent=true;
    }
    void hired(){
        freeAgent=false;
    }
    bool isFreeAgent() const {
        return freeAgent;
    }
    
private:
    string name;
    double strength=0;
    bool freeAgent=true;
};


class Noble{
    friend ostream& operator<<(ostream& os, const Noble& rhs){
        os << rhs.name << " has an army of " << rhs.army.size() << endl;
        for(size_t i=0; i<rhs.army.size(); ++i){
            os << "\t" << *rhs.army[i] << endl;
        }
        return os;
    }
public:
    Noble(const string& name) : name(name){}
    
    const string& getName() const {
        return name;
    }
    bool hire(Warrior* myWarrior){
        if (myWarrior->isFreeAgent()){
            myWarrior->hired();
            army.push_back(myWarrior);
            return true;
        }
        return false;
    }
    bool fire(const string& myWarriorName){
        for (size_t i=0; i<army.size(); ++i){
            if (army[i]->getName() == myWarriorName){
                army[i]->fired();
                army[i] = nullptr;
                removeNullptr();
                return true;
            }
        }
        return false;
    }
    
    void battle(Noble* opponent){
        if (this->alive && opponent->alive){
            if (this->getArmyStrength() > opponent->getArmyStrength()){
                cout << this->name << " defeats " << opponent->name << endl;
                this->subtractStrength(1 - (opponent->getArmyStrength() / this->getArmyStrength()));
                opponent->kill();
            }
            else if (this->getArmyStrength() < opponent->getArmyStrength()){
                cout << opponent->name << " defeats " << this->name << endl;
                opponent->subtractStrength(1 - (this->getArmyStrength() / opponent->getArmyStrength()));
                this->kill();
            }
            else { //both armies have the same strength
                cout << "Mutual Annihalation: " << this->name << " and " <<
                    opponent->name << " die at each other's hands" << endl;
                this->kill();
                opponent->kill();
            }
        }
        else if (this->alive){
            cout << "He's dead, " << this->name << endl;
        }
        else if (opponent->alive){
            cout << "He's dead, " << opponent->name << endl;
        }
        else { //both are not alive
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        
    }
    
    const vector<Warrior*>& getArmy() const {
        return army;
    }
    /* Destructor
    ~Noble(){
        for (Warrior* warrior : army){
            delete warrior;
        }
    }
    */
private:
    string name;
    bool alive=true;
    vector<Warrior*> army;
    
    double getArmyStrength() const {
        double armyStrength=0;
        for (size_t i=0; i<army.size(); ++i){
            armyStrength += army[i]->getStrength();
        }
        return armyStrength;
    }
    
    void kill(){ // a method that sets the fields accordingly when a Noble dies
        alive = false;
        for (size_t i=0; i<army.size(); ++i){
            army[i]->setStrength(0);
        }
    }
    
    void subtractStrength(double strengthRatio){
        for (Warrior* someWarrior : army){
            someWarrior->setStrength(someWarrior->getStrength() * strengthRatio);
        }
    }
    
    void removeNullptr(){
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
};

void openStream(ifstream& myStream);
void executeLines(ifstream& myCommands);
void createNoble(const string& nobleName, vector<Noble*>& myNobles);
void createWarrior(const string& warriorName, const string& strength,
                   vector<Warrior*>& myWarriors);
void hireWarrior(const string& nobleName, const string& warriorName,
                 vector<Noble*>& myNobles, vector<Warrior*>& myWarriors);
void fireWarrior(const string& nobleName, const string& warriorName,
                 vector<Noble*>& myNobles);
void fight(const string& nobleOneName, const string& nobleTwoName,
           vector<Noble*>& myNobles);
void printStatus(vector<Noble*>& myNobles, vector<Warrior*>& myWarriors);
//void printStatusII(vector<Noble*>& myNobles, vector<Warrior*>& myWarriors);
void clearAll(vector<Noble*>& myNobles, vector<Warrior*>& myWarriors);

int main(int argc, const char * argv[]) {
    ifstream commands;
    openStream(commands);
    executeLines(commands);
}

void executeLines(ifstream& myCommands){
    string description;
    string tokenOne;
    string tokenTwo;
    vector<Warrior*> warriors;
    vector<Noble*> nobles;
    while (myCommands>>description){
        if (description == "Noble"){
            myCommands>>tokenOne;
            createNoble(tokenOne, nobles);
        }
        else if (description == "Warrior"){
            myCommands>>tokenOne>>tokenTwo;
            createWarrior(tokenOne, tokenTwo, warriors);
        }
        else if (description == "Hire"){
            myCommands>>tokenOne>>tokenTwo;
            hireWarrior(tokenOne, tokenTwo, nobles, warriors);
        }
        else if (description == "Fire"){
            myCommands>>tokenOne>>tokenTwo;
            fireWarrior(tokenOne, tokenTwo, nobles);
        }
        else if (description == "Battle"){
            myCommands>>tokenOne>>tokenTwo;
            fight(tokenOne, tokenTwo, nobles);
        }
        else if (description == "Status"){
            printStatus(nobles, warriors);
            //printStatusII(nobles, warriors);
        }
        else { //description == "Clear"
            clearAll(nobles, warriors);
        }
    }
    myCommands.close();
}

void openStream(ifstream& myStream){
    myStream.open("nobleWarriors.txt");
    if (!myStream){
        cerr << "file not found" << endl;
        exit(1);
    }
}

void createNoble(const string& nobleName, vector<Noble*>& myNobles){
    bool exists=false;
    for (const Noble* someNoble : myNobles){
        if (someNoble->getName() == nobleName){
            exists = true;
            break;
        }
    }
    if (!exists){
        myNobles.push_back(new Noble(nobleName));
    }
}

void createWarrior(const string& warriorName, const string& strength,
                   vector<Warrior*>& myWarriors){
    bool exists=false;
    for (const Warrior* someWarrior : myWarriors){
        if (someWarrior->getName()==warriorName){
            exists=true;
            break;
        }
    }
    if (!exists){
        myWarriors.push_back(new Warrior(warriorName, stod(strength)));
    }
}

void hireWarrior(const string& nobleName, const string& warriorName,
                 vector<Noble*>& myNobles, vector<Warrior*>& myWarriors){
    for (Noble* someNoble : myNobles){
        if (someNoble->getName() == nobleName){
            for (Warrior* someWarrior : myWarriors){
                if (someWarrior->getName()==warriorName){
                    someNoble->hire(someWarrior);
                    break;
                }
            }
            break;
        }
    }
}

void fireWarrior(const string& nobleName, const string& warriorName,
                 vector<Noble*>& myNobles){
    for (Noble* someNoble : myNobles){
        if (someNoble->getName() == nobleName){
            someNoble->fire(warriorName);
            cout << "You dont work for me anymore " << warriorName <<
                "! -- " << nobleName << endl;
            break;
        }
    }
}

void fight(const string& nobleOneName, const string& nobleTwoName,
           vector<Noble*>& myNobles){
    size_t i=0, j=myNobles.size()-1;
    while(i < myNobles.size() && j >= 0){
        if (myNobles[i]->getName() != nobleOneName){
            ++i;
        }
        if (myNobles[j]->getName() != nobleTwoName){
            --j;
        }
        if (myNobles[i]->getName() == nobleOneName &&
                myNobles[j]->getName() == nobleTwoName){
            cout << myNobles[i]->getName() << " battles " <<
                myNobles[j]->getName() << endl;
            myNobles[i]->battle(myNobles[j]);
            break;
        }
    }
}

void printStatus(vector<Noble*>& myNobles, vector<Warrior*>& myWarriors){
    cout << "Status\n======\nNobles:" << endl;
    if(myNobles.size()>0){
        for(const Noble* someNoble : myNobles){
            cout << *someNoble;
        }
    }
    else{
        cout << "NONE" << endl;
    }
    cout << "Unemployed Warriors:" << endl;
    if(myWarriors.size()>0){
        bool allEmployed=true;
        for (const Warrior* someWarrior : myWarriors){
            if(someWarrior->isFreeAgent()){
                cout << *someWarrior << endl;
                allEmployed=false;
            }
        }
        if (allEmployed){
            cout << "NONE" << endl;
        }
    }
    else {
        cout << "NONE" << endl;
    }
}

void clearAll(vector<Noble*>& myNobles, vector<Warrior*>& myWarriors){
    for (size_t i=0; i<myWarriors.size(); ++i){
        delete myWarriors[i];
    }
    myWarriors.clear();
    for (size_t j=0; j<myNobles.size(); ++j){
        delete myNobles[j];
    }
    myNobles.clear();
}

/*
 void printStatusII(vector<Noble*>& myNobles, vector<Warrior*>& myWarriors){
 cout << "Status\n======\nNobles:" << endl;
 bool clearedNoblesOut=true;
 for(const Noble* someNoble : myNobles){
 if (someNoble != nullptr){
 cout << someNoble->getName() << " has an army of " <<
 someNoble->getArmy.size() << endl;
 for(size_t i=0; i<someNoble->getArmy().size(); ++i){
 if (someNoble->getArmy()[i] != nullptr){
 cout << "\t" << someNoble->getArmy()[i]->getName() <<
 ": " << someNoble->getArmy()[i]->getStrength() << endl;
 }
 }
 clearedNoblesOut=false;
 }
 }
 if (clearedNoblesOut){
 cout << "NONE" << endl;
 }
 cout << "Unemployed Warriors:" << endl;
 bool allEmployed=true;
 bool clearedWarriorsOut=true;
 for (const Warrior* someWarrior : myWarriors){
 if(someWarrior != nullptr){
 if (someWarrior->isFreeAgent()){
 allEmployed=false;
 cout << someWarrior->getName() << ": " <<
 someWarrior->getStrength() << endl;
 }
 clearedWarriorsOut=false;
 }
 }
 if (allEmployed || clearedWarriorsOut) {
 cout << "NONE" << endl;
 }
 }
 */
