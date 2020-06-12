#include "vehicle.h"

using namespace std;

vehicle::vehicle()
{

}

vehicle::vehicle(QString name,QString wheels, bool motor, int motorPower, int numWagons, bool fuel, QString fuelType, QString color, bool wings, bool reactors,
                 bool undercarriage, bool locomotiv,QString wagons, bool spareWheel, bool puntureKit, QString licensePlate)
{
    this->name=name;
    this->wheels=wheels;
    this->motor=motor;
    this->motorPower=motorPower;
    this->numWagons=numWagons;
    this->fuel=fuel;
    this->fuelType=fuelType;
    this->color=color;
    this->wings=wings;
    this->reactors=reactors;
    this->undercarriage=undercarriage;
    this->locomotiv=locomotiv;
    this->wagons=wagons;
    this->spareWheel=spareWheel;
    this->puntureKit=puntureKit;
    this->licensePlate=licensePlate;

}

vehicle::~vehicle()
{

}

QString vehicle::getName(){
    return name;
}

QString vehicle::getFuelType(){
    return fuelType;
}

QString vehicle::getColor(){
    return color;
}

QString vehicle::getLicense(){
    return licensePlate;
}

QString vehicle::getWheels(){
    return wheels;
}

QString vehicle::getWagons(){
    return wagons;
}

int vehicle::getMotorPower(){
    return motorPower;
}

int vehicle::getNumWagons(){
    return numWagons;
}

bool vehicle::getMotor(){
    return motor;
}

bool vehicle::getFuel(){
    return fuel;
}

bool vehicle::getWings(){
    return wings;
}

bool vehicle::getReactors(){
    return reactors;
}

bool vehicle::getUndercarriage(){
    return undercarriage;
}

bool vehicle::getLocomotiv(){
    return locomotiv;
}

bool vehicle::getSpareWheel(){
    return spareWheel;
}

bool vehicle::getPuntureKit(){
    return puntureKit;
}

void vehicle::setName(QString value){
    name=value;
}

void vehicle::setFuelType(QString value){
    fuelType=value;
}

void vehicle::setColor(QString value){
    color=value;
}

void vehicle::setLicense(QString value){
    licensePlate=value;
}

void vehicle::setWheels(QString value){
    wheels=value;
}

void vehicle::setWagons(QString value){
    wagons=value;
}

void vehicle::setMotorPower(int value){
    motorPower=value;
}

void vehicle::setNumWagons(int value){
    numWagons=value;
}

void vehicle::setMotor(bool value){
    motor=value;
}

void vehicle::setFuel(bool value){
    fuel=value;
}

void vehicle::setWings(bool value){
    wings=value;
}

void vehicle::setReactors(bool value){
    reactors=value;
}

void vehicle::setUndercarriage(bool value){
    undercarriage=value;
}

void vehicle::setLocomotiv(bool value){
    locomotiv=value;
}

void vehicle::setSpareWheel(bool value){
    spareWheel=value;
}

void vehicle::setPuntureKit(bool value){
    puntureKit=value;
}
