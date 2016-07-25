#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inputdimension.h"
#include "inputbgcolour.h"
#include <iostream>

extern int drawingmode;
extern int modeldirty;
extern int showaxes, showgrid;
extern XYZ autospin;
extern int autorampiso;
extern VOLUME grid;
extern int pointlinesize;
extern int colourmap;
extern bool pressCancel;
extern int showbbox;
extern float alphaBlending;
extern GLfloat bgColour[3];
extern COLOUR constcolour;


QString filePath = QDir::homePath();


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Marching Cube Viewer");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_clicked()
{
    showaxes = !showaxes;
}

void MainWindow::on_checkBox_2_clicked()
{
    showgrid = !showgrid;
}

void MainWindow::on_checkBox_3_clicked()
{
    if (autospin.x != 0 || autospin.y != 0 || autospin.z != 0) {
            autospin.x = 0; autospin.y = 0; autospin.z = 0;
         } else {
            autospin.x = 1; autospin.y = 0; autospin.z = 0;
         }
}

void MainWindow::on_checkBox_4_clicked()
{
    autorampiso = !autorampiso;
}

void MainWindow::on_Grid_resolution_comboBox_activated(int index)
{
    grid.resolution = index;
    UpdateResolution(0);
}

void MainWindow::on_Point_size_comboBox_activated(int index)
{
    pointlinesize = index;
    modeldirty = GEOMDIRTY;
}

void MainWindow::on_Colour_map_comboBox_activated(int index)
{
    int i,r,g,b;
    index++;
    if(index == 14) {
        index = 100;
    }

    colourmap = index;

    if (colourmap == 100) {
       constcolour.r = r / 255.0;
       constcolour.g = g / 255.0;
       constcolour.b = b / 255.0;
    }
      modeldirty = GEOMDIRTY;
}

void MainWindow::on_Camera_combo_activated(int index)
{
    CameraHome(++index);
}

void MainWindow::on_Drawing_mode_comboBox_activated(int index)
{
    drawingmode = ++index;
    modeldirty = GEOMDIRTY;
}

void MainWindow::on_browse_pushButton_clicked()
{

    InputDimension *inp = new InputDimension(this);
    inp ->exec();
    delete inp;


    if (!pressCancel) {
        QString fileName = QFileDialog::getOpenFileName(
                    this,
                    "Open Volume File",
                    filePath
                    );
        if (fileName != "") {
            QByteArray ba = fileName.toLatin1();
            char *c_str2 = ba.data();
            if (!ReadVolume(c_str2)) {
                QMessageBox::critical(this, "Error", "Unable to open volume file");
            } else {
                CalcBounds();
                UpdateResolution(0);
                CameraHome(0);
                this->ui->filepath_Edit->setText(fileName);
            }
            filePath = QFileInfo(fileName).absoluteDir().absolutePath();
        }
        this->ui->HorizontalSlider->setValue(grid.isolevel);
    } else {
        pressCancel = false;
    }
}

void MainWindow::on_filepath_Edit_returnPressed()
{
    QString fileName = this->ui->filepath_Edit->text();
    if (fileName != "") {
        InputDimension *inp = new InputDimension(this);
        inp ->exec();
        delete inp;
        QByteArray ba = fileName.toLatin1();
        char *c_str2 = ba.data();
        if (!ReadVolume(c_str2)) {
            QMessageBox::critical(this, "Error", "Unable to open volume file");
        } else {
            CalcBounds();
            UpdateResolution(0);
            CameraHome(0);
            this->ui->filepath_Edit->setText(fileName);
        }
        filePath = QFileInfo(fileName).absoluteDir().absolutePath();
    }
}

void MainWindow::on_checkBox_5_clicked()
{
    showbbox = !showbbox;
}

void MainWindow::on_HorizontalSlider_valueChanged(int value)
{
    grid.isolevel = value;
    modeldirty = GEOMDIRTY;
}



void MainWindow::on_opacitySlider_sliderMoved(int position)
{
    alphaBlending = (float) position / 10;
    modeldirty = GEOMDIRTY;
}

void MainWindow::on_Background_comboBox_activated(int index)
{
    switch(index) {
        case 0:
            bgColour[0] = 0.0;
            bgColour[1] = 0.0;
            bgColour[2] = 0.0;
            break;

        case 1:
            bgColour[0] = 1.0;
            bgColour[1] = 1.0;
            bgColour[2] = 1.0;
            break;

        case 2:
            bgColour[0] = 0.65;
            bgColour[1] = 0.65;
            bgColour[2] = 0.65;
            break;

        case 3:
            InputBGColour *inp = new InputBGColour(this);
            inp ->exec();
            delete inp;
            break;
    }
}
