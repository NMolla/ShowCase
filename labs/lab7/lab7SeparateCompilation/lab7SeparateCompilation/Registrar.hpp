//
//  Registrar.hpp
//  lab7SeparateCompilation
//
//  Created by Nahom Molla on 10/19/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#ifndef Registrar_hpp
#define Registrar_hpp

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace BrooklynPoly {
    class Course;
    class Student;
    class Registrar {
        friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);
    public:
        Registrar();
        bool addCourse(const std::string& courseName);
        bool addStudent(const std::string& studentName);
        bool enrollStudentInCourse(const std::string& studentName,
                                   const std::string& courseName);
        bool cancelCourse(const std::string& courseName);
        void purge();
        
    private:
        std::size_t findStudent(const std::string& studentToFind) const;
        std::size_t findCourse(const std::string& courseToFind) const;
        
        std::vector<Course*> courses;
        std::vector<Student*> students;
    };
}
#endif /* Registrar_hpp */
