#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    if(ui->comboBox->currentText()=="Select an option"){
        this->message.setText("Error! You must select an option.");
        this->message.exec();
    }else{
        if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty()){
            this->message.setText("Error! You must write a real number.");
            this->message.exec();
        }else{
            Results *pd = new Results(this);

            float nu = ui->lineEdit->text().toFloat();
            float nu2 = ui->lineEdit_2->text().toFloat();

            pd->show();

            if (ui->comboBox->currentText()=="Addition") {
                pd->convertRealToUnion(nu, nu2,0);
            }else if (ui->comboBox->currentText()=="Product") {
                pd->convertRealToUnion(nu, nu2, 1);
            }else if (ui->comboBox->currentText()=="Division") {
                pd->convertRealToUnion(nu, nu2, 2);
            }


        }
    }
}
