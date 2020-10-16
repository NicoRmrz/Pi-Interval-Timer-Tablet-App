#pragma once
#include <QWidget>
#include <QObject>
#include <QtCore/QTimer>
#include <QTime>
#include <QElapsedTimer> 

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
	QElapsedTimer *eTimer;

	void setClock(int sec, int min);
	void startTimer();
	void clearTimer();
	QString getTime();
	void sendTimer();

	int state, cnt, timeSet;
	bool isRunning;

	int convertToMS(int sec, int min);

signals:
	void showTime();
	void updateColor(int state);
};
