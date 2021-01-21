#pragma once
#include <QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

#include "GUI_Stylesheet.h"

/* Class: mainScreen

    QWidget widget to hold all objects needed for mainScreen implementation
*/
class mainScreen : public QWidget
{
    Q_OBJECT

public:
    mainScreen(QWidget *parent);
    ~mainScreen() {};
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QLabel      *appTitle;
    QPushButton *showIntervalTimer;
    QPushButton *situationalBtn;
    QPushButton *exitButton;

signals:
	void switchToIntervalPage();
	void switchToSituationalPage();

public slots:
	void intervalTimerButton_Released();
	void situationalButton_Released();
	void exitButton_Pressed();
};
