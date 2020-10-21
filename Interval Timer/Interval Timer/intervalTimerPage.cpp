/* File: intervalTimerPage.cpp

    Contains functions for IntervalTimer.

    State       Description
    0           Idle State
    1           Timer Running
    2           Timer Paused

    Author: Nico Ramirez
*/
#include "intervalTimerPage.h"

#include <QDebug>
#include <QDialog>

QString backIcon = ":/images/icons/back.png";
QString backIconPressed = ":/images/icons/backPressed.png";
QString playIcon = ":/images/icons/play.png";
QString pauseIcon = ":/images/icons/pause.png";
QString restartIcon = ":/images/icons/restart.png";
QString restartPressedIcon = ":/images/icons/restartPressed.png";
QString editIcon = ":/images/icons/edit.png";
QString editPressedIcon = ":/images/icons/editPressed.png";

using namespace std;

/* Constructor: IntervalTimer

        Lays out all objects for the Interval Timer page

    Parameters:

        parent - Inherits QWidget attributes
*/
IntervalTimer::IntervalTimer(QWidget *parent) :
    GUI_Style(parent)
{
	setFixedSize(QSize(parent->size()));

    pauseSec = 0;
    pauseMin = 0;

	// Instance modules
	currTimer = new timerReading(this);
	//editPopup = new editWindow(*dialog);

    // start on roll state. Rest = 0, Roll = 1
    isRunning = false;

    // create objects
    exeTimer = new QLabel(parent);
    exeTimer->setObjectName(QString::fromUtf8("exeTimer"));
    exeTimer->setText("00:00");

    startBtn = new QPushButton(parent);
    startBtn->setObjectName(QString::fromUtf8("startBtn"));
    startBtn->setMinimumSize(ICONSIZE, ICONSIZE);
    startBtn->setMaximumSize(ICONSIZE, ICONSIZE);
	startBtn->setIcon(QIcon(playIcon));
	startBtn->setIconSize(QSize(ICONSIZE, ICONSIZE));

    restartBtn = new QPushButton(parent);
    restartBtn->setObjectName(QString::fromUtf8("restartBtn"));
    restartBtn->setMinimumSize(ICONSIZE, ICONSIZE);
    restartBtn->setMaximumSize(ICONSIZE, ICONSIZE);
	restartBtn->setIcon(QIcon(restartIcon));
	restartBtn->setIconSize(QSize(ICONSIZE, ICONSIZE));
	restartBtn->setEnabled(false);

    backBtn = new QPushButton(parent);
    backBtn->setObjectName(QString::fromUtf8("back"));
    backBtn->setMinimumSize(BACKICONSIZE, BACKICONSIZE);
    backBtn->setMaximumSize(BACKICONSIZE, BACKICONSIZE);
	backBtn->setIcon(QIcon(backIcon));
	backBtn->setIconSize(QSize(BACKICONSIZE, BACKICONSIZE));

	editBtn = new QPushButton(parent);
	editBtn->setObjectName(QString::fromUtf8("edit"));
	editBtn->setMinimumSize(BACKICONSIZE, BACKICONSIZE);
	editBtn->setMaximumSize(BACKICONSIZE, BACKICONSIZE);
	editBtn->setIcon(QIcon(editIcon));
	editBtn->setIconSize(QSize(BACKICONSIZE, BACKICONSIZE));

    // set layout
	controlBtnLayout = new QHBoxLayout();
	controlBtnLayout->setContentsMargins(0, 0, 0, 20);
	controlBtnLayout->setSpacing(0);
	controlBtnLayout->addWidget(restartBtn, 0, Qt::AlignCenter);
	controlBtnLayout->addWidget(startBtn, 0, Qt::AlignCenter);

	topBtnLayout = new QHBoxLayout();
	topBtnLayout->setContentsMargins(0, 0, 20, 0);
	topBtnLayout->setSpacing(0);
	topBtnLayout->addWidget(backBtn, 0, Qt::AlignLeft);
	topBtnLayout->addWidget(editBtn, 0, Qt::AlignRight);

    mainVLayout = new QVBoxLayout();
    mainVLayout->setContentsMargins(0, 0, 0, 0);
    mainVLayout->setSpacing(0);
    mainVLayout->addLayout(topBtnLayout);
    mainVLayout->addWidget(exeTimer, 0, Qt::AlignCenter);
    mainVLayout->addLayout(controlBtnLayout);

    setLayout(mainVLayout);

    // connect signals
    connect(startBtn, &QPushButton::pressed, this, &IntervalTimer::startButton_Pressed);
    connect(startBtn, &QPushButton::released, this, &IntervalTimer::startButton_Released);
    connect(restartBtn, &QPushButton::pressed, this, &IntervalTimer::restartButton_Pressed);
    connect(restartBtn, &QPushButton::released, this, &IntervalTimer::restartButton_Released);
    connect(backBtn, &QPushButton::pressed, this, &IntervalTimer::backButton_Pressed);
    connect(backBtn, &QPushButton::released, this, &IntervalTimer::backButton_Released);
    connect(editBtn, &QPushButton::pressed, this, &IntervalTimer::editButton_Pressed);
    connect(editBtn, &QPushButton::released, this, &IntervalTimer::editButton_Released);
    connect(currTimer->myTimer, &QTimer::timeout, this, &IntervalTimer::updateTimerDisplay);
    connect(currTimer, &timerReading::updateColor, this, &IntervalTimer::changeColor);

    // set stylesheet for each object
	parent->setStyleSheet(GUI_Style.mainWindowIdle);
    exeTimer->setStyleSheet(GUI_Style.mainTimer);
	backBtn->setStyleSheet(GUI_Style.iconOnlyButton);
	editBtn->setStyleSheet(GUI_Style.iconOnlyButton);
	restartBtn->setStyleSheet(GUI_Style.iconOnlyButton);
	startBtn->setStyleSheet(GUI_Style.iconOnlyButton);
}

/* Define: changeColor

    Receive timer rest/rolling state to Change Color and save state

 */
void IntervalTimer::changeColor(int colorState)
{
    if (isRunning)
    {
        if (colorState == 0) // Rest
        {
            setStyleSheet(GUI_Style.mainWindowRest);
            emit intervalState(colorState);
        }
        else // Rolling
        {
            setStyleSheet(GUI_Style.mainWindowRoll);
            emit intervalState(colorState);
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
	startBtn->setIcon(QIcon(pauseIcon));
}

/* Function: startButton_Released

        Slot to handle start timer button is released.
*/
void IntervalTimer::startButton_Released()
{
    if (state == 0) // IDE - Start Timer
    {
        currTimer->startTimer();  
        isRunning = true;
        state = 1;
        restartBtn->setEnabled(true);
    }
    else if (state == 1) // RUNNING - Press to Pause
    {
		startBtn->setIcon(QIcon(playIcon));

        // get timer time
        QString currTime = currTimer->getTime();
        QStringList  timeSplit = currTime.split(":");

        // save time to class variables
        pauseSec = timeSplit[1].toDouble() + 1;
        pauseMin = timeSplit[0].toDouble();

        // timer paused and next click transistion to state 2
        isRunning = false;
        state = 2;
    }
    else if (state == 2) // PAUSED - Press to resume
    {
		startBtn->setIcon(QIcon(pauseIcon));
        currTimer->setClock(pauseSec, pauseMin);
        isRunning = true;
        state = 1;
    }
}

/* Function: restartButton_Pressed

        Slot to handle restarting the timer button being pressed
*/
void IntervalTimer::restartButton_Pressed()
{
	restartBtn->setIcon(QIcon(restartPressedIcon));
}

/* Function: restartButton_Released

        Slot to handle restarting the timer button is released.
*/
void IntervalTimer::restartButton_Released()
{
	if (currTimer->isRunning == true)
	{
		pauseSec = currTimer->sec;
		pauseMin = currTimer->min;

		QString second = QString::number(currTimer->sec);
		QString minute = QString::number(currTimer->min);

		if (currTimer->sec < 10)
		{
			second = "0" + second;
		}
		if (currTimer->min < 10)
		{
			minute = "0" + minute;
		}

		exeTimer->setText(minute + ":" + second);
	}

    currTimer->restartTimer();
	restartBtn->setIcon(QIcon(restartIcon));
}

/* Function: backButton_Pressed

        Slot to handle backbutton being pressed
*/
void IntervalTimer::backButton_Pressed()
{
    // color button green indicating pressed button
	backBtn->setIcon(QIcon(backIconPressed));
}
/* Function: backButton_Released

        Slot to handle back button is released.
*/
void IntervalTimer::backButton_Released()
{
	backBtn->setIcon(QIcon(backIcon));
    emit returnPage("timer");
}

/* Function: editButton_Pressed

        Slot to handle edit being pressed
*/
void IntervalTimer::editButton_Pressed()
{
	editBtn->setIcon(QIcon(editPressedIcon));

}
/* Function: editButton_Released

        Slot to handle edit button is released.
*/
void IntervalTimer::editButton_Released()
{
	editWindow *editPopup = new editWindow(0);

	editPopup->exec();

	editBtn->setIcon(QIcon(editIcon));
}