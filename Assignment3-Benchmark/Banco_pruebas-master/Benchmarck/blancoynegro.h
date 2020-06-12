#ifndef BLANCOYNEGRO
#define BLANCOYNEGRO

#include <QDialog>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sys/time.h>
#include <time.h>
#include <iostream>

#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDirIterator>

using namespace std;

/*BLANCOYNEGRO'S HEADER*/

namespace Ui {
class blancoYnegro;
}

class blancoYnegro : public QDialog
{
    Q_OBJECT

    /*Public methods*/
public:
    /*Builder and Destructor*/
    explicit blancoYnegro(QWidget *parent = nullptr);
    ~blancoYnegro();

    /*Functions*/
    void setTimeLineEdit(int i, double microsec);

    void setAverageTime();

    void pictureChangeColor();

    void imageToPixmap();

private slots:
    /*Ui Slots functions*/
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    /*Variables*/

    Ui::blancoYnegro *ui;
    vector <double> times;
    QString file,dir;
    QFileDialog *fileDlg;
    QImage image;
    QPixmap pixmap;
    vector <QImage> images;
    vector <QString> fileNames;
    vector <QPixmap> pixmaps;
    QMessageBox message;
    int count = 0;
};

#endif // BLANCOYNEGRO.H
