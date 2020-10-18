
/* File: mainScreenWidget.cpp

    Contains functions for mainScreenWidget

    Author: Nico Ramirez
*/
#include "mainScreenWidget.h"

#include <QDebug>

QString situationalLogo = ":/images/icons/situationalButton.PNG";            //Path to icon image from resource file
QString intervalTimerIcon = ":/images/icons/intervalTimer.png";

using namespace std;

/* Constructor: mainScreen

        Lays out all objects for the mainScreen page

    Parameters:

        parent - Inherits QWidget attributes
*/
mainScreen::mainScreen(QWidget *parent) :
    GUI_Style(parent)

{
    // Create timer interval button
    showIntervalTimer = new QPushButton(parent);
    showIntervalTimer->setObjectName(QString::fromUtf8("showIntervalTimer"));
    showIntervalTimer->setMinimumSize(240, 240);
    showIntervalTimer->setMaximumSize(240, 240);
	showIntervalTimer->setIcon(QIcon(QPixmap(intervalTimerIcon).scaled(showIntervalTimer->size())));
	showIntervalTimer->setIconSize(QSize(250, 230));

    // Create timer interval button
    situationalBtn = new QPushButton(parent);
    situationalBtn->setObjectName(QString::fromUtf8("showSituationalPage"));
    situationalBtn->setMinimumSize(240, 240);
    situationalBtn->setMaximumSize(240, 240);
    situationalBtn->setIcon(QIcon(QPixmap(situationalLogo).scaled(situationalBtn->size())));
    situationalBtn->setIconSize(QSize(250, 220));

    mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(100);
    mainLayout->addWidget(showIntervalTimer, 0, Qt::AlignCenter);
    mainLayout->addWidget(situationalBtn, 0, Qt::AlignCenter);

    setLayout(mainLayout);

    setStyleSheet(GUI_Style.mainWindowGrey);
    showIntervalTimer->setStyleSheet(GUI_Style.iconBtn);
    situationalBtn->setStyleSheet(GUI_Style.iconBtn1);

	// connect signals 
	connect(showIntervalTimer, &QPushButton::pressed, this, &mainScreen::intervalTimerButton_Pressed);
	connect(showIntervalTimer, &QPushButton::released, this, &mainScreen::intervalTimerButton_Released);
	connect(situationalBtn, &QPushButton::pressed, this, &mainScreen::situationalButton_Pressed);
	connect(situationalBtn, &QPushButton::released, this, &mainScreen::situationalButton_Released);
}


/* Function: intervalTimerButton_Pressed

		Slot to handle interval timer button being pressed
*/
void mainScreen::intervalTimerButton_Pressed()
{
	// color button grey indicating pressed button
	showIntervalTimer->setStyleSheet(GUI_Style.iconBtnPressed);
}

/* Function: intervalTimerButton_Released

		Slot to handle interval timer button is released.
*/
void mainScreen::intervalTimerButton_Released()
{
	showIntervalTimer->setStyleSheet(GUI_Style.iconBtn);
	emit switchToIntervalPage();
}

/* Function: situationalButton_Pressed

		Slot to handle situational button being pressed
*/
void mainScreen::situationalButton_Pressed()
{
	// color button grey indicating pressed button
	situationalBtn->setStyleSheet(GUI_Style.iconBtnPressed);
}

/* Function: situationalButton_Released

		Slot to handle situational button is released.
*/
void mainScreen::situationalButton_Released()
{
	situationalBtn->setStyleSheet(GUI_Style.iconBtn1);
	emit switchToSituationalPage();
}
