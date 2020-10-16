#include "MainWindow.h"
#include "GUI_Stylesheet.h"

/* Define: IntervalTimer

    IntervalTimer app Main Window
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    GUI_Style(parent)
{
	// call out GUI objects created in ui_MainWindow.h
	ui->setupUi(this);

    // instantiate pages
    IntervalTimerWidget = new IntervalTimer(parent);

    // style all objects
    setStyleSheet(GUI_Style.mainWindowGrey);
    ui->statusbar->setStyleSheet(GUI_Style.statusBar);
    ui->showIntervalTimer->setStyleSheet(GUI_Style.intervalTimerBtn);

    // connect signals 
    connect(ui->showIntervalTimer, &QPushButton::pressed, this, &MainWindow::intervalTimerButton_Pressed);
    connect(ui->showIntervalTimer, &QPushButton::released, this, &MainWindow::intervalTimerButton_Released);

}

/* Function: intervalTimerButton_Pressed

        Slot to handle interval timer button being pressed
*/
void MainWindow::intervalTimerButton_Pressed()
{
    // color button grey indicating pressed button
    ui->showIntervalTimer->setStyleSheet(GUI_Style.buttonPressed);
}

/* Function: intervalTimerButton_Released

        Slot to handle interval timer button is released. 
*/
void MainWindow::intervalTimerButton_Released()
{
    setStyleSheet(GUI_Style.mainWindowIdle);

    ui->showIntervalTimer->setStyleSheet(GUI_Style.intervalTimerBtn);

    showIntervalTimer();
}

/* Define: showIntervalTimer

        Show IntervalTimer app on Main Window

 */
void MainWindow::showIntervalTimer()
{
    // remove main window widget
    ui->mainLayout->removeWidget(ui->centralwidget);
    delete (ui->showIntervalTimer);
    ui->showIntervalTimer = NULL;

    // add timer interal app widget
    ui->mainLayout->addWidget(IntervalTimerWidget);

    connect(IntervalTimerWidget, &IntervalTimer::intervalState, this, &MainWindow::updateTimerState);
}

/* Define: IntervalTimer

    IntervalTimer app 

Parameters:

    state - timer state. Rest (0) and Rolling (1)
 */
void MainWindow::updateTimerState(int state)
{
   // if (IntervalTimerWidget->state == 0) // Rest
    if (state == 0) // Rest
    {
        setStyleSheet(GUI_Style.mainWindowRest);
    }
    else // Rolling
    {
        setStyleSheet(GUI_Style.mainWindowRoll);
    }
}

/* Function: closeEvent

        To Perform closing events when application is closed.
        Terminates all threads.

   Paramters:

       event - event triggered sent when application is closed
*/
void MainWindow::closeEvent(QCloseEvent *event)
{
   /* cvThread.terminate();
    cvThread.wait(100);*/

}

/* Deconstructor */
MainWindow::~MainWindow()
{
	delete ui;
}
