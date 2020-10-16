
/* File: intervalTimerPage.cpp

    Contains functions for IntervalTimer

    Author: Nico Ramirez
*/
#include "intervalTimerPage.h"

#include <QDebug>

using namespace std;

/* Constructor: IntervalTimer

        Lays out all objects for the Interval Timer page

    Parameters:

        parent - Inherits QWidget attributes
*/
IntervalTimer::IntervalTimer(QWidget *parent) :
    GUI_Style(parent)

{
    rollSec = 10;
    rollMin = 0;
    restSec = 6;
    restMin = 0;
    pauseSec = 0;
    pauseMin = 0;

	currTimer = new timerReading(this);


    // start on roll state. Rest = 0, Roll = 1
    isRunning = false;

    // create label to be displayed on status bar
    exeTimer = new QLabel(parent);
    exeTimer->setObjectName(QString::fromUtf8("exeTimer"));
    exeTimer->setText("00:00");

    startBtn = new QPushButton(parent);
    startBtn->setObjectName(QString::fromUtf8("startBtn"));
    startBtn->setMinimumSize(100, 90);
    startBtn->setMaximumSize(100, 90);
    startBtn->setText("START");
    startBtn->setEnabled(true);

    pauseResumeBtn = new QPushButton(parent);
    pauseResumeBtn->setObjectName(QString::fromUtf8("pauseResumeBtn"));
    pauseResumeBtn->setMinimumSize(100, 90);
    pauseResumeBtn->setMaximumSize(100, 90);
    pauseResumeBtn->setText("Pause/Resume");

    // set layout
    mainVLayout = new QVBoxLayout();
    mainVLayout->setContentsMargins(0, 0, 0, 0);
    mainVLayout->setSpacing(0);
    mainVLayout->addWidget(exeTimer, 0, Qt::AlignCenter);
    mainVLayout->addWidget(startBtn, 0, Qt::AlignCenter);
    mainVLayout->addWidget(pauseResumeBtn, 0, Qt::AlignCenter);

    setLayout(mainVLayout);

    // connect signals
    connect(startBtn, &QPushButton::pressed, this, &IntervalTimer::startButton_Pressed);
    connect(startBtn, &QPushButton::released, this, &IntervalTimer::startButton_Released);
    connect(pauseResumeBtn, &QPushButton::pressed, this, &IntervalTimer::pauseResumeButton_Pressed);
    connect(pauseResumeBtn, &QPushButton::released, this, &IntervalTimer::pauseResumeButton_Released);
	connect(currTimer->myTimer, &QTimer::timeout, this, &IntervalTimer::updateTimerDisplay);
	connect(currTimer, &timerReading::updateColor, this, &IntervalTimer::changeColor);

    // set stylesheet for each object
    exeTimer->setStyleSheet(GUI_Style.mainTimer);
    setStyleSheet(GUI_Style.mainWindowIdle);
}

/* Define: changeColor

    Change Color

 */
void IntervalTimer::changeColor(int state)
{
    if (isRunning)
    {
        if (state == 0) // Rest
        {
            setStyleSheet(GUI_Style.mainWindowRest);
			emit intervalState(state);
        }
        else // Rolling
        {
            setStyleSheet(GUI_Style.mainWindowRoll);
			emit intervalState(state);
        }
    }
}

/* Define: updateTimerDisplay

    Update time on timer

 */
void IntervalTimer::updateTimerDisplay()
{
    if (isRunning)
    {
        // show timer
        exeTimer->setText(currTimer->getTime());
    }
}

/* Function: startButton_Pressed

        Slot to handle start timer button being pressed
*/
void IntervalTimer::startButton_Pressed()
{
    // color button grey indicating pressed button
   // ui->startBtn->setStyleSheet(GUI_Style.buttonPressed);
}

/* Function: startButton_Released

        Slot to handle start timer button is released.
*/
void IntervalTimer::startButton_Released()
{
	currTimer->startTimer();  // start timer
    startBtn->setEnabled(false);
    isRunning = true;

   // ui->startBtn->setStyleSheet(GUI_Style.intervalTimerBtn);

}

/* Function: pauseResumeButton_Pressed

        Slot to handle pause/resume timer button being pressed
*/
void IntervalTimer::pauseResumeButton_Pressed()
{
    // color button grey indicating pressed button
   // ui->startBtn->setStyleSheet(GUI_Style.buttonPressed);
}

/* Function: pauseResumeButton_Released

        Slot to handle pause/resume timer button is released.
*/
void IntervalTimer::pauseResumeButton_Released()
{
    if (isRunning) // Timer running click to pause
    {
		QString currTime = currTimer->getTime();
		QStringList  timeSplit = currTime.split(":");

        pauseSec = timeSplit[1].toDouble() + 1;
        pauseMin = timeSplit[0].toDouble();
        isRunning = false;
    }
    else // Timer Paused Click to resume timer
    {
		currTimer->setClock(pauseSec, pauseMin);
        isRunning = true;
    }

   // ui->startBtn->setStyleSheet(GUI_Style.intervalTimerBtn);
}


// Deconstructor
IntervalTimer::~IntervalTimer()
{

}
