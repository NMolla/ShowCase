//
//  main.cpp
//  lab7SeparateCompilation
//
//  Created by Nahom Molla on 10/19/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include "Student.hpp"
#include "Course.hpp"
#include "Registrar.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
using namespace BrooklynPoly;

int main() {
    
    Registrar registrar;
    
    cout << "No courses or students added yet\n";
    cout << registrar << endl;
    
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;
    
    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;
    
    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;
    
    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;
    
    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout <<  "Should fail, i.e. do nothing, since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;
    
    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
    
    /*
     // [OPTIONAL - do later if time]
     cout << "ChangeStudentName FritzTheCat MightyMouse\n";
     registrar.changeStudentName("FritzTheCat", "MightyMouse");
     cout << registrar << endl;  // or registrar.printReport()
     
     cout << "DropStudentFromCourse MightyMouse CS101.001\n";
     registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
     cout << registrar << endl;  // or registrar.printReport()
     
     cout << "RemoveStudent FritzTheCat\n";
     registrar.removeStudent("FritzTheCat");
     cout << registrar << endl;  // or registrar.printReport()
     */
    
    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

/*
 void executeLines(ifstream& commands){
 string description;
 string tokenOne;
 string tokenTwo;
 while (commands>>description) {
 if (description == "AddCourse"){
 
 }
 else if (description == "AddStudent"){
 
 }
 else if (description == "EnrollStudentInCourse"){
 
 }
 else if (description == "CancelCourse"){
 
 }
 }
 }
 */


