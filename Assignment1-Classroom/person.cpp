#include "person.h"
#include "student.h"
#include <iostream>

Person::Person(){

}

Person::Person(string name, string surname, string dni){
    this->name=name;
    this->surname=surname;
    this->dni=dni;
}

Person::~Person(){

}

string Person::getName(){
    return name;
}

void Person::setName(string value){
    name=value;
}

string Person::getSurname(){
    return surname;
}

void Person::setSurname(string value){
    surname=value;
}

string Person::getDNI(){
    return dni;
}

void Person::setDNI(string value){
    dni=value;
}



