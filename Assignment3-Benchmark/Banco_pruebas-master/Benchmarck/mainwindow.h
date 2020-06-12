#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>

#include <fibonacci.h>
#include <blancoynegro.h>

using namespace std;

#include <QMainWindow>

/*MAINWINDOW'S HEADER*/

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    /*Public Methods*/
public:
    /*Builder and Destructor*/
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /*Ui Slots functions*/
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    /*Variables*/
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
