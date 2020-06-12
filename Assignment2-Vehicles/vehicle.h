#ifndef VEHICLE_H
#define VEHICLE_H

#include <QMainWindow>
#include <iostream>
#include <string>

class vehicle
{
public:
    vehicle();
    vehicle(QString name,QString wheels, bool motor, int motorPower,int numWagons, bool fuel, QString fuelType,
            QString color, bool wings, bool reactors, bool undercarriage, bool locomotiv,
            QString wagons, bool spareWheel, bool puntureKit, QString licensePlate );
    ~vehicle();

    //Getters
    QString getName();
    QString getFuelType();
    QString getColor();
    QString getLicense();
    QString getWheels();
    QString getWagons();
    int getMotorPower();
    int getNumWagons();
    bool getMotor();
    bool getFuel();
    bool getWings();
    bool getReactors();
    bool getUndercarriage();
    bool getLocomotiv();
    bool getSpareWheel();
    bool getPuntureKit();

    //Setters
    void setName(QString value);
    void setFuelType(QString value);
    void setColor(QString value);
    void setLicense(QString value);
    void setWheels(QString value);
    void setWagons(QString value);
    void setMotorPower(int value);
    void setNumWagons(int value);
    void setMotor(bool value);
    void setFuel(bool value);
    void setWings(bool value);
    void setReactors(bool value);
    void setUndercarriage(bool value);
    void setLocomotiv(bool value);
    void setSpareWheel(bool value);
    void setPuntureKit(bool value);

    QString name,fuelType,color,licensePlate,wheels,wagons;
    int motorPower,numWagons;
    bool motor,fuel,wings,reactors,undercarriage,locomotiv,spareWheel,puntureKit;

};

#endif // VEHICLE_H
