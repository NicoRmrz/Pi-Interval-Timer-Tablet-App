#include "IntervalTimer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IntervalTimer w;
    w.show();
    //w.showFullScreen();
    return a.exec();
}
