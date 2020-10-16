
/* File: timer.cpp

	Contains functions for timer

	Author: Nico Ramirez
*/
#include "timer.h"

#include <QDebug>

using namespace std;


/* Constructor: timerReading

		Lays out all objects for the Interval Timer page

	Parameters:

		parent - Inherits QObject attributes
*/
timerReading::timerReading(QObject *parent) 

{
	state = 0;
	cnt = 0;
	timeSet = 0;
	isRunning = false;
	myTimer = new QTimer();
	eTimer = new QElapsedTimer();
}

/* Function: startTimer

		Slot to start Timer
*/
void timerReading::startTimer()
{
	state = 1;
	cnt = 0;

	// set up time
	time = new QTime(0, 0, 5);
	timeSet = convertToMS(5, 0);

	// send timer to display
	connect(myTimer, &QTimer::timeout, this, &timerReading::sendTimer);
	myTimer->start(1000);
	eTimer->start();
}

/* Define: getTime

		Update time on timer

	Return:

		time in QString
 */
QString timerReading::getTime()
{
	cnt++;
	if ((cnt * 1000) > timeSet)
	{
		clearTimer();
	}
	else
	{
		time->setHMS(0, time->addSecs(-1).minute(), time->addSecs(-1).second());
		return (time->toString("mm:ss"));
	}

	return ("00:00");
}

/* Define: sendTimer

	Send TImer to be updated
 */
void timerReading::sendTimer()
{
	emit showTime();
}

/* Function: setClock

		Slot to set Clock
*/
void timerReading::setClock(int sec, int min)
{
	cnt = 0;
	delete time;
	time = NULL;
	time = new QTime(0, min, sec);
	timeSet = convertToMS(sec, min);
}

/* Function: convertToMS

		Slot to convert min/sec to ms
*/
int timerReading::convertToMS(int sec, int min)
{
	return (min * 60000 + sec * 1000);
}

/* Define: clearTimer

	Change State

 */
void timerReading::clearTimer()
{
	if (state == 0) // Rest
	{
		emit updateColor(0);
		setClock(6, 0);
		state = 1; // change state when done
	}
	else // Rolling
	{
		emit updateColor(1);
		setClock(10, 0);
		state = 0; // change state when done
	}
}

// Deconstructor
timerReading::~timerReading()
{

}
