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
    setWindowTitle(WINDOW_TITLE);
    setWindowIcon(QIcon(MAIN_ICON));

    // style all objects
    setStyleSheet(GUI_Style.mainWindowGrey);
    ui->statusbar->setStyleSheet(GUI_Style.statusBar);

    // connect signals 
	connect(ui->mainPage, &mainScreen::switchToIntervalPage, this, &MainWindow::showIntervalTimer);
	connect(ui->mainPage, &mainScreen::switchToSituationalPage, this, &MainWindow::showSituationalGame);
}

/* Define: showIntervalTimer

        Show IntervalTimer app on Main Window
 */
void MainWindow::showIntervalTimer()
{
	setStyleSheet(GUI_Style.mainWindowIdle);

    // remove main window widget
    ui->mainLayout->removeWidget(ui->centralwidget);
    delete (ui->mainPage);
    ui->mainPage = NULL;

    IntervalTimerWidget = new IntervalTimer(this);

    // add timer interal app widget
    ui->mainLayout->addWidget(IntervalTimerWidget);

    connect(IntervalTimerWidget, &IntervalTimer::intervalState, this, &MainWindow::updateTimerState);
    connect(IntervalTimerWidget, &IntervalTimer::returnPage, this, &MainWindow::returnToMain);
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

/* Define: showSituationalGame

        Show Situational app on Main Window

 */
void MainWindow::showSituationalGame()
{
	setStyleSheet(GUI_Style.mainWindowIdle);

    // remove main window widget
    ui->mainLayout->removeWidget(ui->centralwidget);
    delete (ui->mainPage);
    ui->mainPage = NULL;

    situationalWidget = new situationalGame(this);

    // add timer interal app widget
    ui->mainLayout->addWidget(situationalWidget);
    connect(situationalWidget, &situationalGame::returnPage, this, &MainWindow::returnToMain);

}

/* Define: returnToMain

        Return to main screen
 */
void MainWindow::returnToMain(QString page)
{
    if (page == "situational")
    {
       // remove page
       ui->mainLayout->removeWidget(situationalWidget);
       delete (situationalWidget);
       situationalWidget = NULL;
    }
    if (page == "timer")
    {
        // remove page
        ui->mainLayout->removeWidget(IntervalTimerWidget);
        delete (IntervalTimerWidget);
        IntervalTimerWidget = NULL;
    }

    // revert to main page
    ui->mainPage = new mainScreen(this);
    ui->mainLayout->addWidget(ui->mainPage);
    setStyleSheet(GUI_Style.mainWindowGrey);

    // connect signals 
	connect(ui->mainPage, &mainScreen::switchToIntervalPage, this, &MainWindow::showIntervalTimer);
	connect(ui->mainPage, &mainScreen::switchToSituationalPage, this, &MainWindow::showSituationalGame);
}

/* Function: sendStatusBar

        To send the status bar a message

   Paramters:

       message - message to be sent to the bottom status bar
       time - time in ms for how long the message will be displayed
*/
void MainWindow::sendStatusBar(QString message, int time)
{
    ui->statusbar->setStyleSheet(GUI_Style.statusBar);
    ui->statusbar->showMessage(message, time);
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
