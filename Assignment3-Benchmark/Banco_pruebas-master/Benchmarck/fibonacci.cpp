#include "fibonacci.h"
#include "ui_fibonacci.h"

/*
*
* Constructor of the class
*
* @parameters QWidget
* @return void
*/
fibonacci::fibonacci(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fibonacci)
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
fibonacci::~fibonacci()
{
    delete ui;
}

/*
 *
 * Fibonacci's Methods
 * The value of the fibonacci series will be calculated from the position given by the user
 *
 * @parameters int
 * @return int
 */
int fibonacci::calcularFibonacci(int pos)
{
    this->sucession.push_back(0);
    this->sucession.push_back(1);
    int suma = 0;
    for(int i=2; i<pos; i++){
        suma = sucession[i-2]+sucession[i-1];
        sucession.push_back(suma);
    }
    return sucession[pos-1];
}


/*
 *
 * Calculate Button. Calls the function fo fibonacci and calculates the times storing them in an array.
 * If there is no file does nothing
 *
 * @parameters void
 * @return void
 */
void fibonacci::on_pushButton_clicked()
{

    clock_t clock_init, clock_end;
    double seconds, microseconds;
    bool ex = getValues();

    if (ex == true) {
        for (int i=0;i<5;i++) {
            clock_init=clock();
            calcularFibonacci(values[i]);
            clock_end=clock();

            seconds = (double)(clock_end-clock_init)/(double)CLOCKS_PER_SEC;
            microseconds = (double)seconds*1000000.00;
            setTimeLineEdit(i, microseconds);
            times.push_back(microseconds);
        }

        setAverageTime();
    }
}


/*
 *
 * Reset button. It clears the whole interface, times, and average time.
 *
 * @parameters void
 * @return void
 */
void fibonacci::on_pushButton_3_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
}

/*
 *
 * Sets all the LineEdit's time to the value that has been calculated before
 *
 * @parameters int, double
 * @return void
 */
void fibonacci::setTimeLineEdit(int i, double microsec){

    switch (i) {

        case 0:
            ui->lineEdit->setText(QString::number(microsec)+" μs");
            break;
        case 1:
            ui->lineEdit_5->setText(QString::number(microsec)+" μs");
            break;
        case 2:
            ui->lineEdit_4->setText(QString::number(microsec)+" μs");
            break;
        case 3:
            ui->lineEdit_3->setText(QString::number(microsec)+" μs");
            break;
        case 4:
            ui->lineEdit_2->setText(QString::number(microsec)+" μs");
            break;
    }
}

/*
 *
 * Calculates the average time of  the whole calculation.
 * Then sets that value to the Average's LineEdit.
 *
 * @parameters void
 * @return void
 */
void fibonacci::setAverageTime(){

    double average=0.0;
    for (int i=0;i<(int)times.size();i++) {
        average += times[i];
    }
    average = average/(double)times.size();

    ui->lineEdit_6->setText(QString::number(average)+" μs");

}

/*
 *
 * Gets the values of a .txt file, reads it and storages in values's array
 *
 * @parameters void
 * @return void
 */
bool fibonacci::getValues(){

    bool exit = false;
    this->file= QFileDialog::getOpenFileName(this,tr("Select a Txt"), QDir::homePath(),tr("Txt Files (*.txt)"));
    if (this->file.isEmpty() || this->file.isNull()) {
        message.setText("ERROR! You have to choose a file.");
        message.exec();
    }else{
        char letters[128];

        ifstream fe((this->file.toLatin1()));
        while (!fe.eof()) {
            fe>>letters;
            std::string chain = letters;

            values.push_back(std::stoi(chain));
        }
        fe.close();
        exit=true;
    }
    return exit;

}
