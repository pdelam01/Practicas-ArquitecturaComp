#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <QDialog>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sys/time.h>
#include <time.h>

#include <iostream>
#include <QFileDialog>
#include <fstream>
#include <QMessageBox>

/*FIBONACCI'S HEADER*/
using namespace std;

namespace Ui {
class fibonacci;
}

class fibonacci : public QDialog
{
    Q_OBJECT

/*Public methods*/
public:
    /*Builder and Destructor*/
    explicit fibonacci(QWidget *parent = nullptr);
    ~fibonacci();

    /*Functions*/
    int calcularFibonacci(int pos);

    void setTimeLineEdit(int i, double microsec);

    void setAverageTime();

    bool getValues();

private slots:
    /*Ui Slots functions*/
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    /*Variables*/
    Ui::fibonacci *ui;
    QString file;
    vector <int> sucession;
    vector <int> values;
    vector <double> times;
    QMessageBox message;

};

#endif // FIBONACCI_H
