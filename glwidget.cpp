#include "glwidget.h"
#include <QSize>
#include <QByteArray>
#include <GL/glu.h>
#include "opengl/paulslib.h"

/* Global Flags */
extern int debug;
int currentbutton = -1;
extern int modeldirty;
extern int stereo;
extern int showhistogram;
extern int autorampiso;
extern XYZ autospin; /* 0, 1, or -1 for still, left, right */
extern int windowdump;
extern int movierecord;
extern GLfloat bgColour[3];
///* Camera variables */
extern CAMERA camera;


///* Grid globals */
extern VOLUME grid;

///* Drawing mode */
extern double framerate;


using namespace std;


GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(0);

//    timer -> start(VALUE);
}


void GLWidget::initializeGL(){
    int i;
    int argc;
    char** argv;
    char volname[64];

        /* Initialise things */
        volname[0] = '\0';
        grid.data = NULL;
        grid.Nx = 50; grid.Ny = 50; grid.Nz = 50;
        grid.Rx = 2; grid.Ry = 2; grid.Rz = 2;
        grid.resolution = 2;
        grid.Dx = 1; grid.Dy = 1; grid.Dz = 1;
        grid.isolevel = 256;
        HandleDataMenu(10);

        camera.screenwidth = 800;
        camera.screenheight = 600;
        CreateEnvironment();

        /* Read data */
        if (strlen(volname) > 0) {
            ReadVolume(volname);
        CalcBounds();
        UpdateResolution(0);
        }

        /* Ready to go! */
        if (debug)
            fprintf(stderr,"Starting\n");
        CameraHome(0);
}

void GLWidget::paintGL() {

    int i,j;
    XYZ r,eyepos;
    double dist,ratio,radians,scale,wd2,ndfl;
    double near,far;
    double left,right,top,bottom;
    static int framecount = -1;
    static double tstart,tstop;         /* Frame rate calculations */

    glClearColor(bgColour[0], bgColour[1], bgColour[2], 0.0);
    /* Set the time the first time around */
    if (framecount < 0) {
      framecount = 0;
      tstart = GetRunTime();
    }
    framecount++;

    /* Clip to avoid extreme stereo */
    near = 0.1;
    far = 2*(grid.Nx*grid.Dx+grid.Ny*grid.Dy+grid.Nz*grid.Dz);
    if (stereo)
      near = camera.focallength / 5;

    /* Misc stuff */
    ratio  = camera.screenwidth / (double)camera.screenheight;
    radians = DTOR * camera.aperture / 2;
    wd2     = near * tan(radians);
    ndfl    = near / camera.focallength;

    /* Are we in autospin mode */
    if ((int)autospin.x != 0)
      RotateCamera(autospin.x/2,0.0,0.0,KEYBOARDCONTROL);
    if ((int)autospin.y != 0)
      RotateCamera(0.0,autospin.y/2,0.0,KEYBOARDCONTROL);
    if ((int)autospin.z != 0)
      RotateCamera(0.0,0.0,autospin.z/2,KEYBOARDCONTROL);

    /* Are we in autospin isolevel mode */
    if (autorampiso != 0) {
        grid.isolevel += autorampiso;
        if (grid.isolevel > grid.themax)
            grid.isolevel = grid.themin;
        if (grid.isolevel < grid.themin)
            grid.isolevel = grid.themax;


        modeldirty = GEOMDIRTY;
    }

    /* Derive the the "right" vector */
    CROSSPROD(camera.vd,camera.vu,r);
    Normalise(&r);
    r.x *= camera.eyesep / 2.0;
    r.y *= camera.eyesep / 2.0;
    r.z *= camera.eyesep / 2.0;

    /* Do we need to create the geometry */
    MakeGeometry();

    /* Clear the buffers */
    glDrawBuffer(GL_BACK_LEFT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (stereo) {
      glDrawBuffer(GL_BACK_RIGHT);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    if (stereo) {

      /* Derive the two eye positions */
      CROSSPROD(camera.vd,camera.vu,r);
      Normalise(&r);
      r.x *= camera.eyesep / 2.0;
      r.y *= camera.eyesep / 2.0;
      r.z *= camera.eyesep / 2.0;
        eyepos = VectorAdd(camera.vp,r);

      glMatrixMode(GL_MODELVIEW);
      glDrawBuffer(GL_BACK_RIGHT);
      glLoadIdentity();
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      left  = - ratio * wd2 - 0.5 * camera.eyesep * ndfl;
      right =   ratio * wd2 - 0.5 * camera.eyesep * ndfl;
      top    =   wd2;
      bottom = - wd2;
      glFrustum(left,right,bottom,top,near,far);
      gluLookAt(eyepos.x,eyepos.y,eyepos.z,
                eyepos.x + camera.vd.x,
                eyepos.y + camera.vd.y,
                eyepos.z + camera.vd.z,
                camera.vu.x,camera.vu.y,camera.vu.z);
        MakeEnv();
      glCallList(1);
        DrawExtras();

      glMatrixMode(GL_MODELVIEW);
      glDrawBuffer(GL_BACK_LEFT);
      glLoadIdentity();
      eyepos = VectorSub(r,camera.vp);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      left  = - ratio * wd2 + 0.5 * camera.eyesep * ndfl;
      right =   ratio * wd2 + 0.5 * camera.eyesep * ndfl;
      top    =   wd2;
      bottom = - wd2;
      glFrustum(left,right,bottom,top,near,far);
      gluLookAt(eyepos.x,eyepos.y,eyepos.z,
                eyepos.x + camera.vd.x,
                eyepos.y + camera.vd.y,
                eyepos.z + camera.vd.z,
                camera.vu.x,camera.vu.y,camera.vu.z);
        MakeEnv();
      glCallList(1);
        DrawExtras();

    } else {

      glMatrixMode(GL_MODELVIEW);
      glDrawBuffer(GL_BACK_LEFT);
      glLoadIdentity();
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      left  = - ratio * wd2;
      right =   ratio * wd2;
      top    =   wd2;
      bottom = - wd2;
      glFrustum(left,right,bottom,top,near,far);
      gluLookAt(camera.vp.x,camera.vp.y,camera.vp.z,
                camera.vp.x + camera.vd.x,
                camera.vp.y + camera.vd.y,
                camera.vp.z + camera.vd.z,
                camera.vu.x,camera.vu.y,camera.vu.z);
        MakeEnv();
        glCallList(1);
        DrawExtras();
    }

    /* Optionally dump image */
    if (windowdump || movierecord) {
        WindowDump("",camera.screenwidth,camera.screenheight,stereo,-5);
        windowdump = FALSE;
    }

    /* Let's look at it */
//    glutSwapBuffers();

    /* Frame rate calculations */
    tstop = GetRunTime();
    if (tstop - tstart > 5) {
      framerate = framecount / (tstop - tstart);
      if (debug)
         fprintf(stderr,"Frame rate = %.1f frames/second\n",framerate);
      framecount = 0;
      tstart = tstop;
    }

//    updateGL();
}

void GLWidget::resizeGL(int w, int h) {

}


/* -------------------- Event Handler ------------------- */


/*
   Handle mouse events
    Right button events are passed to menu handlers
*/
void GLWidget::mousePressEvent(QMouseEvent *event) {
    if (showhistogram)
        HistogramClick(event->pos().x(),camera.screenheight-event->pos().y());

    if (event->button() == Qt::LeftButton) {
        currentbutton = Qt::LeftButton;
    } else if (event->button() == Qt::MiddleButton) {
        currentbutton = Qt::MiddleButton;
    }
}

/*
   Handle mouse motion
*/
void GLWidget::mouseMoveEvent(QMouseEvent *event) {

    static int xlast=-1,ylast=-1;
    int dx,dy, x = event->pos().x(), y = event->pos().y();

    dx = x - xlast;
    dy = y - ylast;
    if (dx < 0)      dx = -1;
    else if (dx > 0) dx =  1;
    if (dy < 0)      dy = -1;
    else if (dy > 0) dy =  1;

    if (currentbutton == Qt::LeftButton) {
       RotateCamera(-(double)dx,(double)dy,0.0,MOUSECONTROL);
    } else if (currentbutton == Qt::MiddleButton) {
       RotateCamera(0.0,0.0,(double)dx,MOUSECONTROL);
    }

    xlast = x;
    ylast = y;
}

/*
 * Handle scroll event
*/
void GLWidget::wheelEvent(QWheelEvent *event) {
    if (event -> delta() > 0) {
        FlyCamera(5);
    } else {
        FlyCamera(-5);
    }
}

void GLWidget::timerEvent(QTimerEvent*) {
//    update();
}
