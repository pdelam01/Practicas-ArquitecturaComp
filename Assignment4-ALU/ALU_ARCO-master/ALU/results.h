#ifndef RESULTS_H
#define RESULTS_H

#include <QDialog>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <QString>

union Code {

    struct{
        unsigned int partFrac : 23;
        unsigned int expo : 8;
        unsigned int sign : 1;
    }bitfield;

    float numero;
    unsigned int numerox;
};

using namespace std;

namespace Ui {
class Results;
}

class Results : public QDialog
{
    Q_OBJECT

public:
    explicit Results(QWidget *parent = nullptr);
    ~Results();

    void mostrarResultados(union Code op1, union Code op2, union Code result);

    QString vectorToString(vector<int> oper);

    Results();

    int convertRealToUnion(float number, float number2, int operation);

    vector<int> convertToBinaryExp(int number, int fracpart, int sign);

    vector<int> convertToBinaryExpResult(int number, int pf, int sign);

    vector<int> operationAddition(union Code op1, union Code op2);

    vector<int> operationProduct(union Code op1, union Code op2);

    vector<int> operationDivision(union Code op1, union Code op2);

    vector<int> complement_A2(vector<int> vec);

    vector<int> complement_A1(vector<int> vec);

    vector<int> returnMantissa();

    vector<int> move0s(vector<int> pe ,int d);

    vector<int> move1s(vector<int> pe ,int d);

    vector<int> mantissaAddition(vector<int> pe);

    vector<int> vectorBinaryAddition(vector<int> a, vector<int> b);

    vector<int> numberToBinary(int n, int size);

    vector<int> moveNbits(int n, bool derecha, vector<int> vector);

    double binaryToDecimal(vector<int> vec);

    double mantissaToDecimal(vector<int> mant);

    vector<int> binaryProductWithoutSign(vector<int> mantA, vector<int> mantB);

    int overflowProduct(int exponente);

    vector<int> treatmentDenormals(vector<int> exp,  vector<int> p);

    void cleanVectors();



private:
    Ui::Results *ui;

    double total = 0.0;
    vector<int> vectorIEEE;

    union Code res;
    vector <int> operator1;
    vector <int> operator2;

    bool NaN = false;
    bool inf = false;

    int c1;

    struct{
          int sign;
          vector<int>  exponent;
          vector<int>  mantissa;
          vector<int>  partfracc;
    }result;
};

#endif // RESULTS_H
