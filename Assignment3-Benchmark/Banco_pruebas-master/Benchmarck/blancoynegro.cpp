#include "blancoynegro.h"
#include "ui_blancoynegro.h"

/*
*
* Constructor of the class
*
* @parameters QWidget
* @return void
*/
blancoYnegro::blancoYnegro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::blancoYnegro)
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
blancoYnegro::~blancoYnegro()
{
    delete ui;
}

/*
 *
 * Calculate Button. If the image is not selected, ERROR
 * If not, calculates the time of changing the image to black&white for 5 times
 *
 * @parameters void
 * @return void
 */
void blancoYnegro::on_pushButton_clicked()
{

    if(this->images.size()<=0){
        message.setText("ERROR! You must select a folder before!");
        message.exec();
    }else{

        clock_t clock_init, clock_end;
        double seconds, miliseconds;

        for (int i=0;i<5;i++) {
            clock_init=clock();
            pictureChangeColor();
            clock_end=clock();


            seconds= (double)(clock_end-clock_init)/CLOCKS_PER_SEC;
            miliseconds=seconds*1000.00;
            setTimeLineEdit(i, miliseconds);
            times.push_back(miliseconds);
        }
        imageToPixmap();
        setAverageTime();
        ui->label_2->setPixmap(pixmaps[0]);
        count=0;

    }
}

/*
 *
 * Reset button. It clears the whole interface, times, image and average time.
 *
 * @parameters void
 * @return void
 */
void blancoYnegro::on_pushButton_3_clicked()
{
   ui->lineEdit_7->clear();
   ui->lineEdit_8->clear();
   ui->lineEdit_9->clear();
   ui->lineEdit_10->clear();
   ui->lineEdit_11->clear();
   ui->lineEdit_12->clear();
   ui->label_2->clear();
   this->images.clear();
   this->pixmaps.clear();
   this->fileNames.clear();
   this->file.clear();
   ui->label_2->setTextFormat(Qt::RichText);
   ui->label_2->setText("<html><head/><body><p><span style=' font-size:11pt; font-weight:600;'>INSERT AN IMAGE HERE</span></p></body></html>");
   count=0;
}

/*
 *
 * Button that moves backwards in the pixmap array
 *
 * @paremeters void
 * @return void
 */
void blancoYnegro::on_pushButton_6_clicked()
{
    if (count > 0) {
        count --;
        ui->label_2->setPixmap(pixmaps[count]);
    }
}

/*
 *
 * Button that moves forwards in the pixmap array
 *
 * @paremeters void
 * @return void
 */
void blancoYnegro::on_pushButton_7_clicked()
{
    if (count < (int)pixmaps.size()-1) {
        count ++;
        ui->label_2->setPixmap(pixmaps[count]);
    }
}

/*
 *
 * Changes the whole image to black&white using a matriz, going over all
 * the pixels of the image, and changing to gray.
 *
 * @parameters void
 * @return void
 */

void blancoYnegro::pictureChangeColor()
{
    for (int k = 0;k < (int)images.size();k++) {
        for(int i=0; i<images[k].width(); i++){
            for(int j=0; j<images[k].height(); j++){
                int gray = qGray(images[k].pixel(i, j));
                images[k].setPixel(i, j, QColor(gray, gray, gray).rgb());
            }
        }
    }
}

/*
 *
 * Sets all the LineEdit's time to the value that has been calculated before
 *
 * @parameters int, double
 * @return void
 */
void blancoYnegro::setTimeLineEdit(int i, double milisec)
{
    switch (i) {

        case 0:
            ui->lineEdit_7->setText(QString::number(milisec)+" μs");
            break;
        case 1:
            ui->lineEdit_9->setText(QString::number(milisec)+" μs");
            break;
        case 2:
            ui->lineEdit_8->setText(QString::number(milisec)+" μs");
            break;
        case 3:
            ui->lineEdit_10->setText(QString::number(milisec)+" μs");
            break;
        case 4:
            ui->lineEdit_11->setText(QString::number(milisec)+" μs");
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
void blancoYnegro::setAverageTime()
{
    double average=0.0;
    for (int i=0;i<(int)times.size();i++) {
        average += times[i];
    }
    average = average/(double)times.size();

    ui->lineEdit_12->setText(QString::number(average)+" μs");
}

/*
 *
 * Loads the image of the User's computer and sets in the Qlabel's background
 *
 * @parameters void
 * @return void
 */
void blancoYnegro::on_pushButton_4_clicked()
{
    on_pushButton_3_clicked();
    this->dir = this->fileDlg->getExistingDirectory(this,tr("Open Directory"),QDir::homePath());
    if (!this->dir.isEmpty()) {
        QDirIterator dirIter(QFile::encodeName(this->dir).constData(), QDirIterator::Subdirectories);

        while (dirIter.hasNext()) {
            dirIter.next();
            if (QFileInfo(dirIter.filePath()).isFile()) {
                if (QFileInfo(dirIter.filePath()).suffix() == "jpg" || QFileInfo(dirIter.filePath()).suffix() == "png") {
                    this->fileNames.push_back(dirIter.fileName());
                    this->image.load(dirIter.filePath());
                    this->images.push_back(this->image);
                    this->pixmap = QPixmap::fromImage(image);
                    this->pixmaps.push_back(this->pixmap);

                }
            }
        }
        ui->label_2->setPixmap(pixmaps[0]);
    }
}

/*
 *
 * Saves the image in the User's computer got from the Qlabel's background
 *
 * @parameters void
 * @return void
 */
void blancoYnegro::on_pushButton_5_clicked()
{
    if (images.size()>0) {
        this->dir = this->fileDlg->getExistingDirectory(this,tr("Save Directory"),QDir::homePath());
        if (!this->dir.isEmpty()) {
            QString fileSaved;

            for (int i =0;i< (int)images.size();i++) {
                fileSaved = this->dir+"/"+fileNames[i];
                images[i].save(fileSaved);
            }
                      message.setText("The picture was save successfully!");
                      message.exec();
        }
    } else {
        message.setText("ERROR! You must select a folder before!");
        message.exec();
    }
}

/*
 *
 * Changes the images array to a pixmap array
 *
 * @parameters void
 * @return void
 */
void blancoYnegro::imageToPixmap()
{
    for (int i = 0;i < (int)this->images.size(); i++) {
        this->pixmaps[i]=QPixmap::fromImage(images[i]);
    }
}
