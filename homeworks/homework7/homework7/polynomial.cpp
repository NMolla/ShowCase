//
//  polynomial.cpp
//  homework7
//
//  Created by Nahom Molla on 12/2/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include "polynomial.hpp"
#include <cmath>
using namespace std;

//public
Polynomial::Polynomial() : degree(0) {
    listAddHead(terms, 0);
}
Polynomial::Polynomial(vector<int> v) : degree(v.size()-1) {
    for (int i : v){
        listAddHead(terms, i);
    }
}
Polynomial::Polynomial(const Polynomial& rhs) : degree(rhs.degree) {
    terms = listDuplicateR(rhs.terms);
}
Polynomial& Polynomial::operator=(const Polynomial& rhs){
    if (this != &rhs){
        listClear(terms);
        terms = listDuplicateR(rhs.terms);
        degree = rhs.degree;
    }
    return *this;
}
Polynomial::~Polynomial(){
    listClear(terms);
}
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    Node* cursorOne = terms;
    Node* cursorTwo = rhs.terms;
    if (degree >= rhs.degree){
        while (cursorTwo){
            cursorOne->data += cursorTwo->data;
            cursorOne = cursorOne->next;
            cursorTwo = cursorTwo->next;
        }
    }
    else {
        while (cursorOne) {
            cursorOne->data += cursorTwo->data;
            cursorOne = cursorOne->next;
            cursorTwo = cursorTwo->next;
        }
        while (cursorTwo) {
            listAddTail(terms, cursorTwo->data);
            cursorTwo = cursorTwo->next;
        }
    }
    return *this;
}
int Polynomial::evaluate(int x) const {
    int val=0;
    Node* cursor = terms;
    for (size_t i=0; i<degree+1; ++i){
        val += cursor->data * pow(x, i);
        cursor = cursor->next;
    }
    return val;
}

//private
string Polynomial::createStringR(Node* cursor, size_t exponent) const {
    if (exponent == degree){
        if (!exponent) return to_string(cursor->data); // x^0
        else if (!cursor->data) return ""; // 0^n
        else if (exponent == 1) { //ax^1
            if (cursor->data == 1) return "x";  //1x^1
            return to_string(cursor->data) + "x"; //bx^1
        }
        return to_string(cursor->data) + "x^" + to_string(exponent); //other cases
    }
    else {
        string res = createStringR(cursor->next, exponent+1);
        if (res != ""){
            if (!exponent) return res + " + " + to_string(cursor->data); // x^0
            else if (!cursor->data) return res; // 0^n
            else if (exponent == 1) { //ax^1
                if (cursor->data == 1) return res + " + x";  //1x^1
                return res + " + " + to_string(cursor->data) + "x"; //bx^1
            }
            return res + " + " + to_string(cursor->data) +
                "x^" + to_string(exponent); //other cases
        }
        if (!exponent) return to_string(cursor->data); // x^0
        else if (!cursor->data) return "0"; // 0^n
        else if (exponent == 1) { //ax^1
            if (cursor->data == 1) return "x";  //1x^1
            return to_string(cursor->data) + "x"; //bx^1
        }
        return to_string(cursor->data) + "x^" + to_string(exponent); //other cases
    }
}

string Polynomial::createString() const {
    string result = "";
    Node* cursor = terms;
    if (cursor->data || !degree) result = to_string(cursor->data);
    for (size_t i=1; i<degree+1; ++i){
        if (cursor->data) {
            if (cursor->data == 1) {
                if (i == 1) { result = "x + " + result; }
                else { result = to_string(cursor->data) +
                    "x + " + result; }
            }
            else {
                if (i == 1) { result = to_string(cursor->data)
                    + "x + " + result; }
                else { result = to_string(cursor->data) +
                    "x^" + to_string(i) + " + " + result; }
            }
        }
        cursor = cursor->next;
    }
    return result;
}

//functions
ostream& operator<<(ostream& os, const Polynomial& rhs){
    os << rhs.createStringR(rhs.terms, 0);
    //os << rhs.createString();
    return os;
}
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial p(lhs);
    p += rhs;
    return p;
}
bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    if (lhs.degree != rhs.degree) return false;
    if (lhs.terms->data != rhs.terms->data) return false;
    Node* cursorOne = lhs.terms;
    Node* cursorTwo = rhs.terms;
    while (cursorOne) {
        if (cursorOne->data != cursorTwo->data) return false;
        cursorOne = cursorOne->next;
        cursorTwo = cursorTwo->next;
    }
    return true;
}
bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs == rhs);
}

//Node
//Constructor
Node::Node(int data, Node* next) : data(data), next(next) {}

//Functions
void listClear(Node*& headPtr){
    while (headPtr != nullptr){
        listRemoveHead(headPtr);
    }
}
Node* listDuplicateR(Node* headPtr){
    if (headPtr == nullptr) return nullptr;
    return new Node(headPtr->data, listDuplicateR(headPtr->next));
}
void listDisplay(const Node* headPtr){
    const Node* p = headPtr;
    while (p != nullptr){
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}
int listLength(Node* headPtr){
    const Node* p = headPtr;
    int counter = 0;
    while (p != nullptr){
        ++counter;
        p = p->next;
    }
    return counter;
}
void listAddHead(Node*& headPtr, int data){
    headPtr = new Node(data, headPtr);
}
bool listRemoveHead(Node*& headPtr){
    if (headPtr != nullptr){
        Node* first = headPtr;
        headPtr = headPtr->next;
        delete first;
        return true;
    }
    return false;
}
void listAddTail(Node*& headPtr, int data){
    Node* cursor = headPtr;
    for (size_t i=0; i<listLength(headPtr)-1; ++i){
        cursor = cursor->next;
    }
    cursor->next = new Node(data);
}
bool listRemoveTail(Node*& headPtr){
    int length = listLength(headPtr);
    if (!length) return false;
    if (length == 1){
        delete headPtr;
        headPtr = nullptr;
    }
    else {
        Node* cursor = headPtr;
        for (size_t i=0; i<length-2; ++i){
            cursor = cursor->next;
        }
        delete cursor->next;
        cursor->next = nullptr;
    }
    return true;
}
