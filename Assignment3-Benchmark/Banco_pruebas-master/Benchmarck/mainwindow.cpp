#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
*
* Constructor of the class
*
* @parameters QWidget
* @return void
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
}


/*
 *
 *Destructor of the class
 *
 * @parameters void
 * @return void
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*
 *
 * Opens the Fibonacci's Interface
 *
 * @parameters void
 * @return void
 */
void MainWindow::on_pushButton_clicked()
{
    fibonacci pd(this);
    pd.exec();
}

/*
 *
 * Opens the Black&White's Interface
 *
 * @parameters void
 * @return void
 */
void MainWindow::on_pushButton_2_clicked()
{
    blancoYnegro pd(this);
    pd.exec();
}

