//
//  Registrar.cpp
//  lab7SeparateCompilation
//
//  Created by Nahom Molla on 10/19/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include "Registrar.hpp"
#include "Course.hpp"
#include "Student.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

namespace BrooklynPoly {
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
        if (findCourse(courseName) == courses.size()){
            courses.push_back(new Course(courseName));
            return true;
        }
        return false;
    }
    bool Registrar::addStudent(const string& studentName) {
        if (findStudent(studentName) == students.size()){
            students.push_back(new Student(studentName));
            return true;
        }
        return false;
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
        size_t i = findCourse(courseName);
        if (i<courses.size()){
            courses[i]->removeStudentsFromCourse();
            delete courses[i];
            courses[i] = nullptr;
            for (size_t j=i; j<courses.size()-1; ++j){
                courses[j] = courses[j+1];
            }
            courses.pop_back();
            return true;
        }
        return false;
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
}
