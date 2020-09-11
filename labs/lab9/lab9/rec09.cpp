//
//  main.cpp
//  lab9
//
//  Created by Nahom Molla on 11/2/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

// Task 3
class PrintedMaterial {
public:
    PrintedMaterial(unsigned numOfPages) : numberOfPages(numOfPages) {}
    virtual void displayNumPages() const = 0;
private:
    unsigned numberOfPages;
};

void PrintedMaterial::displayNumPages() const {
    cout << numberOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numOfPages) : PrintedMaterial(numOfPages) {}
    void displayNumPages() const override { PrintedMaterial::displayNumPages(); }
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numOfPages) : PrintedMaterial(numOfPages) {}
    void displayNumPages() const override { PrintedMaterial::displayNumPages(); }
};

class TextBook : public Book {
public:
    TextBook(unsigned numOfPages, unsigned numOfIndex) : Book(numOfPages), numOfIndexPages(numOfIndex) {}
    void displayNumPages() const override {
        PrintedMaterial::displayNumPages();
        cout << numOfIndexPages << endl;
    }
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numOfPages) : Book(numOfPages) {}
    void displayNumPages() const override { PrintedMaterial::displayNumPages(); }
};

void displayNumberOfPages(const PrintedMaterial& someMaterial){
    someMaterial.displayNumPages();
}

// tester/modeler code
int main() {
    TextBook t(8, 2);
    Novel n(5);
    Magazine m(3);
    
    vector<PrintedMaterial*> printedMaterials;
    printedMaterials.push_back(&t);
    printedMaterials.push_back(&n);
    printedMaterials.push_back(&m);
    
    for (const PrintedMaterial* somePm : printedMaterials){
        somePm->displayNumPages();
    }
}
