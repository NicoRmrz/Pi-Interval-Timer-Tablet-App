#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "GUI_Stylesheet.h"
#include "intervalTimerPage.h"
#include "situationalPage.h"

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
    void intervalTimerButton_Pressed();
    void intervalTimerButton_Released();
    void situationalButton_Pressed();
    void situationalButton_Released();
    void sendStatusBar(QString message, int time);
    void returnToMain(QString page);

private:
    void closeEvent(QCloseEvent *event);

    void showIntervalTimer();
    void showSituationalGame();
	Ui::MainWindow *ui;
    GUI_Style GUI_Style;
};
