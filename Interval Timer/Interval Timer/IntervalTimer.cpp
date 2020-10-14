#include "IntervalTimer.h"

IntervalTimer::IntervalTimer(QWidget *parent)
    : QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	// call out GUI objects created in ui_MainWindow.h
	ui->setupUi(this);
}

/* Deconstructor */
IntervalTimer::~IntervalTimer()
{
	delete ui;
}
