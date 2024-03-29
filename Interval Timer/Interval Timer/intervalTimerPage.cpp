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



QString switchTimer = "cvlc /home/pi/Pi-Interval-Timer-Tablet-App/sounds/menu_done.wav";
QString tone1 = "cvlc /home/pi/Pi-Interval-Timer-Tablet-App/sounds/switchtimer.wav";
QString buzzer = "cvlc /home/pi/Pi-Interval-Timer-Tablet-App/sounds/buzzer.wav";

using namespace std;

/* Constructor: IntervalTimer

        Lays out all objects for the Interval Timer page

    Parameters:

        parent - Inherits QWidget attributes
*/
IntervalTimer::IntervalTimer(QWidget *parent) 
{
	setFixedSize(QSize(parent->size()));

    pauseSec = 0;
    pauseMin = 0;

	// Instance modules
	currTimer = new timerReading(this);

    playSound(switchTimer);

    // start on roll state. Rest = 0, Roll = 1
    isRunning = false;

    // create objects
    exeTimer = new QLabel(parent);
    exeTimer->setObjectName(QString::fromUtf8("exeTimer"));
    exeTimer->setText("00:00");

	timerStateLabel = new QLabel(parent);
	timerStateLabel->setObjectName(QString::fromUtf8("timerState"));
	timerStateLabel->setText("");

    startBtn = new QPushButton(parent);
    startBtn->setObjectName(QString::fromUtf8("startBtn"));
    startBtn->setMinimumSize(ICONSIZE, ICONSIZE);
    startBtn->setMaximumSize(ICONSIZE, ICONSIZE);
    startBtn->setIconSize(QSize(ICONSIZE, ICONSIZE));
    startBtn->setFocusPolicy(Qt::NoFocus);

    restartBtn = new QPushButton(parent);
    restartBtn->setObjectName(QString::fromUtf8("restartBtn"));
    restartBtn->setMinimumSize(ICONSIZE, ICONSIZE);
    restartBtn->setMaximumSize(ICONSIZE, ICONSIZE);
    restartBtn->setIconSize(QSize(ICONSIZE, ICONSIZE));
    restartBtn->setEnabled(false);
    restartBtn->setFocusPolicy(Qt::NoFocus);

    backBtn = new QPushButton(parent);
    backBtn->setObjectName(QString::fromUtf8("back"));
    backBtn->setMinimumSize(BACKICONSIZE, BACKICONSIZE);
    backBtn->setMaximumSize(BACKICONSIZE, BACKICONSIZE);
    backBtn->setIconSize(QSize(BACKICONSIZE, BACKICONSIZE));
    backBtn->setFocusPolicy(Qt::NoFocus);

    editBtn = new QPushButton(parent);
    editBtn->setObjectName(QString::fromUtf8("edit"));
    editBtn->setMinimumSize(BACKICONSIZE, BACKICONSIZE);
    editBtn->setMaximumSize(BACKICONSIZE, BACKICONSIZE);
    editBtn->setIconSize(QSize(BACKICONSIZE, BACKICONSIZE));
    editBtn->setFocusPolicy(Qt::NoFocus);

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
	topBtnLayout->addWidget(timerStateLabel, 0, Qt::AlignCenter);
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
    connect(restartBtn, &QPushButton::released, this, &IntervalTimer::restartButton_Released);
    connect(backBtn, &QPushButton::released, this, &IntervalTimer::backButton_Released);
    connect(editBtn, &QPushButton::released, this, &IntervalTimer::editButton_Released);
    connect(currTimer->myTimer, &QTimer::timeout, this, &IntervalTimer::updateTimerDisplay);
    connect(currTimer, &timerReading::updateColor, this, &IntervalTimer::changeColor);

    // set stylesheet for each object
	parent->setStyleSheet(mainWindowIdle);
    exeTimer->setStyleSheet(mainTimer);
	backBtn->setStyleSheet(backButtonStyle);
	editBtn->setStyleSheet(editButtonStyle);
	restartBtn->setStyleSheet(restartButtonStyle);
    startBtn->setIcon(QIcon(PLAY_ICON));
    startBtn->setStyleSheet(iconOnlyButton);
	timerStateLabel->setStyleSheet(timerState);
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
	        playSound(buzzer);

            setStyleSheet(mainWindowRest);
            emit intervalState(colorState);
			timerStateLabel->setText("REST");
        }
        else // Rolling
        {
	        playSound(buzzer);

            setStyleSheet(mainWindowRoll);
            emit intervalState(colorState);
			timerStateLabel->setText("ROLL");
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
    startBtn->setIcon(QIcon(PAUSE_ICON));
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
		startBtn->setIcon(QIcon(PLAY_ICON));

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
		startBtn->setIcon(QIcon(PAUSE_ICON));
        currTimer->setClock(pauseSec, pauseMin);
        isRunning = true;
        state = 1;
    }
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
    playSound(switchTimer);
}

/* Function: backButton_Released

        Slot to handle back button is released.
*/
void IntervalTimer::backButton_Released()
{
    emit returnPage("timer");
}

/* Function: editButton_Released

        Slot to handle edit button is released.
*/
void IntervalTimer::editButton_Released()
{
	editWindow *editPopup = new editWindow(0);

	editPopup->exec();
}

/* Function: playSound

       PlaySound Tone
*/
void IntervalTimer::playSound(QString sound)
{
    soundProcess = new QProcess(this);
    soundProcess->start(sound);
}
