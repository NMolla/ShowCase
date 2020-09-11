//
//  Student.cpp
//  lab7SeparateCompilation
//
//  Created by Nahom Molla on 10/19/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include "Student.hpp"
#include "Course.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

namespace BrooklynPoly {
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

    void Student::removedFromCourse(Course* courseToRemove){
        bool exists = false;
        for (size_t i=0; i<courses.size(); ++i){
            if (courses[i]->getName() == courseToRemove->getName()){
                courses[i] = nullptr;
                exists=true;
            }
            if (exists && i<courses.size()-1){
                courses[i] = courses[i+1];
            }
        }
        courses.pop_back();
    }
}
