//
//  Course.hpp
//  lab7SeparateCompilation
//
//  Created by Nahom Molla on 10/19/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#ifndef Course_hpp
#define Course_hpp

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace BrooklynPoly {
    class Student;
    class Course {
        friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
    public:
        // Course methods needed by Registrar
        Course(const std::string& courseName);
        const std::string& getName() const;
        bool addStudent(Student* studentToAdd);
        void removeStudentsFromCourse();
        
    private:
        std::string name;
        std::vector<Student*> students;
    };
}
#endif /* Course_hpp */
