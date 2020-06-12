#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

class Student: public Person{
public:
    Student();
    ~Student();

    int getGrades(int value);
    void setGrades(int value);
    int returnSizeStudent();
    void printGrades();
    void printAvgGrades();
    void toStringN();
    void toString();

private:
    vector<int> grades;
};

#endif // STUDENT_H
