//
//  main.cpp
//  lab14
//
//  Created by Nahom Molla on 12/14/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

struct TNode {
    TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
        : data(data), left(left), right(right) {}
    int data;
    TNode *left, *right;
};

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

void listClear(Node*& headPtr);
bool listRemoveHead(Node*& headPtr);
void listClear2(Node*& headPtr);
void listClearR(Node*& headPtr);
Node* listDuplicate(Node* headPtr);
Node* listDuplicate2(Node* headPtr);
void listDisplay(const Node* headPtr);
int listLength(Node* headPtr);
void listAddHead(Node*& headPtr, int data);

//Task 1
bool evenBits(int n){
    if (n == 0){
        return true;
    }
    bool res = evenBits(n/2);
    if (n % 2 == 0){
        return res;
    }
    else {
        return !res;
    }
}

//Task 2
Node* createListSum(Node* firstHead, Node* secondHead){
    if (!firstHead && !secondHead) return nullptr;
    else if (!secondHead){
        return firstHead;
    }
    else if (!firstHead){
        return secondHead;
    }
    Node* resHead = createListSum(firstHead->next, secondHead->next);
    return new Node(firstHead->data + secondHead->data, resHead);
}

//Task 3
int max(TNode* root) {
    if (!root) {
        cerr << "Invalid Input!\n";
        throw bad_typeid();
    }
    if (!root->left && !root->right){
        return root->data;
    }
    else if (!root->right){
        return std::max(root->data, max(root->left));
    }
    else if(!root->left){
        return std::max(root->data, max(root->right));
    }
    else {
        int maxLeft = max(root->left);
        int maxRight = max(root->right);
        return std::max(root->data, std::max(maxLeft, maxRight));
    }
}

//Task 4
bool palindrome(char* arr, int len){
    if (len <= 1) return true;
    bool res = palindrome(arr+1, len-2);
    return arr[0] == arr[len-1] && res;
}

template <typename A>
bool isPalindrome(A start, A stop){
    --stop;
    while (start != stop){
        if (*start != *stop){
            return false;
        }
        ++start;
        --stop;
    }
    return true;
}

//Task 5
int towers(int n, char start, char target, char spare){
    if (n == 1) {
        return 1;
    }
    int movesOne = towers(n-1, start, spare, target);
    int movesTwo = towers(n-1, spare, target, start);
    return movesOne + movesTwo + 1;
}

//Task 6
void mystery(int n) {
    if (n > 1) {
        cout << 'a';
        mystery(n/2);
        cout << 'b';
        mystery(n/2);
    }
    cout << 'c';
}

int main(int argc, const char * argv[]) {
    /*
    //Task 1
    cout << boolalpha;
    cout << evenBits(3);
    cout << endl;
   
    //Task 2
    Node* lstOne = nullptr;
    for (int i=0; i<10; ++i){
        listAddHead(lstOne, 9-i);
    }
    Node* lstTwo = nullptr;
    for (int i=0; i<6; ++i){
        listAddHead(lstTwo, i);
    }
    Node* lstThree = nullptr;
    for (int i=15; i<21; ++i){
        listAddHead(lstThree, i);
    }
    Node* sum1;
    sum1 = createListSum(lstOne, lstTwo);
    Node* sum2;
    sum2 = createListSum(lstOne, lstThree);
    
    listDisplay(lstOne);
    listDisplay(lstTwo);
    listDisplay(lstThree);
    listDisplay(sum1);
    listDisplay(sum2);
    
    //Task 3
    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    try {
        cout << max(&f) << endl;
    }
    catch (bad_typeid& bti){
        cout << "subset of bad type_id: " << bti.what() << endl;
    }
    //Task 4
    cout << "\nTask 4" << endl;
    char s[] = "raccar";
    if (palindrome(s, 6)) { cout << "Yes!\n"; }
    cout << endl;
    //Task 5
    cout << towers(1, 'a', 'b', 'c') << endl;
    cout << towers(2, 'a', 'b', 'c') << endl;
    cout << towers(3, 'a', 'b', 'c') << endl;
    cout << towers(4, 'a', 'b', 'c') << endl;
    cout << towers(5, 'a', 'b', 'c') << endl;
    cout << towers(6, 'a', 'b', 'c') << endl;
    cout << towers(7, 'a', 'b', 'c') << endl;
    cout << towers(8, 'a', 'b', 'c') << endl;
    cout << towers(9, 'a', 'b', 'c') << endl;
    cout << towers(10, 'a', 'b', 'c') << endl;
     
    //Task 6
    mystery(5);
    cout << endl;
     */
    
    int* arr = new int[3] {1, 2, 3};
    for (size_t i=0; i<3; ++i){
        cout << arr[i] << endl;
    }
}

void listClear(Node*& headPtr) {
    if (headPtr == nullptr) return;
    Node* cur = headPtr;
    Node* next = headPtr->next;
    
    while(next != nullptr) {
        delete cur;
        cur = next;
        next = next->next;
    }
    delete cur;
    headPtr = nullptr;
}

bool listRemoveHead(Node*& headPtr) {
    if (headPtr != nullptr) {
        Node* first = headPtr;
        headPtr = headPtr->next;
        delete first;
        return true;
    }
    return false;
}

void listClear2(Node*& headPtr) {
    while (headPtr != nullptr) {
        listRemoveHead(headPtr);
    }
}

void listClearR(Node*& headPtr) {
    if (headPtr == nullptr) return;
    
    listClearR(headPtr->next);
    delete headPtr;
    headPtr = nullptr;
}

Node* listDuplicate(Node* headPtr) {
    if (headPtr == nullptr) return nullptr;
    // some initialization code
    Node* result = new Node(headPtr->data);
    Node* cursor = headPtr->next;
    Node* last = result;
    
    while (cursor != nullptr) {
        last->next = new Node(cursor->data);
        last = last->next;
        cursor = cursor->next;
    }
    return result;
}

Node* listDuplicate2(Node* headPtr) {
    if (headPtr == nullptr) return nullptr;
    return new Node(headPtr->data, listDuplicate2(headPtr->next));
}

void listDisplay(const Node* headPtr) {
    const Node* p = headPtr;
    while (p != nullptr) {
        //while (p) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

int listLength(Node* headPtr) {
    const Node* p = headPtr;
    int counter = 0;
    while (p != nullptr) {
        ++counter;
        p = p->next;
    }
    return counter;
}

void listAddHead(Node*& headPtr, int data) {
    headPtr = new Node(data, headPtr);
}
