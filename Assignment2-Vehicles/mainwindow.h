#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "vehicle.h"
#include <vector>
#include <QMainWindow>


using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    vector<vehicle*> vehiclesList;


private slots:
    //License plate
    void on_pushButton_clicked();
    //Creating the vehicle
    void on_pushButton_2_clicked();
    //Seing the features
    void on_pushButton_3_clicked();

    void on_checkBox_4_clicked();
    void on_checkBox_5_clicked();
    void on_checkBox_2_clicked();

    QString toString();

private:
    Ui::MainWindow *ui;
    QString name,fuelType,color,licensePlate,wheels,wagons;
    int motorPower,numWagons;
    bool motor,fuel,wings,reactors,undercarriage,locomotiv,spareWheel,puntureKit;

};
#endif // MAINWINDOW_H

