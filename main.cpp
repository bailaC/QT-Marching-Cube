#include "mainwindow.h"

#include <QApplication>
MainWindow *w;
int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    w = new MainWindow();

    w->show();
//    w.height();
//    w.setGeometry(QRect(50,50,128,128));
    return a.exec();
}
