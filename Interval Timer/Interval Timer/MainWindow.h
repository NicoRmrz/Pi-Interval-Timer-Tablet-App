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


public slots:
    void intervalTimerButton_Pressed();
    void intervalTimerButton_Released();

private:
    void closeEvent(QCloseEvent *event);

    void showIntervalTimer();
	Ui::MainWindow *ui;
    GUI_Style GUI_Style;
};
