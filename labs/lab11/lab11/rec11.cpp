//
//  main.cpp
//  lab11
//
//  Created by Nahom Molla on 11/16/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Node to be used a part of linked list
struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

// listInsertHead: adds a data item to the beginning of a [possibly empty] list
void listInsertHead(Node*& headPtr, int entry) {
    headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like.
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listInsertHead(result, vals[index-1]);
    }
    return result;
}

void splice(Node*& listToAdd, Node*& addAfterCurrent){
    Node* nodeAfterCurrent=addAfterCurrent->next;
    addAfterCurrent->next = listToAdd;
    Node* currNode=listToAdd;
    while (currNode->next){
        currNode = currNode->next;
    }
    currNode->next = nodeAfterCurrent;
}

void printList(Node* cursor){
    while (cursor){
        cout << cursor->data << ' ';
        cursor = cursor->next;
    }
    cout << endl;
}

Node* isSublist(Node* mainList, Node* listToSearch){
    while (mainList) {
        if (mainList->data != listToSearch->data){
            mainList = mainList->next;
        }
        else if (mainList->data == listToSearch->data){
            Node* cursor = mainList;
            Node* cursorTwo = listToSearch;
            while (cursorTwo){
                if (cursorTwo->data != cursor->data) {
                    mainList = mainList->next;
                    break;
                }
                else {
                    cursorTwo = cursorTwo->next;
                    cursor = cursor->next;
                }
                if (!cursorTwo){
                    return mainList;
                }
                else if (!cursor){
                    return nullptr;
                }
            }
        }
    }
    return nullptr;
}

Node* sharedListBruteForce(Node* listOne, Node* listTwo){
    while (listOne){
        while (listTwo) {
            if (listOne == listTwo){
                return listOne;
            }
            listTwo = listTwo->next;
        }
        listOne = listOne->next;
    }
    return nullptr;
}

Node* sharedListUsingSet(Node* listOne, Node* listTwo){
    unordered_set<Node*> one;
    while (listOne){
        one.insert(listOne);
        listOne = listOne->next;
    }
    while (listTwo){
        if (one.find(listTwo) == one.end()){
            return listTwo;
        }
        listTwo = listTwo->next;
    }
    return  nullptr;
}

int main(int argc, const char * argv[]) {
    Node* listOne = listBuild({5, 7, 9, 1});
    Node* listTwo = listBuild({6, 3, 2});
    
    cout << "Part One:" << endl;
    
    cout << "\nL1: ";
    printList(listOne);
    cout << "L2: ";
    printList(listTwo);
    
    Node* target = listOne;
    while (target->data != 7){
        target = target->next;
    }
    cout << "Target: ";
    printList(target);
    cout << "Splicing L2 at Target in L1" << endl;
    splice(listTwo, target);
    
    cout << "L1: ";
    printList(listOne);
    cout << "L2: ";
    printList(listTwo);
    cout << "============================\n\nPart Two:\n";
    
    Node* masterList = listBuild({1, 2, 3, 2, 3, 2, 4, 5, 6});
    Node* t1 = listBuild({1});
    Node* t2 = listBuild({3, 9});
    Node* t3 = listBuild({2, 3});
    Node* t4 = listBuild({2, 4, 5, 6});
    Node* t5 = listBuild({2, 3, 2, 4});
    Node* t6 = listBuild({5, 6, 7});
    
    cout << "Attempt match: 1\n";
    Node* one = isSublist(masterList, t1);
    if (one) { printList(one);}
    else { cout << "Failed to match\n"; }
    
    cout << "Attempt match: 3, 9\n";
    Node* two = isSublist(masterList, t2);
    if (two) { printList(two);}
    else { cout << "Failed to match\n"; }
    
    cout << "Attempt match: 2, 3\n";
    Node* three = isSublist(masterList, t3);
    if (three) { printList(three);}
    else { cout << "Failed to match\n"; }
    
    cout << "Attempt match: 2, 4, 5, 6\n";
    Node* four = isSublist(masterList, t4);
    if (four) { printList(four); }
    else { cout << "Failed to match\n"; }
    
    cout << "Attempt match: 2, 3, 2, 4\n";
    Node* five = isSublist(masterList, t5);
    if (five) { printList(five); }
    else { cout << "Failed to match\n"; }
    
    cout << "Attempt match: 5, 6, 7\n";
    Node* six = isSublist(masterList, t6);
    if (six) { printList(six); }
    else { cout << "Failed to match\n"; }
}
