//
//  main.cpp
//  lab10
//
//  Created by Nahom Molla on 11/9/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//
/*
#include <iostream>
#include <vector>
using namespace std;

class Instrument {
public:
    virtual void makeSound() const = 0;
private:
};

void Instrument::makeSound() const { cout << "To make a sound... "; }

class Brass : public Instrument {
public:
    Brass(int size) : size(size) {}
    void makeSound() const;
private:
    unsigned size;
};
void Brass::makeSound() const {
    Instrument::makeSound();
    cout << "blow on a mouthpiece of size " << size << endl;
}

class String : public Instrument {
public:
    String(int pitch) : pitch(pitch) {}
    void makeSound() const;
private:
    unsigned pitch;
};
void String::makeSound() const {
    Instrument::makeSound();
    cout << "bow a string with pitch " << pitch << endl;
}

class Percussion : public Instrument {
public:
    void makeSound() const;
private:
};
void Percussion::makeSound() const {
    Instrument::makeSound();
    cout << "hit me!" << endl;
}

class Trumpet : public Brass {
public:
    Trumpet(int size) : Brass(size) {}
};
class Trombone : public Brass {
public:
    Trombone(int size) : Brass(size) {}
};

class Violin : public String {
public:
    Violin(int pitch) : String(pitch) {}
};
class Cello : public String {
public:
    Cello(int pitch) : String(pitch) {}
};

class Drum : public Percussion {
public:
};
class Cymbal : public Percussion {
public:
};


class MILL {
public:
    void receiveInstr(Instrument& instrumentToReceive){
        bool added=false;
        for (size_t i=0; i<library.size(); ++i){
            if (!library[i]){
                library[i] = &instrumentToReceive;
                added = true;
                break;
            }
        }
        if (!added){
            library.push_back(&instrumentToReceive);
        }
    }
    Instrument* loanOut() {
        for (size_t i=0; i < library.size(); ++i){
            if (library[i]) {
                Instrument* result = library[i];
                library[i] = nullptr;
                return result;
            }
        }
        return nullptr;
    }
    void dailyTestPlay() const {
        for (Instrument* instrument : library){
            if (instrument) instrument->makeSound();
        }
    }
    
private:
    vector<Instrument*> library;
};


class Musician {
public:
    Musician() : instr(nullptr) {}
    
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }
    
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }
    
    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }
    
private:
    Instrument* instr;
};


// PART ONE
int main() {
    
    cout << "Define some instruments ------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
    
    // use the debugger to look at the mill
    cout << "Define the MILL --------------------------------------------\n";
    MILL mill;
    
    cout << "Put the instruments into the MILL --------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    
    cout << "Daily test -------------------------------------------------\n";
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
    
    cout << "Define some Musicians---------------------------------------\n";
    Musician harpo;
    Musician groucho;
    
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();
    cout << endl;
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    
    cout << endl << endl;
    
    groucho.testPlay();
    cout << endl;
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    harpo.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    
    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    
    // fifth
    mill.receiveInstr(*groucho.giveBackInstr());
    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    
    
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
    
    cout << endl;
}
*/

#include <iostream>
#include <vector>
using namespace std;

class Instrument {
public:
    virtual void makeSound() const = 0;
    virtual void play() const = 0;
private:
};

void Instrument::makeSound() const { cout << "To make a sound... "; }

class Brass : public Instrument {
public:
    Brass(int size) : size(size) {}
    void makeSound() const {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << size << endl;
    }
private:
    unsigned size;
};

class String : public Instrument {
public:
    String(int pitch) : pitch(pitch) {}
    void makeSound() const {
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
private:
    unsigned pitch;
};

class Percussion : public Instrument {
public:
    void makeSound() const {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
private:
};

class Trumpet : public Brass {
public:
    Trumpet(int size) : Brass(size) {}
    void play() const override { cout << "Toot"; }
};
class Trombone : public Brass {
public:
    Trombone(int size) : Brass(size) {}
    void play() const override { cout << "Blat"; }
};

class Violin : public String {
public:
    Violin(int pitch) : String(pitch) {}
    void play() const override { cout << "Screech"; }
};
class Cello : public String {
public:
    Cello(int pitch) : String(pitch) {}
    void play() const override { cout << "Squawk"; }
};

class Drum : public Percussion {
public:
    void play() const override { cout << "Boom"; }
};
class Cymbal : public Percussion {
public:
    void play() const override { cout << "Crash"; }
};


class MILL {
public:
    void receiveInstr(Instrument& instrumentToReceive){
        for (size_t i=0; i<library.size(); ++i){
            if (!library[i]){
                library[i] = &instrumentToReceive;
                return;
            }
        }
        library.push_back(&instrumentToReceive);
    }
    Instrument* loanOut() {
        for (size_t i=0; i < library.size(); ++i){
            if (library[i]) {
                Instrument* result = library[i];
                library[i] = nullptr;
                return result;
            }
        }
        return nullptr;
    }
    void dailyTestPlay() const {
        for (Instrument* instrument : library){
            if (instrument) instrument->makeSound();
        }
    }
    
private:
    vector<Instrument*> library;
};


class Musician {
public:
    Musician() : instr(nullptr) {}
    
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }
    
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }
    
    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }
    
    void play() const {
        if (instr) instr->play();
    }
    
private:
    Instrument* instr;
};


class Orchestra {
public:
    void addPlayer(Musician& player){
        band.push_back(&player);
    }
    void play(){
        for (Musician* player : band){
            player->play(); //the normal way
        }
        cout << endl;
    }
private:
    vector<Musician*> band;
};

int main() {
    // The initialization phase
    
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);
    
    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    
    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;
    
    Orchestra orch;
    
    // THE SCENARIO
    
    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);
    
    //The orchestra performs
    cout << "orch performs\n";
    orch.play();
    
    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);
    
    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());
    
    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);
    
    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());
    
    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);
    
    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());
    
    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    
    //Ralph joins the orchestra.
    orch.addPlayer(ralph);
    
    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());
    
    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());
    
    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    
    //Morgan joins the orchestra.
    orch.addPlayer(morgan);
    
    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    
} // main
