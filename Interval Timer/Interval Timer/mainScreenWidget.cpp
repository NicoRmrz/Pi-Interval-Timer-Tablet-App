
/* File: mainScreenWidget.cpp

    Contains functions for mainScreenWidget

    Author: Nico Ramirez
*/
#include "mainScreenWidget.h"

#include <QDebug>
#include <QCoreApplication>

using namespace std;

/* Constructor: mainScreen

        Lays out all objects for the mainScreen page

    Parameters:

        parent - Inherits QWidget attributes
*/
mainScreen::mainScreen(QWidget *parent) 

{
	setFixedSize(QSize(parent->size()));

    // create title
    appTitle = new QLabel(parent);
    appTitle->setText("Jitz Trainer");
    appTitle->setMinimumWidth(500);
    appTitle->setAlignment(Qt::AlignCenter);

    // Create timer interval button
    showIntervalTimer = new QPushButton(parent);
    showIntervalTimer->setObjectName(QString::fromUtf8("showIntervalTimer"));
    showIntervalTimer->setMinimumSize(230, 230);
    showIntervalTimer->setMaximumSize(230, 230);
    showIntervalTimer->setIconSize(QSize(250, 230));
    showIntervalTimer->setFocusPolicy(Qt::NoFocus);
    
    // Create timer interval button
    situationalBtn = new QPushButton(parent);
    situationalBtn->setObjectName(QString::fromUtf8("showSituationalPage"));
    situationalBtn->setMinimumSize(230, 230);
    situationalBtn->setMaximumSize(250, 260);
    situationalBtn->setIconSize(QSize(240, 250));
    situationalBtn->setFocusPolicy(Qt::NoFocus);

	// exit button
	exitButton = new QPushButton(parent);
	exitButton->setObjectName(QString::fromUtf8("exitButton"));
	exitButton->setMinimumSize(25, 25);
	exitButton->setMaximumSize(25, 25);
	exitButton->setIconSize(QSize(25, 25));
	exitButton->setFocusPolicy(Qt::NoFocus);

	buttonLayout = new QHBoxLayout();
	buttonLayout->setContentsMargins(0, 0, 0, 0);
	buttonLayout->setSpacing(0);
	buttonLayout->addWidget(showIntervalTimer, 0, Qt::AlignCenter);
	buttonLayout->addWidget(situationalBtn, 0, Qt::AlignCenter);

	mainLayout = new QVBoxLayout();
	mainLayout->setContentsMargins(20, 10, 20, 20);
	mainLayout->setSpacing(0);
	mainLayout->addWidget(exitButton, 0, Qt::AlignRight);
	mainLayout->addWidget(appTitle, 1, Qt::AlignCenter);
    mainLayout->addLayout(buttonLayout, Qt::AlignTop);

    setLayout(mainLayout);

    setStyleSheet(mainWindowGrey);
    showIntervalTimer->setStyleSheet(timerButtonSTYLE);
    situationalBtn->setStyleSheet(situationalButtonSTYLE);
    exitButton->setStyleSheet(exitButtonStyle);
    appTitle->setStyleSheet(appMainTitle);


	// connect signals 
	connect(showIntervalTimer, &QPushButton::released, this, &mainScreen::intervalTimerButton_Released);
	connect(situationalBtn, &QPushButton::released, this, &mainScreen::situationalButton_Released);
	connect(exitButton, &QPushButton::pressed, this, &mainScreen::exitButton_Pressed);
}

/* Function: intervalTimerButton_Released

		Slot to handle interval timer button is released.
*/
void mainScreen::intervalTimerButton_Released()
{
	emit switchToIntervalPage();
}


/* Function: situationalButton_Released

		Slot to handle situational button is released.
*/
void mainScreen::situationalButton_Released()
{
	emit switchToSituationalPage();
}

/* Function: exitButton_Pressed

		Slot to handle exut button being pressed
*/
void mainScreen::exitButton_Pressed()
{
	QCoreApplication::exit();
}
