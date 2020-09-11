//
//  rec06.cpp
//  lab6
//
//  Created by Nahom Molla on 10/12/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//
#include <string>
#include <iostream>
using namespace std;

class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
            << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
        : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    // Overload output operator
    friend ostream& operator<<(ostream& os, const Directory& rhs){
        for (size_t i=0; i<rhs.size; ++i){
            os << *rhs.entries[i] << endl;
        }
        return os;
    }

public:
    //default constructor
    Directory() : size(0), capacity(1), entries(new Entry*[1]){}
    
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)    {
            Entry** old = entries;
            entries = new Entry*[2*capacity];
            for (size_t i=0; i<size; ++i){
                entries[i] = old[i];
            }
            delete[] old;
            capacity *= 2;
        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add
    
    unsigned operator[](const string& name) const {
        for (size_t i=0; i<size; ++i){
            if (entries[i]->getName() == name){
                return entries[i]->getPhone();
            }
        }
        cout << name << " not found in directory" << endl;
        return 0;
    }
    
    Directory& operator=(const Directory& toCopy){
        cout << "Assinging..." << endl;
        if (this != &toCopy){
        //free this up, allocate new space on this, assign elements to this, return this
            for (size_t i=0; i<capacity; ++i){
                delete entries[i];
            }
            delete[] entries;
            cout << "Creating new array..." << endl;
            entries = new Entry*[toCopy.capacity];
            capacity = toCopy.capacity;
            size = toCopy.size;
            cout << "Copying each entry..." << endl;
            for (size_t i=0; i<size; ++i){
                entries[i] = new Entry (*toCopy.entries[i]);
            }
        }
        return *this;
    }
    
    Directory(const Directory& toCopy){ //copy constructor
        cout << "Creating a Copy..." << endl;
        size = toCopy.size;
        capacity = toCopy.capacity;
        cout << "Creating new array of Entry pointers..." << endl;
        entries = new Entry*[capacity];
        for(size_t i=0; i<size; ++i){
            cout << "Copying each Entry pointer" << endl;
            entries[i] = new Entry (*toCopy.entries[i]);
        }
    }
    
    ~Directory(){ //destructor
        cout << "Deleting..." << endl;
        cout << "Deleting each entry..." << endl;
        for (size_t i=0; i<size; ++i){
            delete entries[i]; //using capacity delete the entries the array points to
        }
        cout << "Deleting array..." << endl;
        delete[] entries; //delete the array
    }
    
private:
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {
    
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
    
    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;
    
    Directory d2 = d;    // What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d2 << endl;
    
    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";
    
    Directory d3;
    d3 = d2;
    
    // Should display 1592
    cout << d2["Carmack"] << endl;
    cout << d2["Marilyn"] << endl;
} // main
