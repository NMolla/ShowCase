//
//  main.cpp
//  lab12
//
//  Created by Nahom Molla on 11/30/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
using namespace std;

class List {
    friend ostream& operator<<(ostream& os, const List& rhs){
        if (!rhs.size()){
            return os;
        }
        Node* cursor = rhs.head;
        for (size_t i=0; i<rhs.size(); ++i){
            os << cursor->data << ' ';
            cursor = cursor->next;
        }
        return os;
    }
    struct Node {
        Node(int data, Node*prev=nullptr, Node* next=nullptr) :
            data(data), prev(prev), next(next) {}
        int data;
        Node* prev;
        Node* next;
    };
    
public:
    class iterator {
        friend List;
        friend bool operator==(const List::iterator& lhs, const List::iterator& rhs);
    public:
        iterator(Node* p) : where(p) {}
        iterator& operator++(){
            where = where->next;
            return *this;
        }
        iterator& operator--(){
            where = where->prev;
            return *this;
        }
        int& operator*() {
            return where->data;
        }
    private:
        Node* where;
    };
    
    void push_back(int data){
        if (!head){
            head = new Node(data);
            tail = head;
        }
        else {
            tail->next = new Node(data, tail);
            tail = tail->next;
        }
        ++length;
    }
    void push_front(int data){
        if (!head){
            push_back(data);
        }
        else {
            head->prev = new Node(data, nullptr, head);
            head = head->prev;
            ++length;
        }
    }
    void pop_back(){
        if (!head){ //empty
            return;
        }
        if (head == tail){ //1 element
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else { // > 1 element
            Node* prior = tail->prev;
            prior->next = nullptr;
            delete tail;
            tail = prior;
        }
        --length;
    }
    void pop_front(){
        if (!head || (head == tail)){ //empty or 1 element
            pop_back();
        }
        else { // > 1 element
            Node* successor = head->next;
            successor->prev = nullptr;
            delete head;
            head = successor;
            --length;
        }
    }
    iterator insert(iterator pos, int data){
        Node* successor = pos.where;
        if (!successor){
            push_back(data);
            return iterator(head);
        }
        else if (!successor->prev){
            push_front(data);
            return iterator(head);
        }
        else {
            Node* newNode = new Node(data, successor->prev, successor);
            successor->prev->next = newNode;
            successor->prev = newNode;
            return iterator(newNode);
        }
    }
    
    int& front(){
        return head->data;
    }
    int& back(){
        return tail->data;
    }
    int front() const {
        int x = head->data;
        return x;
    }
    int back() const {
        int x = tail->data;
        return x;
    }
    size_t size() const {
        return length;
    }
    void clear(){
        if (!size()) return;
        while (head != tail){
            Node* prev = tail->prev;
            delete tail;
            tail = prev;
        }
        delete head;
        head = nullptr;
        tail = nullptr;
        length = 0;
    }
    int operator[](size_t index) const {
        Node* cursor = head;
        for (size_t i=0; i<index; ++i){
            cursor = cursor->next;
        }
        int x = cursor->data;
        return x;
    }
    int& operator[](size_t index){
        Node* cursor = head;
        for (size_t i=0; i<index; ++i){
            cursor = cursor->next;
        }
        return cursor->data;
    }
    iterator begin() {
        return iterator(head);
    }
    iterator end() {
        return iterator(nullptr);
    }
    iterator erase(iterator pos) {
        Node* curr = pos.where;
        if (!curr){
            return iterator(nullptr);
        }
        else if (!curr->next){
            delete curr;
            head = nullptr;
            tail = nullptr;
            length--;
            return iterator(nullptr);
        }
        else {
            Node* prior = curr->prev;
            Node* successor = curr->next;
            delete curr;
            if (prior){
                prior->next = successor;
            }
            else {
                head = successor;
            }
            if (successor){
                successor->prev = prior;
            }
            else {
                tail = prior;
            }
            length--;
            return iterator(successor);
        }
    }
private:
    Node* head=nullptr;
    Node* tail=nullptr;
    size_t length=0;
};

bool operator==(const List::iterator& lhs, const List::iterator& rhs){
    if (lhs.where == rhs.where) return true;
    else return false;
}

bool operator!=(const List::iterator& lhs, const List::iterator& rhs){
    return !(lhs == rhs);
}

void printListInfo(List& myList);
void doNothing(List aList); //Task 8

int main(int argc, const char * argv[]) {
    List myList;
    
    // Task 1
    cout << "\n------Task One------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";
    
    // Task2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";
    
    // Task3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";
    
    // Task4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    
    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
    
    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
    << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";
    
    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";
    
    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);
    
    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}

void printListInfo(List& myList) {
    cout << "size: " << myList.size()
    << ", front: " << myList.front()
    << ", back(): " << myList.back()
    << ", list: " << myList << endl;
}

void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}
