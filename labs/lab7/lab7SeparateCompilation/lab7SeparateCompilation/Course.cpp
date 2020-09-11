//
//  Course.cpp
//  lab7SeparateCompilation
//
//  Created by Nahom Molla on 10/19/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include "Course.hpp"
#include "Student.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

namespace BrooklynPoly {
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
}
