
/* File: timer.cpp

	Contains functions for timer

	Author: Nico Ramirez
*/
#include "timer.h"

using namespace std;
#define STARTUP_TIMEOUT 5

/* Constructor: timerReading

		Lays out all objects for the timer for Interval Timer page

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
	currState = 0;  // current timer state
	rollSec = 10;
	rollMin = 0;
	restSec = 6;
	restMin = 0;
}

/* Function: startTimer

		Slot to start Timer
*/
void timerReading::startTimer()
{
	state = 1;
	cnt = 0;

	// set up time
	time = new QTime(0, 0, STARTUP_TIMEOUT);
	timeSet = convertToMS(STARTUP_TIMEOUT, 0);

	// send timer to display
	myTimer->start(1000);
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
		currState = 0;
		emit updateColor(currState);
		setClock(restSec, restMin);
		state = 1; // change state when done
	}
	else // Rolling
	{
		currState = 1;
		emit updateColor(currState);
		setClock(rollSec, rollMin);
		state = 0; // change state when done
	}
}

/* Define: restartTimer

	Restart timer
 */
void timerReading::restartTimer()
{
	if 	(isRunning == false)
	{
		if (currState == 0) // Idle
		{
			setClock(restSec, restMin);
		}
		else if (currState == 1) // Rolling
		{
			setClock(rollSec, rollMin);
		}
	}
}

/* Function: setRollTime

		Set Roll Timer
*/
void timerReading::setRollTime(int sec, int min)
{
	rollSec = sec;
	rollMin = min;
}

/* Function: setRestTime

		Set Rest Timer
*/
void timerReading::setRestTime(int sec, int min)
{
	restSec = sec;
	restMin = min;
}

