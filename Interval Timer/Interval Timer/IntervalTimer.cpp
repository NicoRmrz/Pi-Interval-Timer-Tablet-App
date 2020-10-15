#include "IntervalTimer.h"
#include "GUI_Stylesheet.h"


/* Define: IntervalTimer

    IntervalTimer Main Window
 */
IntervalTimer::IntervalTimer(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    GUI_Style(parent)
{
	// call out GUI objects created in ui_MainWindow.h
	ui->setupUi(this);

    // style all objects
    setStyleSheet(GUI_Style.mainWindow);

}

/* Deconstructor */
IntervalTimer::~IntervalTimer()
{
	delete ui;
}
