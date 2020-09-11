//
//  main.cpp
//  lab13
//
//  Created by Nahom Molla on 12/7/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

void printList(const list<int>& lst){
    for (list<int>::const_iterator p=lst.begin(); p!=lst.end(); ++p){
        cout << *p << ' ';
    }
    cout << endl;
}

void printListRanged(const list<int>& lst){
    for (int i : lst){
        cout << i << ' ';
    }
    cout << endl;
}

//Task 11
void printAlternate(const list<int>& lst){
    for (auto p=lst.begin(); p!=lst.end(); ++++p){
        cout << *p << ' ';
    }
    cout << endl;
}

//Task 12
list<int>::const_iterator findItem(const list<int>& lst, int item){
    for (list<int>::const_iterator p=lst.begin(); p!=lst.end(); ++p){
        if (*p == item) return p;
    }
    return lst.end();
}

//Task 13
auto findItemAuto(const list<int>& lst, int item){
    for(auto p=lst.begin(); p!=lst.end(); ++p){
        if (*p == item) return p;
    }
    return lst.end();
}

//Task 15
bool isEven(int val) { return val % 2 == 0; }

//Task 16
struct isEvenFunctor {
    bool operator()(int val) const {
        return val % 2 == 0;
    }
};

//Task 19
list<int>::const_iterator ourFind(list<int>::iterator start, list<int>::iterator stop, int item){
    cout << "ourFind (non-templated) in progress..." << endl;
    for (list<int>::const_iterator p = start; p != stop; ++p){
        if (*p == item) return p;
    }
    return stop;
}

//Task 20
template<typename T, typename U>
T ourFind(T start, T stop, U item){
    cout << "ourFind (templated) in progress...\n";
    for (T p=start; p!=stop; ++p){
        if (*p == item) return p;
    }
    return stop;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vect {1, 14, 22, 32, 53, 48, 13, 21};
    for (int i : vect){ cout << i << ' '; }
    cout << "\n=======\n";
    
    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> lst(vect.begin(), vect.end());
    for (int i : lst) { cout << i << ' '; }
    cout << "\n=======\n";
    
    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vect.begin(), vect.end());
    for (int i : vect){ cout << i << ' '; }
    cout << endl;
    for (int i : lst) { cout << i << ' '; }
    cout << "\n=======\n";
    
    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i=0; i<vect.size(); ++++i){
        cout << vect[i] << ' ';
    }
    cout << "\n=======\n";
    
    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    //for (size_t i=0; i<lst.size(); ++i){
    //    if (i % 2 == 0) { cout << lst[i] << ' '; }
    //}
    cout << "No index operator available for list\n=======\n";
    
    //
    // Iterators
    //
    
    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator p=vect.begin(); p!=vect.end(); ++++p){
        cout << *p << ' ';
    }
    cout << "\n=======\n";
    
    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for (list<int>::iterator p=lst.begin(); p!=lst.end(); ++++p){
        cout << *p << ' ';
    }
    cout << "\n=======\n";
    
    // 8. Sorting a list
    cout << "Task 8:\n";
    lst.sort();
    for (list<int>::iterator p=lst.begin(); p!=lst.end(); ++p){
        cout << *p << ' ';
    }
    cout << "\n=======\n";
    
    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printList(lst);
    cout << "=======\n";
    
    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printListRanged(lst);
    cout << "=======\n";
    
    //
    // Auto
    //
    
    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printAlternate(lst);
    cout << "=======\n";
    
    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    cout << *findItem(lst, 14) << endl;
    cout << *findItem(lst, 10004) << endl;
    cout << "=======\n";
    
    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    cout << *findItemAuto(lst, 14) << endl;
    cout << *findItemAuto(lst, 10000) << endl;
    cout << "=======\n";
    
    //
    // Generic Algorithms
    //
    
    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    cout << *find(lst.begin(), lst.end(), 14) << endl;
    cout << *find(lst.begin(), lst.end(), 1000) << endl;
    cout << "=======\n";
    
    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    vector<int>::iterator evenInVector = find_if(vect.begin(), vect.end(), isEven);
    list<int>::iterator evenInList = find_if(lst.begin(), lst.end(), isEven);
    
    if (evenInVector == vect.end()) cout << "No even number in vector" << endl;
    else cout << *evenInVector << endl;

    if (evenInList == lst.end()) cout << "No even number in vector" << endl;
    else cout << *evenInList << endl;

    cout << "=======\n";
    
    // 16. Functor
    cout << "Task 16:\n";
    list<int>::iterator evenInList2 = find_if(lst.begin(), lst.end(), isEvenFunctor());
    cout << *evenInList2 << endl;
    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    list<int>::iterator evenInList3 = find_if(lst.begin(), lst.end(), [] (int val) { return val % 2 == 0; });
    cout << *evenInList3 << endl;
    cout << "=======\n";
    
    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int arr[lst.size()];
    copy(lst.begin(), lst.end(), arr);
    for (int i : arr){
        cout << i << ' ';
    }
    cout << endl;
    int* oddInArray = find_if(arr, arr+lst.size(), [] (int n) { return n % 2 == 1; });
    cout << *oddInArray << endl;
    cout << "=======\n";
    
    //
    // Templated Functions
    //
    
    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    list<int>::const_iterator res = ourFind(lst.begin(), lst.end(), 14);
    cout << *res << endl;
    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    list<int>::const_iterator res2 = ourFind(lst.begin(), lst.end(), 14);
    cout << *res2 << endl;
    cout << "===\n";
    vector<int>::const_iterator res3 = ourFind(vect.begin(), vect.end(), 14);
    cout << *res3 << endl;
    cout << "=======\n";
    //
    // Associative collections
    //
    
    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    vector<string> vs;
    ifstream ifs("pooh-nopunc.txt");
    if (!ifs) { cerr << "FNF"; exit(1); }
    string word;
    while (ifs >> word){
        if (find(vs.begin(), vs.end(), word) == vs.end()){
            vs.push_back(word);
        }
    }
    cout << vs.size() << endl;
    for (const string& i : vs) {
        cout << i << ' ';
    }
    ifs.close();
    cout << "\n=======\n";
    
    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    set<string> ss;
    ifstream ifs2("pooh-nopunc.txt");
    if (!ifs2) { cerr << "FNF"; exit(1); }
    string word2;
    while (ifs2 >> word2){
        ss.insert(word2);
    }
    cout << ss.size() << endl;
    for (const string& i : ss){
        cout << i << ' ';
    }
    cout << endl;
    ifs2.close();
    cout << "=======\n";
    
    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<size_t>> wordMap;
    size_t i = 0;
    ifstream ifs3("pooh-nopunc.txt");
    if (!ifs3) { cerr << "FNF"; exit(1); }
    string word3;
    while (ifs3 >> word3){
        wordMap[word3].push_back(i);
        ++i;
    }
    for (const auto& item : wordMap){
        cout << item.first << ' ';
        for (size_t j : item.second){
            cout << j << ' ';
        }
        cout << endl;
    }
    cout << endl;
    cout << "=======\n";
}
