#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class IntervalTimer : public QMainWindow
{
    Q_OBJECT

public:
    IntervalTimer(QWidget *parent = Q_NULLPTR);
	~IntervalTimer();

private:
	Ui::MainWindow *ui;
};
