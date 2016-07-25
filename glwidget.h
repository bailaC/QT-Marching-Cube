#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include "opengl/glvolume.h"

class GLWidget : public QGLWidget
{
//    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);


    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void timerEvent(QTimerEvent*);


    void HandleDisplay(void);
//    void CreateEnvironment(void);
    void CreateWorld(void);
//    void MakeGeometry(void);
    void MakeLighting(void);
//    void DrawExtras(void);
//    void MakeEnv(void);
//    int  ReadVolume(char *);
    int  SaveVolume(char *);
    void HandleKeyboard(unsigned char key,int x, int y);
    void HandleSpecialKeyboard(int key,int x, int y);
    void HandleMouse(int,int,int,int);
    void HandleVisibility(int vis);
    void HandleReshape(int,int);
//    void HandleMouseMotion(int,int);
    void HandlePassiveMotion(int,int);
    void HandleTimer(int);
//    void RotateCamera(double,double,double,int);
    void TranslateCamera(int,int);
//    void CameraHome(int);
//    void FlyCamera(int);
//    void MallocGrid(int,int,int);
//    void CalcBounds(void);
//    void UpdateResolution(int);
};

#endif // GLWIDGET_H
