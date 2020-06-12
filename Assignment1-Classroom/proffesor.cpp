#include "proffesor.h"
#include "student.h"
#include <string>

Proffesor::Proffesor(){

}

Proffesor::~Proffesor(){

}

Student* Proffesor::getStudent(int position){
    return students[position];
}

void Proffesor::addStudent(Student *student){
    students.push_back(student);
}

void Proffesor::addGrades(int firstGrade, Student* student){
    student->setGrades(firstGrade);
}

void Proffesor::addGrades(int firstGrade, int secondGrade, Student* student){
    student->setGrades(firstGrade);
    student->setGrades(secondGrade);
}

void Proffesor::addGrades(int firstGrade, int secondGrade, int thirdGrade, Student* student){
    student->setGrades(firstGrade);
    student->setGrades(secondGrade);
    student->setGrades(thirdGrade);
}

double Proffesor::midGrade(Student* student){
    int aux=0;
    double valor=0.0;
    for(int i=0;i<student->returnSizeStudent();i++){
        aux=(double)student->getGrades(i)+aux;
    }
    valor=aux/(double)student->returnSizeStudent();
    return valor;
}

void Proffesor::printAvgGrades(){
    for(int i=0;i<(int)students.size();i++){
        students[i]->toStringN();
        cout<<"The average grade is: "<<midGrade(students[i])<<endl;
    }
}

void Proffesor::highestGradeStudent(){
    double big,aux;
    Student *stu;
    for(int i=0;i<(int)students.size();i++){
        if(students[i]->returnSizeStudent()==3){
            aux=midGrade(students[i]);
            if(aux>big){
                big=aux;
                stu=students[i];
            }
        }else{
           //
        }
    }
    cout<<"The highest average grade is: "<<big<<". The student with this average is: "<<endl;
    stu->toStringN();
}

int Proffesor::returnSize(){
    return students.size();
}

void Proffesor::printStudents(){
    for(int i=0; i<(int)students.size();i++){
        students[i]->toString();
    }
}

void Proffesor::printStudentGrades(){
    for(int i=0; i<(int)students.size();i++){
        students[i]->toStringN();
        students[i]->printGrades();
        cout<<"\n"<<endl;
    }
}

void Proffesor::toString(){
    cout<<"\n**TEACHER** \n"
          "Name: "+getName()+", Surname: "+getSurname()+", DNI: "+getDNI()+"\n";
}

