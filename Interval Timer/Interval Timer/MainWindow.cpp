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

    // style all objects
    setStyleSheet(GUI_Style.mainWindowGrey);
    ui->statusbar->setStyleSheet(GUI_Style.statusBar);


    // connect signals 
    connect(ui->maingPage->showIntervalTimer, &QPushButton::pressed, this, &MainWindow::intervalTimerButton_Pressed);
    connect(ui->maingPage->showIntervalTimer, &QPushButton::released, this, &MainWindow::intervalTimerButton_Released);
    connect(ui->maingPage->situationalBtn, &QPushButton::pressed, this, &MainWindow::situationalButton_Pressed);
    connect(ui->maingPage->situationalBtn, &QPushButton::released, this, &MainWindow::situationalButton_Released);
}

/* Function: intervalTimerButton_Pressed

        Slot to handle interval timer button being pressed
*/
void MainWindow::intervalTimerButton_Pressed()
{
    // color button grey indicating pressed button
    ui->maingPage->showIntervalTimer->setStyleSheet(GUI_Style.buttonPressed);
}

/* Function: intervalTimerButton_Released

        Slot to handle interval timer button is released. 
*/
void MainWindow::intervalTimerButton_Released()
{
    setStyleSheet(GUI_Style.mainWindowIdle);

    ui->maingPage->showIntervalTimer->setStyleSheet(GUI_Style.intervalTimerBtn);

    showIntervalTimer();
}

/* Define: showIntervalTimer

        Show IntervalTimer app on Main Window

 */
void MainWindow::showIntervalTimer()
{
    // remove main window widget
    ui->mainLayout->removeWidget(ui->centralwidget);
    delete (ui->maingPage);
    ui->maingPage = NULL;

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

/* Function: situationalButton_Pressed

        Slot to handle situational button being pressed
*/
void MainWindow::situationalButton_Pressed()
{
    // color button grey indicating pressed button
    ui->maingPage->showIntervalTimer->setStyleSheet(GUI_Style.buttonPressed);
}

/* Function: situationalButton_Released

        Slot to handle situational button is released.
*/
void MainWindow::situationalButton_Released()
{
    setStyleSheet(GUI_Style.mainWindowIdle);

    ui->maingPage->showIntervalTimer->setStyleSheet(GUI_Style.intervalTimerBtn);

    showSituationalGame();
}


/* Define: showSituationalGame

        Show Situational app on Main Window

 */
void MainWindow::showSituationalGame()
{
    // remove main window widget
    ui->mainLayout->removeWidget(ui->centralwidget);
    delete (ui->maingPage);
    ui->maingPage = NULL;

    situationalWidget = new situationalGame(this);

    // add timer interal app widget
    ui->mainLayout->addWidget(situationalWidget);
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
    ui->maingPage = new mainScreen(this);
    ui->mainLayout->addWidget(ui->maingPage);
    setStyleSheet(GUI_Style.mainWindowGrey);

    // connect signals 
    connect(ui->maingPage->showIntervalTimer, &QPushButton::pressed, this, &MainWindow::intervalTimerButton_Pressed);
    connect(ui->maingPage->showIntervalTimer, &QPushButton::released, this, &MainWindow::intervalTimerButton_Released);
    connect(ui->maingPage->situationalBtn, &QPushButton::pressed, this, &MainWindow::situationalButton_Pressed);
    connect(ui->maingPage->situationalBtn, &QPushButton::released, this, &MainWindow::situationalButton_Released);
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
