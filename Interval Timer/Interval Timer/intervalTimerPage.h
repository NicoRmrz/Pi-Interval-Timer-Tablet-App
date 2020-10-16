#pragma once
#include <QWidget>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

#include "GUI_Stylesheet.h"
#include "timer.h"

/* Class: IntervalTimer

    QWidget widget to hold all objects needed for IntervalTimer implementation
*/
class IntervalTimer : public QWidget
{
    Q_OBJECT

public:
    IntervalTimer(QWidget *parent);
    ~IntervalTimer() {};
    GUI_Style    GUI_Style;
    QLabel      *exeTimer;
	timerReading      *currTimer;
    QPushButton *startBtn;
    QPushButton *pauseResumeBtn;
    QPushButton *backBtn;
    QVBoxLayout *mainVLayout;
    bool isRunning;

signals:
    void intervalState(int state);
    void returnPage(QString page);

public slots:
    void updateTimerDisplay();
    void changeColor(int state);
    void startButton_Pressed();
    void startButton_Released();
    void pauseResumeButton_Pressed();
    void pauseResumeButton_Released();
    void backButton_Pressed();
    void backButton_Released();

private:
    int rollSec, rollMin, restSec, restMin, pauseSec, pauseMin;

};
