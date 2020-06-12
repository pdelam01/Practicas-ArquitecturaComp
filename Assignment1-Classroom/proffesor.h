#ifndef PROFFESOR_H
#define PROFFESOR_H

#include "person.h"
#include "student.h"

class Proffesor: public Person{
public:
    Proffesor();
    ~Proffesor();

    Student* getStudent(int position);
    void addStudent(Student* student);
    void addGrades(int firstGrade, Student *student);
    void addGrades(int firstGrade, int secondGrade,Student *student);
    void addGrades(int firstGrade, int secondGrade, int thirdGrade,Student *student);
    double midGrade(Student *student);
    void printAvgGrades();
    void highestGradeStudent();
    int returnSize();
    void printStudents();
    void printStudentGrades();
    void toString();

private:
    vector<Student*> students;
};

#endif // PROFFESOR_H
