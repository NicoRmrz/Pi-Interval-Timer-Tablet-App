#pragma once
#include <QWidget>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtCore/QTimer>
#include <QTime>

#include "GUI_Stylesheet.h"

/* Class: IntervalTimer

    QWidget widget to hold all objects needed for IntervalTimer implementation
*/
class IntervalTimer : public QWidget
{
    Q_OBJECT

public:
    IntervalTimer(QWidget *parent);
    ~IntervalTimer();
    GUI_Style    GUI_Style;
    QLabel      *exeTimer;
    QTimer      *timer;
    QTime       *time;
    QPushButton *startBtn;
    QPushButton *pauseResumeBtn;
    QVBoxLayout *mainVLayout;
    int state;
    bool isRunning;

signals:
    void intervalState(int state);

public slots:
    void updateTimerDisplay();
    void changeState();
    void startButton_Pressed();
    void startButton_Released();
    void pauseResumeButton_Pressed();
    void pauseResumeButton_Released();

private:
    int rollSec, rollMin, restSec, restMin, pauseSec, pauseMin;
    void setClock(int sec, int min);
    void resetTimer(QTimer* timer);

    // void writeToOutput(QString mesaage);
   // void connectionIndicator(bool connection);
  //  bool checkValidInput(QString);
};
