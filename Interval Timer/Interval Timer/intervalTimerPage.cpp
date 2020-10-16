
/* File: intervalTimerPage.cpp

    Contains functions for IntervalTimer

    Author: Nico Ramirez
*/
#include "intervalTimerPage.h"

#include <QRegularExpression>
#include <QFile>
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
    restSec = 10;
    restMin = 0;
    pauseSec = 0;
    pauseMin = 0;



    // start on roll state. Rest = 0, Roll = 1
    state = 1;
    playToggle = false;

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
    mainVLayout = new QVBoxLayout(parent);
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

    // set stylesheet for each object
    exeTimer->setStyleSheet(GUI_Style.mainTimer);
    setStyleSheet(GUI_Style.mainWindowIdle);

}

/* Define: changeState

    Change State

 */
void IntervalTimer::changeState()
{
    int toMs;
    if (playToggle)
    {
        if (state == 0) // Rest
        {
            setClock(restSec, restMin);

            //delete time;
          /*  time = new QTime(0, restMin, restSec);
            toMs = restMin * 60000 + restSec * 1000;
            QTimer::singleShot(toMs, this, &IntervalTimer::changeState);*/

            setStyleSheet(GUI_Style.mainWindowRest);
            emit intervalState(0);
            state = 1; // change state when done

        }
        else // Rolling
        {
            setClock(rollSec, rollMin);

           // delete time;
            //time = new QTime(0, rollMin, rollSec);
            //toMs = rollMin * 60000 + rollSec * 1000;
            //QTimer::singleShot(toMs, this, &IntervalTimer::changeState);

            setStyleSheet(GUI_Style.mainWindowRoll);
            emit intervalState(1);
            state = 0; // change state when done

        }
    }
}

/* Define: updateTimer

    Update time on timer

 */
void IntervalTimer::updateTimer()
{
    if (playToggle)
    {
        // timer countdown
        time->setHMS(0, time->addSecs(-1).minute(), time->addSecs(-1).second());

        // show timer
        exeTimer->setText(time->toString("mm:ss"));
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
    // set up timer 
    timer = new QTimer(this);
    time = new QTime(0, 0, 5);

    state = 1;
    QTimer::singleShot(5000, this, &IntervalTimer::changeState);

    connect(timer, &QTimer::timeout, this, &IntervalTimer::updateTimer);
    timer->start(1000);
   
    startBtn->setEnabled(false);
    playToggle = true;

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
    if (playToggle) // pause timer
    {
        delete timer;
        timer = new QTimer(this);
        timer->start(1000);
        connect(timer, &QTimer::timeout, this, &IntervalTimer::updateTimer);

        pauseSec = time->second();
        pauseMin = time->minute();
        playToggle = false;
       // timer->stop();

    }
    else // resume timer
    {
        setClock(pauseSec, pauseMin);
       // delete time;
       /* time = new QTime(0, pauseMin, pauseSec);
        int toMs = pauseMin * 60000 + pauseSec * 1000;
        QTimer::singleShot(toMs, this, &IntervalTimer::changeState);*/

        playToggle = true;
       // timer->start();

    }

   // ui->startBtn->setStyleSheet(GUI_Style.intervalTimerBtn);

}

/* Function: setClock

        Slot to set Clock
*/
void IntervalTimer::setClock(int sec, int min)
{
    delete time;
    time = new QTime(0, min, sec);
    int toMs = min * 60000 + sec * 1000;
    QTimer::singleShot(toMs, this, &IntervalTimer::changeState);

}

// Deconstructor
IntervalTimer::~IntervalTimer()
{

}
