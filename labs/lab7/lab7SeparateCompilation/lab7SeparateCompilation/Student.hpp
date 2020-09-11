//
//  Student.hpp
//  lab7SeparateCompilation
//
//  Created by Nahom Molla on 10/19/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#ifndef Student_hpp
#define Student_hpp

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace BrooklynPoly {
    class Course;

    class Student {
        friend std::ostream& operator<<(std::ostream& os, const Student& rhs);
    public:
        // Student methods needed by Registrar
        Student(const std::string& name);
        const std::string& getName() const;
        bool addCourse(Course* courseToAdd);
        
        // Student method needed by Course
        void removedFromCourse(Course* courseToRemove);
        
    private:
        std::string name;
        std::vector<Course*> courses;
    };
}
#endif /* Student_hpp */
