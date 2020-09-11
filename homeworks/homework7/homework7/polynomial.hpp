//
//  polynomial.hpp
//  homework7
//
//  Created by Nahom Molla on 12/2/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#ifndef polynomial_hpp
#define polynomial_hpp

#include <iostream>
#include <vector>

struct Node {
    Node(int data, Node* next = nullptr);
    int data;
    Node* next;
};

void listClear(Node*& headPtr);
Node* listDuplicateR(Node* headPtr);
void listDisplay(const Node* headPtr);
int listLength(Node* headPtr);
void listAddHead(Node*& headPtr, int data);
bool listRemoveHead(Node*& headPtr);
void listAddTail(Node*& headPtr, int data);
bool listRemoveTail(Node*& headPtr);

class Polynomial {
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
    std::string createStringR(Node* cursor, std::size_t exponent) const;
    std::string createString() const;
public:
    Polynomial();
    Polynomial(std::vector<int> v);
    Polynomial(const Polynomial& rhs);
    Polynomial& operator=(const Polynomial& rhs);
    ~Polynomial();
    Polynomial& operator+=(const Polynomial& rhs);
    int evaluate(int x) const;
private:
    Node* terms=nullptr;
    size_t degree=0;
};

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
bool operator==(const Polynomial& lhs, const Polynomial& rhs);
bool operator!=(const Polynomial& lhs, const Polynomial& rhs);



#endif /* polynomial_hpp */
