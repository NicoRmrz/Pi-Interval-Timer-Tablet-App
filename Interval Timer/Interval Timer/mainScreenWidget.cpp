
/* File: mainScreenWidget.cpp

    Contains functions for mainScreenWidget

    Author: Nico Ramirez
*/
#include "mainScreenWidget.h"

#include <QDebug>
#include <QCoreApplication>

QString situationalIcon = ":/images/icons/situationalButton.PNG";            //Path to icon image from resource file
QString situationalIconPressed = ":/images/icons/situationalButtonPressed.PNG";            //Path to icon image from resource file
QString intervalTimerIcon = ":/images/icons/intervalTimer1.png";
QString intervalTimerIconPressed = ":/images/icons/intervalTimer.png";
QString exitIcon = ":/images/icons/exit.png";

using namespace std;

/* Constructor: mainScreen

        Lays out all objects for the mainScreen page

    Parameters:

        parent - Inherits QWidget attributes
*/
mainScreen::mainScreen(QWidget *parent) 

{
	setFixedSize(QSize(parent->size()));

    // Create timer interval button
    showIntervalTimer = new QPushButton(parent);
    showIntervalTimer->setObjectName(QString::fromUtf8("showIntervalTimer"));
    showIntervalTimer->setMinimumSize(230, 230);
    showIntervalTimer->setMaximumSize(230, 230);
	showIntervalTimer->setIcon(QIcon(QPixmap(intervalTimerIcon).scaled(showIntervalTimer->size())));
	showIntervalTimer->setIconSize(QSize(250, 230));

    // Create timer interval button
    situationalBtn = new QPushButton(parent);
    situationalBtn->setObjectName(QString::fromUtf8("showSituationalPage"));
    situationalBtn->setMinimumSize(230, 230);
    situationalBtn->setMaximumSize(230, 230);
    situationalBtn->setIcon(QIcon(QPixmap(situationalIcon).scaled(situationalBtn->size())));
    situationalBtn->setIconSize(QSize(250, 220));

	// exit button
	exitButton = new QPushButton(parent);
	exitButton->setObjectName(QString::fromUtf8("exitButton"));
	exitButton->setMinimumSize(25, 25);
	exitButton->setMaximumSize(25, 25);
	exitButton->setIcon(QIcon(exitIcon));
	exitButton->setIconSize(QSize(25, 25));

	buttonLayout = new QHBoxLayout();
	buttonLayout->setContentsMargins(0, 0, 0, 0);
	buttonLayout->setSpacing(0);
	buttonLayout->addWidget(showIntervalTimer, 0, Qt::AlignCenter);
	buttonLayout->addWidget(situationalBtn, 0, Qt::AlignCenter);

	mainLayout = new QVBoxLayout();
	mainLayout->setContentsMargins(20, 10, 20, 20);
	mainLayout->setSpacing(0);
	mainLayout->addWidget(exitButton, 0, Qt::AlignRight);
    mainLayout->addLayout(buttonLayout, Qt::AlignTop);

    setLayout(mainLayout);

    setStyleSheet(mainWindowGrey);
    showIntervalTimer->setStyleSheet(iconOnlyButton);
    situationalBtn->setStyleSheet(iconOnlyButton);
	exitButton->setStyleSheet(iconOnlyButton);

	// connect signals 
	connect(showIntervalTimer, &QPushButton::pressed, this, &mainScreen::intervalTimerButton_Pressed);
	connect(showIntervalTimer, &QPushButton::released, this, &mainScreen::intervalTimerButton_Released);
	connect(situationalBtn, &QPushButton::pressed, this, &mainScreen::situationalButton_Pressed);
	connect(situationalBtn, &QPushButton::released, this, &mainScreen::situationalButton_Released);
	connect(exitButton, &QPushButton::pressed, this, &mainScreen::exitButton_Pressed);
}

/* Function: intervalTimerButton_Pressed

		Slot to handle interval timer button being pressed
*/
void mainScreen::intervalTimerButton_Pressed()
{
	// color button green indicating pressed button
	showIntervalTimer->setIcon(QIcon(QPixmap(intervalTimerIconPressed).scaled(showIntervalTimer->size())));
}

/* Function: intervalTimerButton_Released

		Slot to handle interval timer button is released.
*/
void mainScreen::intervalTimerButton_Released()
{
	showIntervalTimer->setIcon(QIcon(QPixmap(intervalTimerIcon).scaled(showIntervalTimer->size())));
	emit switchToIntervalPage();
}

/* Function: situationalButton_Pressed

		Slot to handle situational button being pressed
*/
void mainScreen::situationalButton_Pressed()
{
	// color button green indicating pressed button
	situationalBtn->setIcon(QIcon(QPixmap(situationalIconPressed).scaled(situationalBtn->size())));
}

/* Function: situationalButton_Released

		Slot to handle situational button is released.
*/
void mainScreen::situationalButton_Released()
{
	situationalBtn->setIcon(QIcon(QPixmap(situationalIcon).scaled(situationalBtn->size())));
	emit switchToSituationalPage();
}

/* Function: exitButton_Pressed

		Slot to handle exut button being pressed
*/
void mainScreen::exitButton_Pressed()
{
	QCoreApplication::exit();
}
