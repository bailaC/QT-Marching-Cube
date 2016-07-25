#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include "opengl/glvolume.h"



class Histogram : public QGLWidget
{
public:
//    Histogram();
    Histogram (QWidget *parent = 0);

    void initializeGL();
    void paintGL();

    void mousePressEvent(QMouseEvent *);
};

#endif // HISTOGRAM_H
