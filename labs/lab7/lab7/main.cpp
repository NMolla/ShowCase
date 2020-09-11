//
//  main.cpp
//  lab7
//
//  Created by Nahom Molla on 10/19/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student* studentToAdd);
    void removeStudentsFromCourse();
    
private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course* courseToAdd);
    
    // Student method needed by Course
    void removedFromCourse(Course* courseToRemove);
    
private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string& courseName);
    bool addStudent(const string& studentName);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();
    
private:
    size_t findStudent(const string& studentToFind) const;
    size_t findCourse(const string& courseToFind) const;
    
    vector<Course*> courses;
    vector<Student*> students;
};

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

//=====================================================
//Course
Course::Course(const string& courseName) : name(courseName) {}
const string& Course::getName() const { return name; }

bool Course::addStudent(Student* studentToAdd){
    bool exists=false;
    for (size_t i=0; i<students.size(); ++i){
        if (students[i]->getName() == studentToAdd->getName()){
            exists=true;
            break;
        }
    }
    if (!exists){
        students.push_back(studentToAdd);
        return true;
    }
    return false;
}

void Course::removeStudentsFromCourse(){
    for (size_t i=0; i<students.size(); ++i){
        students[i]->removedFromCourse(this);
        students[i] = nullptr;
    }
    students.clear();
}

ostream& operator<<(ostream& os, const Course& rhs){
    os << rhs.name << ": ";
    if (rhs.students.size() == 0){ os << "No Students";}
    else {
        for (const Student* someStudent : rhs.students){
            os << someStudent->getName() << ' ';
        }
    }
    return os;
}

//=====================================================
//Student
ostream& operator<<(ostream& os, const Student& rhs) {
    os << rhs.name << ": ";
    if (rhs.courses.size() == 0){ os << "No Courses";}
    else {
        for (const Course* someCourse : rhs.courses){
            os << someCourse->getName() << ' ';
        }
    }
    return os;
}

// Student methods needed by Registrar
Student::Student(const string& name) : name(name){}
const string& Student::getName() const { return name; }
bool Student::addCourse(Course* courseToAdd){
    bool exists=false;
    for (const Course* someCourse : courses){
        if (someCourse->getName() == courseToAdd->getName()){
            exists=true;
            break;
        }
    }
    if(!exists){
        courses.push_back(courseToAdd);
        return true;
    }
    return false;
}

// Student method needed by Course
void Student::removedFromCourse(Course* courseToRemove){
    bool exists = false;
    for (size_t i=0; i<courses.size(); ++i){
        if (courses[i]->getName() == courseToRemove->getName()){
            courses[i] = nullptr; //delete course from student
            exists=true;
        }
        if (exists && i<courses.size()-1){
            courses[i] = courses[i+1];
        }
    }
    courses.pop_back();
}

//=====================================================
//Registrar


ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Registrar's Report\n" << "Courses:" << endl;
    if (rhs.courses.size() > 0){
        for (const Course* someCourse : rhs.courses){
            os << *someCourse << endl;
        }
    }
    os << "Students:" << endl;
    if (rhs.students.size() > 0){
        for (const Student* someStudent : rhs.students){
            os << *someStudent << endl;
        }
    }
    return os;
}

Registrar::Registrar() {}
bool Registrar::addCourse(const string& courseName) {
    for (const Course* someCourse : courses){
        if (someCourse->getName() == courseName){
            return false;
        }
    }
    courses.push_back(new Course(courseName));
    return true;
}
bool Registrar::addStudent(const string& studentName) {
    for (const Student* someStudent : students){
        if (someStudent->getName() == studentName){
            return false;
        }
    }
    students.push_back(new Student(studentName));
    return true;
}
bool Registrar::enrollStudentInCourse(const string& studentName,
                                      const string& courseName) {
    
    if (findStudent(studentName)==students.size() ||
        findCourse(courseName)==courses.size()){
            return false;
    }
    students[findStudent(studentName)]->
        addCourse(courses[findCourse(courseName)]);
    courses[findCourse(courseName)]->
        addStudent(students[findStudent(studentName)]);
    return true;
}
bool Registrar::cancelCourse(const string& courseName) {
    bool exists=false;
    for (size_t i=0; i<courses.size(); ++i){
        if (courses[i]->getName() == courseName){
            courses[i]->removeStudentsFromCourse();
            delete courses[i];
            courses[i] = nullptr;
            exists=true;
        }
        if (exists && i<courses.size()-1){
            courses[i] = courses[i+1];
        }
    }
    courses.pop_back();
    return exists;
}
void Registrar::purge() {
    for (Course* someCourse : courses){
        someCourse->removeStudentsFromCourse();
        delete someCourse;
    }
    for (Student* someStudent : students){
        delete someStudent;
    }
    courses.clear();
    students.clear();
}

size_t Registrar::findStudent(const string& studentToFind) const {
    for (size_t i=0; i<students.size(); ++i){
        if (students[i]->getName() == studentToFind){ return i; }
    }
    return students.size();
}
size_t Registrar::findCourse(const string& courseToFind) const {
    for (size_t i=0; i<courses.size(); ++i){
        if (courses[i]->getName() == courseToFind){ return i; }
    }
    return courses.size();
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


