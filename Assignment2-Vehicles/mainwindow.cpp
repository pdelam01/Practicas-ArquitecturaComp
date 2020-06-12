#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"


#include <time.h>
#include <vehicle.h>
#include "vehicle.h"
#include <string>
#include <stdlib.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setVisible(false);
    ui->horizontalSlider->setVisible(false);
    ui->comboBox_2->setVisible(false);
    ui->spinBox_2->setVisible(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}

//Method generates the randomd license plate
void MainWindow::on_pushButton_clicked(){

    char license[8];
    string letters, numbers;
    letters="BCDFGHJKLMNPQRSTVWXYZ";
    numbers="1234567890";
    srand(time(NULL));

    for(int i=0;i<4;i++){
        license[i]=numbers[rand()%numbers.length()];
    }
    for(int j=4;j<7;j++){
        license[j]=letters[rand()%letters.length()];
    }
    ui->lineEdit_3->setText(license);
}

//When the Create vehicle button is cliked, a message will appers showing the type of vehicle created
void MainWindow::on_pushButton_2_clicked(){
    name=ui->lineEdit_2->text();
    wheels=ui->comboBox_3->currentText();
    motor=ui->checkBox_4->isChecked();
    motorPower=ui->spinBox->value();
    fuel=ui->checkBox_5->isChecked();
    fuelType=ui->comboBox_2->currentText();
    color=ui->comboBox->currentText();
    wings=ui->checkBox->isChecked();
    reactors=ui->checkBox_3->isChecked();
    undercarriage=ui->checkBox_7->isChecked();
    locomotiv=ui->checkBox_6->isChecked();
    wagons=ui->checkBox_2->isChecked();
    numWagons=ui->spinBox_2->value();
    spareWheel=ui->radioButton->isChecked();
    puntureKit=ui->radioButton_2->isChecked();
    licensePlate=ui->lineEdit_3->text();

    QMessageBox message;
    QString numOfVehicles;
    int aux;

    //Now we calificate the vehicle created by its qualities
    if(ui->lineEdit_2->text()!="" && ui->lineEdit_3->text()!=""){
            //Bycicle
        if(wheels=="2" && motor==false && wings==false && reactors==false && undercarriage==false && locomotiv==false && wagons==false && puntureKit==true){
            message.setText("The vehicle created was a: Bycicle!");
            //For the message to been shown
            message.exec();
            aux=1;

            //Trycicle
        }else if(wheels=="3" && motor==false && wings==false && reactors==false && undercarriage==false && locomotiv==false && wagons==false && puntureKit==true){
            message.setText("The vehicle created was a: Trycicle!");
            message.exec();
            aux=1;

            //Motorbike
        }else if(wheels=="2" && motor==true && fuel==true && fuelType!="Kerosene" && wings==false && reactors==false && undercarriage==false && locomotiv==false && wagons==false && puntureKit==true){
            message.setText("The vehicle created was a: Motorbike!");
            message.exec();
            aux=1;

            //Car
        }else if(wheels=="4" && motor==true && fuel==true && fuelType!="Kerosene" && wings==false && reactors==false && undercarriage==false && locomotiv==false && wagons==false && spareWheel==true){
            message.setText("The vehicle created was a: Car!");
            message.exec();
            aux=1;

            //Sport car
        }else if(wheels=="4" && motor==true && motorPower>=250 && fuel==true && (fuelType=="Gasoline" || fuelType=="Electric") && wings==false && reactors==false && undercarriage==false && locomotiv==false && wagons==false && puntureKit==true){
            message.setText("The vehicle created was a: Sport Car!");
            message.exec();
            aux=1;

            //Plane
        }else if(wheels=="6" && motor==true && motorPower==450 && fuel==true && fuelType=="Kerosene" && color=="White" && wings==true && reactors==true && undercarriage==true && locomotiv==false && wagons==false && spareWheel==true){
            message.setText("The vehicle created was a: Plane!");
            message.exec();
            aux=1;

            //Train
        }else if(wheels=="40" && motor==true && motorPower==450 && fuel==true && (fuelType=="Diesel" || fuelType=="Electric") && color=="Black" && wings==false && reactors==false && undercarriage==false && locomotiv==true && wagons==true && spareWheel==true){
            message.setText("The vehicle created was a: Train!");
            message.exec();
            aux=1;

            //Other configuration
        }else{
            message.setText("The combination created does not belong to any kind of vehicle");
            message.exec();
            aux=0;
        }
    }else{
        message.setText("You must insert a Name and a License Plate!");
        message.exec();
        aux=0;
    }

    //If the created vehicle exists, the count of vehicles increments
    if(aux==1){
    vehicle *v1 = new vehicle(name,wheels,motor,motorPower,numWagons,fuel,fuelType,color,wings,reactors,undercarriage,locomotiv,wagons,spareWheel,puntureKit,licensePlate);
    vehiclesList.push_back(v1);

    //Add the name of the vehicle created so that you can choose then for its features
    ui->comboBox_4->addItem(v1->getLicense());

    }

    numOfVehicles=QString::number(vehiclesList.size());
    ui->lineEdit->setText(numOfVehicles);

    //Reset the values
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_6->setChecked(false);
    ui->checkBox_7->setChecked(false);

    ui->spinBox->hide();
    ui->spinBox->setValue(80);
    ui->horizontalSlider->hide();
    ui->horizontalSlider->setValue(80);
    ui->spinBox_2->hide();
    ui->spinBox_2->setValue(5);

    ui->comboBox_2->hide();

    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);

}

//See the features
void MainWindow::on_pushButton_3_clicked(){
    QMessageBox message;

    if(ui->lineEdit_4->text()!=""){
        for(int i=0;i<(int)vehiclesList.size();i++){
            if(ui->lineEdit_4->text()==vehiclesList[i]->getLicense()){
                message.setText(toString());
                message.exec();
                ui->lineEdit_4->clear();
                break;

            }else{
                //message.setText("The License Plate does not exist");
                //message.exec();
            }
        }
    }else{
        message.setText("You must insert a License Plate!");
        message.exec();
    }
}

//When motor check box is cliked, we open the power motor option
void MainWindow::on_checkBox_4_clicked(){
    if(ui->checkBox_4->isChecked()==true){
        ui->spinBox->setVisible(true);
        ui->horizontalSlider->setVisible(true);
    }else{
        ui->spinBox->setValue(0);
        ui->spinBox->hide();
        ui->horizontalSlider->hide();
    }
}

//When fuel check box is clicked, a combo box furl type is opened
void MainWindow::on_checkBox_5_clicked(){
    if(ui->checkBox_5->isChecked()==true){
        ui->comboBox_2->setVisible(true);
    }else{
        ui->comboBox_2->hide();
    }
}

//When wagons check box if clicked, the number of wagons option is shown
void MainWindow::on_checkBox_2_clicked(){
    if(ui->checkBox_2->isChecked()==true){
        ui->spinBox_2->setVisible(true);
    }else{
        ui->spinBox_2->setValue(0);
        ui->spinBox_2->hide();
    }
}

QString MainWindow::toString(){
    QString result;
    QMessageBox message;

    result="Features of the Vehicle \n\n";
    for(int i=0;i<(int)vehiclesList.size();i++){
        if(ui->lineEdit_4->text()==vehiclesList[i]->getLicense()){
            result.append("Name of the Vehicle: "+vehiclesList[i]->getName()+"\n");
            result.append("License Plate: "+vehiclesList[i]->getLicense()+"\n");
            result.append("Number of Wheels: "+vehiclesList[i]->getWheels()+"\n");
            if(vehiclesList[i]->getMotor()!=false){
                result.append("Motor: Yes, and the its cv are: "+QString::number(vehiclesList[i]->getMotorPower())+"\n");
            }else{
                result.append("Motor: No\n");
            }

            if(vehiclesList[i]->getFuel()!=false){
                result.append("Fuel: Yes, and the its type is: "+vehiclesList[i]->getFuelType()+"\n");
            }else{
                result.append("Fuel: No\n");
            }

            result.append("Color: "+vehiclesList[i]->getColor()+"\n");

            if(vehiclesList[i]->getWings()!=false){
                result.append("Wings: Yes\n");
            }else{
                result.append("Wings: No\n");
            }

            if(vehiclesList[i]->getWagons()!=false){
                result.append("Wagons: Yes, an the total number is: "+QString::number(vehiclesList[i]->getNumWagons())+"\n");
            }else{
                result.append("Wagons: No\n");
            }

            if(vehiclesList[i]->getReactors()!=false){
                result.append("Reactors: Yes\n");
            }else {
                result.append("Reactors: No\n");
            }

            if(vehiclesList[i]->getLocomotiv()!=false){
                result.append("Locomotiv: Yes\n");
            }else {
                result.append("Locomotiv: No\n");
            }

            if(vehiclesList[i]->getUndercarriage()!=false){
                result.append("Undercarriage: Yes\n");
            }else{
                result.append("Undercarriage: No\n");
            }

            if(vehiclesList[i]->getPuntureKit()!=false){
                result.append("Punture Kit: Yes\n");
            }else{
                result.append("Punture Kit: No\n");
            }

            if(vehiclesList[i]->getSpareWheel()!=false){
                result.append("Spare Wheel: Yes\n");
            }else{
                result.append("Spare Wheel: No\n");
            }
        }
    }
    result.append("\n\n");
    return result;
}

