#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOverrideCursor( QCursor( Qt::BlankCursor ) );

    MainWindow w;
    //w.show();
    w.showFullScreen();
    return a.exec();
}
