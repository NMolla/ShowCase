//
//  main.cpp
//  lab02
//
//  Created by Nahom Molla on 9/14/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Molecule{
    vector<string> scientificNames;
    int carbonAtoms;
    int hydrogenAtoms;
};

void openStream(ifstream& a_File);
void insertIntoVector(ifstream& myStream, vector<Molecule>& myVector);
void sortVector(vector<Molecule>& myVector);
void displayVector(const vector<Molecule>& myVector);


int main(int argc, const char * argv[]) {
    ifstream myFile;
    vector<Molecule> chemicals;
    openStream(myFile);
    insertIntoVector(myFile, chemicals);
    sortVector(chemicals);
    displayVector(chemicals);
    
    
    return 0;
}

void openStream(ifstream& a_File){
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    a_File.open(filename);
    while(!a_File){
        a_File.clear();
        cerr << "failed to open " << filename << endl;
        cout << "Enter correct filename: ";
        cin >> filename;
        a_File.open(filename);
    }
}


void insertIntoVector(ifstream& myStream, vector<Molecule>& myVector){
    // create a Molecule struct and push_back to the vector
    string name;
    char carbon;
    char hydrogen;
    int numCarbon;
    int numHydrogen;
    while (myStream >> name >> carbon >> numCarbon >> hydrogen >> numHydrogen){
        bool duplicate = false;
        for (Molecule& molecule : myVector){
            if (molecule.carbonAtoms == numCarbon && molecule.hydrogenAtoms == numHydrogen){
                molecule.scientificNames.push_back(name);
                duplicate = true;
                break;
            }
        }
        if (!duplicate){
            Molecule someMolecule;
            someMolecule.scientificNames.push_back(name);
            someMolecule.carbonAtoms = numCarbon;
            someMolecule.hydrogenAtoms = numHydrogen;
            myVector.push_back(someMolecule);
        }
    }
    myStream.close();
}

void sortVector(vector<Molecule>& myVector){
    for (size_t i=0; i<myVector.size(); ++i){
        for (size_t j=0; j<(myVector.size()-1); ++j){
            if (myVector[j].carbonAtoms > myVector[j+1].carbonAtoms
                || (myVector[j].carbonAtoms == myVector[j+1].carbonAtoms
                    && myVector[j].hydrogenAtoms > myVector[j+1].hydrogenAtoms)){
                    Molecule tmp = myVector[j];
                    myVector[j] = myVector[j+1];
                    myVector[j+1] = tmp;
            }
        }
    }
}

void displayVector(const vector<Molecule>& myVector){
    for (const Molecule& someMolecule : myVector){
        cout << 'C' << someMolecule.carbonAtoms << 'H' << someMolecule.hydrogenAtoms;
        for (const string& name : someMolecule.scientificNames){
            cout << ' ' << name;
        }
        cout << endl;
    }
    
}
