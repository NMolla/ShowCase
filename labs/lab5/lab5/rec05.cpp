//
//  reco05.cpp
//  lab5
//
//  Created by Nahom Molla on 10/5/18.
//  Copyright © 2018 Nahom Molla. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Section{
    friend ostream& operator<<(ostream& os, const Section& rhs){
        os << "Section: " << rhs.name << ", " << rhs.time <<
        ", Students: ";
        if (rhs.studentRecords.size() == 0){
            os << "None";
        }
        else {
            os << endl;
            for (size_t i=0; i<rhs.studentRecords.size()-1; ++i){
                os << *(rhs.studentRecords[i]) << endl;
            }
            os << *(rhs.studentRecords[rhs.studentRecords.size()-1]); //to fix the spacing
        }
        return os;
    }
    
// ================================================================
    // -->
    // ================================================================
    class TimeSlot{
        friend ostream& operator<<(ostream& os, const TimeSlot& rhs){
            os << "Time slot: [Day: " << rhs.day << ", Start time: " <<
                rhs.convertTime() << ']';
            return os;
        }
    public:
        TimeSlot(const string& day, int time) : //check time
            day(day), time(time){};
        
    private:
        string day;
        unsigned time;
        
        const string convertTime() const {
            if (time >= 1 && time < 12){
                return to_string(time) + "am";
            }
            else {
                if (time == 12){
                    return to_string(time) + "pm";
                }
                else if (time > 12 && time < 24){
                    return to_string(time-12) + "pm";
                }
                else { //time == 24
                    return to_string(time-12) + "am";
                }
            }
        }
    };
    // <--
    // ================================================================
    // -->
    class StudentRecord{
        friend ostream& operator<<(ostream& os, const StudentRecord& rhs){
            os << "Name: " << rhs.name << ", Grades: ";
            for (int grade : rhs.grades){
                os << grade << ' ';
            }
            return os;
        }
    public:
        StudentRecord(const string& name) :
            name(name), grades(14, -1){}
        
        const string& getName() const { //check return by reference
            return name;
        }
        
        void addGrade(int grade, int week){
            grades[week-1] = grade;
        }
        
    private:
        string name;
        vector<int> grades;
    };
    // <--
    // ================================================================
//Section
public:
    Section(const string& name, const string& day, int time) :
        name(name), time(day, time){}
    
    void addStudent(const string& name){
        studentRecords.push_back(new StudentRecord(name));
    }
    
    void addGrade(const string& name, int grade, int week){
        for (StudentRecord*& someStudent : studentRecords){
            if (someStudent->getName() == name){
                someStudent->addGrade(grade, week);
                break;
            }
        }
    }
    
    ~Section(){
        cout << "Section: " << name << " is being deleted" << endl;
        for (StudentRecord* someStudent : studentRecords){
            cout << "Deleting " << someStudent->getName() << endl;
            delete someStudent;
            
        }
    }
    
    Section(const Section& rhs): name(rhs.name), time(rhs.time){
        for (size_t i=0; i<rhs.studentRecords.size(); ++i){
            studentRecords.push_back(new StudentRecord (*rhs.studentRecords[i]));
        }
    }
    
private:
    TimeSlot time;
    string name;
    vector<StudentRecord*> studentRecords;
};
// ================================================================

class LabWorker{
    friend ostream& operator<<(ostream& os, const LabWorker& rhs){
        if (rhs.section==nullptr){
            os << rhs.name << " does not have a section";
        }
        else {
            os << rhs.name << " has " << *(rhs.section);
        }
        return os;
    }
public:
    LabWorker(const string& name) : name(name){};
    void addSection(Section& sectionToAdd){ //check const
        section = &sectionToAdd;
    }
    void addGrade(const string& name, int grade, int week){
        section->addGrade(name, grade, week);
    }
    
private:
    string name;
    Section* section=nullptr; //check const
};
// ================================================================

void doNothing(Section sec) {
    cout << sec << endl;;
}
// ================================================================

int main() {
    
    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;
    
    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;
    
    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe("Moe");
    cout << moe << endl;
    
    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection(secA2);
    cout << moe << endl;
    
    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection(secB3);
    cout << jane << endl;
    
    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;
    
    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;
    
    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
    << "those students (or rather their records?)\n";
    
    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
    << "then make sure the following call works properly, i.e. no memory leaks\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";
    
    
}
