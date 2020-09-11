//
//  main.cpp updated
//  homework1
//
//  Created by Nahom Molla on 9/19/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


struct Warrior {
    string name;
    int strength;
};

void openStream(ifstream& myStream);
Warrior createWarrior(const string& theName, const string& theStrength);
void battle(Warrior& warriorOne, Warrior& warriorTwo);
void executeLines(ifstream& myStream, vector<Warrior>& myVector);

int main(int argc, const char * argv[]) {
    ifstream myInputStream;
    openStream(myInputStream);
    vector<Warrior> warriors;
    executeLines(myInputStream, warriors);
    return 0;
}

// function that takes in a filename and opens a stream
void openStream(ifstream& myStream){
    myStream.open("warriors.txt");
    if (!myStream){ // checks the stream
        cerr << "File not found.";
        exit(1);
    }
}

// function that creates a warrior object and returns it
Warrior createWarrior(const string& theName, const string& theStrength){
    Warrior myWarrior;
    myWarrior.name = theName;
    myWarrior.strength = stoi(theStrength);
    return myWarrior;
}

// function that takes two warriors and makes them fight
void battle(Warrior& warriorOne, Warrior& warriorTwo){
    cout << warriorOne.name <<" battles " << warriorTwo.name << endl;
    if (warriorOne.strength > warriorTwo.strength){
        if (warriorTwo.strength == 0){ // if fighter two has no strength
            cout << "He's dead, " << warriorOne.name << endl;
        }
        else { // fighter two dies
            warriorOne.strength = warriorOne.strength - warriorTwo.strength;
            warriorTwo.strength = 0;
            cout << warriorOne.name <<" defeats " << warriorTwo.name << endl;
        }
    }
    else if (warriorOne.strength < warriorTwo.strength){
        if (warriorOne.strength == 0){ // if fighter one has no strength
            cout << "He's dead, " << warriorTwo.name << endl;
        }
        else { // fighter one dies
            warriorTwo.strength = warriorTwo.strength - warriorOne.strength;
            warriorOne.strength = 0;
            cout << warriorTwo.name <<" defeats " << warriorOne.name << endl;
        }
    }
    else { // if both fighters have equal strength
        if (warriorOne.strength == 0){ // if both fighters are already dead
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else { // both fighters die
            warriorOne.strength = 0;
            warriorTwo.strength = 0;
            cout << "Mutual Annihilation: " << warriorOne.name << " and " << warriorTwo.name
            << " die at each other's hands" << endl;
        }
    }
}

// function that reads from the file and executes the commands
void executeLines(ifstream& myStream, vector<Warrior>& myWarriors){
    string description;
    string tokenOne;
    string tokenTwo;
    Warrior myWarrior;
    while (myStream >> description){
        if (description == "Warrior"){ // a Warrior object is created
            myStream >> tokenOne >> tokenTwo;
            myWarrior = createWarrior(tokenOne, tokenTwo);
            myWarriors.push_back(myWarrior);
        }
        else if (description == "Battle"){ // fighter one battles fighter two
            myStream >> tokenOne >> tokenTwo;
            size_t i=0;
            size_t j=myWarriors.size()-1;
            while(i < myWarriors.size() && j >= 0){ // making sure the loop runs until it finds exactly 2 fighters
                if(myWarriors[i].name != tokenOne){
                    ++i;
                }
                if(myWarriors[j].name != tokenTwo){
                    --j;
                }
                if ((myWarriors[i].name == tokenOne) && (myWarriors[j].name == tokenTwo)){
                    battle(myWarriors[i], myWarriors[j]);
                    break;
                }
            }
        }
        else { // if (description == "Status"); print out the warriors' names and strengths
            cout << "There are: " << myWarriors.size() << " warriors" << endl;
            for (const Warrior& warrior : myWarriors){
                cout << "Warrior: " << warrior.name << ", Strength: " << warrior.strength << endl;
            }
        }
    }
    myStream.close();
}
