#include <iostream>
#include "person.h"
#include "proffesor.h"
#include "student.h"

using namespace std;

void Calificando(){
    vector<Proffesor> vecProff;

    //-------Teachers Data---------
    Proffesor *proffesor = new Proffesor();
    proffesor->setName("Antonio");
    proffesor->setSurname("Alvarez");
    proffesor->setDNI("AA");

    Proffesor *proffesor1 = new Proffesor();
    proffesor1->setName("Maria");
    proffesor1->setSurname("Ramirez");
    proffesor1->setDNI("AB");

    //-------Students Data---------
    Student *student = new Student();
    student->setName("Rebeca");
    student->setSurname("Gutierres");
    student->setDNI("11");

    Student *student1 = new Student();
    student1->setName("Antonio");
    student1->setSurname("Alvarez");
    student1->setDNI("12");

    Student *student2 = new Student();
    student2->setName("Ramiro");
    student2->setSurname("Pan y Agua");
    student2->setDNI("13");

    Student *student3 = new Student();
    student3->setName("Rosalia");
    student3->setSurname("Alcantara");
    student3->setDNI("14");

    //--------Assignment----------
    proffesor->addStudent(student);
    proffesor->addStudent(student1);
    proffesor->addStudent(student2);

    proffesor1->addStudent(student3);

    proffesor->addGrades(6,6,5,student);
    proffesor->addGrades(5,6,student1);
    proffesor->addGrades(5,9,2,student2);
    proffesor1->addGrades(8,8,8,student3);

    vecProff.push_back(*proffesor);
    vecProff.push_back(*proffesor1);

    //We print the list of teachers and students associated with them. Also, we print the student with the highest average grade
    for(int i=0;i<(int)vecProff.size();i++){
        vecProff[i].toString();
        cout<<"**STUDENTS**"<<endl;
        vecProff[i].printStudents();
        vecProff[i].highestGradeStudent();
        cout<<"============================================"<<endl;
     }


    //We check the entry of the DNI
    int nop;
    int nop2;
    do{
        string value;
        cout<<"\n"<<endl;
        cout<<"Please, enter a DNI: "<< endl;
        cin>>value;
        for(int i=0;i<(int)vecProff.size();i++){
            if(vecProff[i].getDNI()==value){
               vecProff[i].toString();
               cout<<"**STUDENTS**"<<endl;
               vecProff[i].printStudents();
               cout<<"--------------------------------------------"<<endl;
               vecProff[i].printStudentGrades();
               cout<<"--------------------------------------------"<<endl;
               vecProff[i].printAvgGrades();
               cout<<"--------------------------------------------"<<endl;
               vecProff[i].highestGradeStudent();
               cout<<"--------------------------------------------"<<endl;
               nop=0;
               break;
             }else{
                for(int j=0;j<(int)vecProff[i].returnSize();j++){
                    if(vecProff[i].getStudent(j)->getDNI()==value){
                        cout<<"--------------------------------------------"<<endl;
                        vecProff[i].getStudent(j)->toString();
                        cout<<"--------------------------------------------"<<endl;
                        vecProff[i].getStudent(j)->printGrades();
                        cout<<"--------------------------------------------"<<endl;
                        vecProff[i].getStudent(j)->printAvgGrades();
                        nop=0;
                        nop2=0;
                    }else{
                        nop=1;
                    }
                 }
             }
         }
    }while(nop==1 && nop2!=0);

    //Always we must delete the objects to free memory
    delete proffesor;
    delete proffesor1;
    delete student;
    delete student1;
    delete student2;
    delete student3;
}


int main(){
    Calificando();
    return 0;
}
