#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "GUI_Stylesheet.h"
#include "intervalTimerPage.h"
#include "situationalPage.h"

//Path to icon image from resource file
#define APP_VERSION QString("1.0")
#define WINDOW_TITLE QString("Jitz Trainer v" + APP_VERSION)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
    void updateTimerState(int state);
    IntervalTimer *IntervalTimerWidget;
    situationalGame *situationalWidget;

public slots:

    void sendStatusBar(QString message, int time);
    void returnToMain(QString page);

private:
    void closeEvent(QCloseEvent *event);

    void showIntervalTimer();
    void showSituationalGame();
	Ui::MainWindow *ui;
};
