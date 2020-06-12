#include "student.h"
#include "person.h"

Student::Student(){

}

Student::~Student(){

}

int Student::getGrades(int position){
    return grades[position];
}

void Student::setGrades(int grade){
    grades.push_back(grade);
}

int Student::returnSizeStudent(){
    return grades.size();
}

void Student::printGrades(){
    cout<<"The grades are: "<<endl;
    for(int i=0;i<(int)grades.size();i++){
        cout<<"For the "<<i+1<<" exam: "<<getGrades(i)<<""<<endl;
    }
}


void Student::printAvgGrades(){
    double aux,valor;
    for(int i=0;i<(int)grades.size();i++){
        aux=(double)getGrades(i)+aux;
    }
    valor=aux/(double)grades.size();
    cout<<"The average grade is: "<<valor<<endl;
}

void Student::toStringN(){
    cout<<""+getName()+" "+getSurname()+", DNI: "+getDNI()<<endl;
}

void Student::toString(){
    cout<<"Name: "+getName()+", Surname: "+getSurname()+", DNI: "+getDNI()<<endl;
}


