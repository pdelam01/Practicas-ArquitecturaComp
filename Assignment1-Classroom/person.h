#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <vector>

using namespace std;

class Person{
public:
    //Constructor de la clase
    Person();

    //Constructor sobrecargado
    Person(string name, string surname, string dni);

    //Destructor
    ~Person(void);

    //Getters and Setter
    string getName();
    void setName(string value);

    string getSurname();
    void setSurname(string value);

    string getDNI();
    void setDNI(string value);

private:
    string name;
    string surname;
    string dni;
};

#endif // PERSON_H
