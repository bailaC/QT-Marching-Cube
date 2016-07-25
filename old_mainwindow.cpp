#include "mainwindow.h"
#include "ui_mainwindow.h"

extern int drawingmode;
extern int modeldirty;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    drawingmode = 6;
    modeldirty = GEOMDIRTY;
}
