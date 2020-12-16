#pragma once
#include <QWidget>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QProcess>

#include "GUI_Stylesheet.h"
#include "timer.h"
#include "editPopUp.h"

/* Class: IntervalTimer

    QWidget widget to hold all objects needed for IntervalTimer implementation
*/
class IntervalTimer : public QWidget
{
    Q_OBJECT

public:
    IntervalTimer(QWidget *parent);
    ~IntervalTimer() {};
    QLabel      *exeTimer;
    QLabel      *timerStateLabel;
	timerReading *currTimer;
    QPushButton *startBtn;
    QPushButton *restartBtn;
    QPushButton *backBtn;
    QPushButton *editBtn;
    QVBoxLayout *mainVLayout;
    QHBoxLayout *controlBtnLayout;
    QHBoxLayout *topBtnLayout;
    QProcess    *soundProcess;

    void playSound(QString sound);
    
    bool isRunning;
    int state = 0;

signals:
    void intervalState(int state);
    void returnPage(QString page);

public slots:
    void updateTimerDisplay();
    void changeColor(int state);
    void startButton_Pressed();
    void startButton_Released();
    void restartButton_Pressed();
    void restartButton_Released();
    void backButton_Pressed();
    void backButton_Released();    
	void editButton_Pressed();
    void editButton_Released();

private:
    int pauseSec, pauseMin;

};
