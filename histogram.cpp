#include "histogram.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inputdimension.h"
#include "inputbgcolour.h"


extern int colourmap;
extern CAMERA camera;
extern MainWindow *w;
extern VOLUME grid;

Histogram::Histogram(QWidget *parent) :
    QGLWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(0);
}


void Histogram::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
    glDisable(GL_DITHER);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(1.0);
    glPointSize(1.0);
    glClearColor(0.0,0.0,0.0,0.0);


    glViewport(0, 0, 430, 400);


    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
}


void Histogram::paintGL() {
    glDisable(GL_DEPTH_TEST);
    DrawHistogram(colourmap);
    glEnable(GL_DEPTH_TEST);
    w->ui->HorizontalSlider->setMaximum(grid.themax);
    w->ui->HorizontalSlider->setMinimum(grid.themin);
    w->ui->HorizontalSlider->setValue(grid.isolevel);

    QString label;
    w->ui->isoLabel->setStyleSheet("QLabel { background-color : black; color : white; }");
    w->ui->isoLabel->setText(label.setNum(grid.isolevel));

    w->ui->minLabel->setStyleSheet("QLabel { background-color : black; color : yellow; }");
    w->ui->minLabel->setText("Min: " + label.setNum(grid.themin));

    w->ui->maxLabel->setStyleSheet("QLabel { background-color : black; color : red; }");
    w->ui->maxLabel->setText("Max: " + label.setNum(grid.themax));
}


/*
   Handle mouse events
    Right button events are passed to menu handlers
*/
void Histogram::mousePressEvent(QMouseEvent *event) {
    HistogramClick(event->pos().x()+15,event->pos().y());
}
