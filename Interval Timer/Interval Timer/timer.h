#pragma once
#include <QWidget>
#include <QObject>
#include <QtCore/QTimer>
#include <QTime>

#define STARTUP_TIMEOUT 5
#define DEFAULT_ROLL_SECOND 30
#define DEFAULT_ROLL_MINUTE 2
#define DEFAULT_REST_SECOND 30
#define DEFAULT_REST_MINUTE 0

/* Class: timerReading

	QWidget widget to hold all objects needed for IntervalTimer implementation
*/
class timerReading : public QObject
{
	Q_OBJECT

public:
	timerReading(QObject *parent);
	~timerReading() {};
	QTimer      *myTimer;
	QTime       *time;
	void setClock(int sec, int min);
	void startTimer();
	void clearTimer();
	void restartTimer();
	QString getTime();
	int state, cnt, timeSet, sec, min;
	bool isRunning;
	int convertToMS(int sec, int min);
	void setRollTime(int sec, int min);
	void setRestTime(int sec, int min);

signals:
	void updateColor(int state);

private:
	int rollSec, rollMin, restSec, restMin, pauseSec, pauseMin, currState;
};
